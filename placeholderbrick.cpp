#include "placeholderbrick.h"
#include <QTextCursor>
#include <QTextBlockFormat>
#include <QDebug>

PlaceholderBrick::PlaceholderBrick(QTextEdit *textEdit, QObject *parent) : QObject(parent), m_textEdit(textEdit) {}

void PlaceholderBrick::insertPlaceholder(int position, ContentType type) {
    if (!m_textEdit) {
        qDebug() << "PlaceholderBrick: No text edit set";
        return;
    }

    QTextCursor cursor = m_textEdit->textCursor();
    cursor.setPosition(position);

    QTextBlockFormat blockFormat;
    blockFormat.setProperty(QTextFormat::UserProperty, static_cast<int>(type));
    cursor.mergeBlockFormat(blockFormat);

    m_textEdit->setTextCursor(cursor);
    qDebug() << "PlaceholderBrick: Inserted placeholder for" << (type == Table ? "Table" : "Image") << "at position" << position;
}
