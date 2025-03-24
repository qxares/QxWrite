#include "italicbrick.h"
#include <QDebug>

ItalicBrick::ItalicBrick(QTextEdit *edit, QObject *parent)
    : QObject(parent), m_edit(edit) {
    qDebug() << "ItalicBrick initialized, target edit:" << m_edit;
    italicAct = new QAction("Italic", this);
    connect(italicAct, &QAction::triggered, this, &ItalicBrick::toggleItalic);
}

void ItalicBrick::toggleItalic() {
    qDebug() << "ItalicBrick: toggleItalic triggered, checked:" << italicAct->isChecked();
    QTextCharFormat fmt;
    fmt.setFontItalic(italicAct->isChecked());
    m_edit->mergeCurrentCharFormat(fmt);
}
