#include "resizebrick.h"
#include <QTextCursor>
#include <QTextTable>
#include <QMouseEvent>
#include <QDebug>
#include <QApplication>
#include <QAbstractTextDocumentLayout> // Added for documentLayout()

ResizeBrick::ResizeBrick(QTextEdit *textEdit, QObject *parent) : QObject(parent), 
    m_textEdit(textEdit), m_resizing(false), m_currentTable(nullptr) {}

void ResizeBrick::setTextEdit(QTextEdit *textEdit) {
    m_textEdit = textEdit;
}

void ResizeBrick::enableResize() {
    if (!m_textEdit) return;
    m_textEdit->viewport()->installEventFilter(this);
    qDebug() << "ResizeBrick: Enabled for textEdit:" << m_textEdit;
}

bool ResizeBrick::eventFilter(QObject *obj, QEvent *event) {
    if (obj == m_textEdit->viewport()) {
        switch (event->type()) {
            case QEvent::MouseButtonPress:
                mousePressEvent(static_cast<QMouseEvent*>(event));
                return true;
            case QEvent::MouseMove:
                mouseMoveEvent(static_cast<QMouseEvent*>(event));
                return true;
            case QEvent::MouseButtonRelease:
                mouseReleaseEvent(static_cast<QMouseEvent*>(event));
                return true;
            default:
                return false;
        }
    }
    return QObject::eventFilter(obj, event);
}

void ResizeBrick::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QTextCursor cursor = m_textEdit->cursorForPosition(event->pos());
        m_currentTable = cursor.currentTable();
        if (m_currentTable) {
            QRectF tableRect = m_textEdit->document()->documentLayout()->frameBoundingRect(m_currentTable);
            QPointF clickPos = event->pos();
            if ((tableRect.bottomRight() - clickPos).manhattanLength() < 10) { // Near bottom-right
                m_resizing = true;
                m_startPos = event->pos();
                QApplication::setOverrideCursor(Qt::SizeFDiagCursor);
                qDebug() << "ResizeBrick: Started resizing table at" << m_startPos;
            }
        }
    }
}

void ResizeBrick::mouseMoveEvent(QMouseEvent *event) {
    if (m_resizing && m_currentTable) {
        QPoint delta = event->pos() - m_startPos;
        QTextTableFormat format = m_currentTable->format();
        QVector<QTextLength> constraints = format.columnWidthConstraints();
        int cols = m_currentTable->columns();
        for (int i = 0; i < cols; ++i) {
            qreal newWidth = qMax(50.0, constraints[i].rawValue() + delta.x() / cols); // Min width 50px
            constraints[i] = QTextLength(QTextLength::FixedLength, newWidth);
        }
        format.setColumnWidthConstraints(constraints);
        m_currentTable->setFormat(format);
        m_textEdit->update();
    }
}

void ResizeBrick::mouseReleaseEvent(QMouseEvent *event) {
    if (m_resizing) {
        m_resizing = false;
        m_currentTable = nullptr;
        QApplication::restoreOverrideCursor();
        qDebug() << "ResizeBrick: Finished resizing";
    }
}

void ResizeBrick::moveObject() {
    if (!m_textEdit) return;
    QTextCursor cursor = m_textEdit->textCursor();
    QTextTable *table = cursor.currentTable();
    if (!table) {
        qDebug() << "ResizeBrick: No table to move";
        return;
    }

    QPoint initialPos = QCursor::pos();
    QTextBlock block = cursor.block();
    QApplication::setOverrideCursor(Qt::SizeAllCursor);

    while (!(QApplication::mouseButtons() & Qt::LeftButton)) {
        QApplication::processEvents();
    }

    while (QApplication::mouseButtons() & Qt::LeftButton) {
        QApplication::processEvents();
        QPoint currentPos = QCursor::pos();
        int dx = currentPos.x() - initialPos.x();
        QTextBlockFormat blockFormat = block.blockFormat();
        blockFormat.setLeftMargin(qMax(0, dx)); // No negative margin
        cursor.setBlockFormat(blockFormat);
        m_textEdit->update();
    }

    QApplication::restoreOverrideCursor();
    qDebug() << "ResizeBrick: Moved table to left margin:" << block.blockFormat().leftMargin();
}
