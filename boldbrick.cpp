#include "boldbrick.h"
#include <QDebug>

BoldBrick::BoldBrick(QTextEdit *edit, QObject *parent)
    : QObject(parent), m_edit(edit) {
    qDebug() << "BoldBrick initialized, target edit:" << m_edit;
    boldAct = new QAction("Bold", this);
    connect(boldAct, &QAction::triggered, this, &BoldBrick::toggleBold);
}

void BoldBrick::toggleBold() {
    qDebug() << "BoldBrick: toggleBold triggered, checked:" << boldAct->isChecked();
    QTextCharFormat fmt;
    fmt.setFontWeight(boldAct->isChecked() ? QFont::Bold : QFont::Normal);
    m_edit->mergeCurrentCharFormat(fmt);
}
