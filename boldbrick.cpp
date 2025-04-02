#include "boldbrick.h"
#include "documenthandlerbrick.h"
#include <QTextEdit>
#include <QDebug>

BoldBrick::BoldBrick(QTextEdit *edit, QObject *parent) : QObject(parent), m_textEdit(edit) {
    qDebug() << "BoldBrick initialized with textEdit:" << m_textEdit;
}

void BoldBrick::applyBold() {
    DocumentHandlerBrick *handler = qobject_cast<DocumentHandlerBrick*>(parent());
    if (!handler) {
        qDebug() << "BoldBrick: No DocumentHandlerBrick parent, cannot apply bold";
        return;
    }
    m_textEdit = handler->getActiveTextEdit();
    if (!m_textEdit || !m_textEdit->document()) {
        qDebug() << "BoldBrick: No active text edit or document, cannot apply bold";
        return;
    }
    QTextCursor cursor = m_textEdit->textCursor();
    if (!cursor.isNull()) {
        int start = cursor.selectionStart();
        int end = cursor.selectionEnd();
        bool hasSelection = cursor.hasSelection();

        if (!hasSelection) {
            int pos = cursor.position();
            cursor.select(QTextCursor::WordUnderCursor);
            if (cursor.selectedText().isEmpty()) {
                qDebug() << "BoldBrick: No word under cursor, expanding to full word";
                cursor.movePosition(QTextCursor::StartOfWord);
                int wordStart = cursor.position();
                cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
                if (pos >= wordStart && pos <= cursor.position()) {
                    m_textEdit->setTextCursor(cursor);
                } else {
                    cursor.setPosition(pos);
                    cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
                    m_textEdit->setTextCursor(cursor);
                }
            } else {
                qDebug() << "BoldBrick: No selection, selecting current word";
                m_textEdit->setTextCursor(cursor);
            }
        }

        QTextCharFormat format;
        format.setFontWeight(cursor.charFormat().fontWeight() == QFont::Bold ? QFont::Normal : QFont::Bold);
        cursor.mergeCharFormat(format);  // Safer than setCharFormat
        m_textEdit->setCurrentCharFormat(format);  // Ensure format sticks
        m_textEdit->repaint();  // Force redraw

        if (hasSelection) {
            cursor.setPosition(start);
            cursor.setPosition(end, QTextCursor::KeepAnchor);
        } else {
            cursor.clearSelection();
        }
        m_textEdit->setTextCursor(cursor);
        qDebug() << "BoldBrick: Applied bold to selection, cursor pos:" << cursor.position();
    } else {
        qDebug() << "BoldBrick: Invalid cursor, skipping bold";
    }
}

void BoldBrick::setTextEdit(QTextEdit *edit) {
    m_textEdit = edit;
    qDebug() << "BoldBrick: TextEdit updated to:" << m_textEdit;
}

void BoldBrick::resetTextEdit() {
    m_textEdit = nullptr;
    qDebug() << "BoldBrick: TextEdit reset to nullptr";
}
