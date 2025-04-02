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
    QTextCharFormat format = m_textEdit->currentCharFormat();
    format.setFontWeight(format.fontWeight() == QFont::Bold ? QFont::Normal : QFont::Bold);
    m_textEdit->mergeCurrentCharFormat(format);
}

void BoldBrick::setTextEdit(QTextEdit *edit) {
    m_textEdit = edit;
    qDebug() << "BoldBrick: TextEdit updated to:" << m_textEdit;
}

void BoldBrick::resetTextEdit() {
    m_textEdit = nullptr;
    qDebug() << "BoldBrick: TextEdit reset to nullptr";
}
