#include "fontbrick.h"
#include <QTextEdit>
#include <QFontDialog>
#include <QAction>
#include <QDebug>

FontBrick::FontBrick(QTextEdit *edit, QObject *parent)
    : QObject(parent), targetEdit(edit), fontAct(new QAction(tr("Font"), this)) {
    qDebug() << "FontBrick initialized, target edit:" << edit;
    fontAct->setToolTip(tr("Change font and size"));
    connect(fontAct, &QAction::triggered, this, &FontBrick::showFontDialog);
}

void FontBrick::showFontDialog() {
    qDebug() << "FontBrick: showFontDialog triggered";
    bool ok;
    QFont font = QFontDialog::getFont(&ok, targetEdit->currentFont(), targetEdit->window(), tr("Select Font"));
    if (ok) {
        QTextCursor cursor = targetEdit->textCursor();
        if (!cursor.hasSelection()) {
            targetEdit->setCurrentFont(font);
        } else {
            QTextCharFormat format;
            format.setFont(font);
            cursor.mergeCharFormat(format);
        }
        qDebug() << "FontBrick: Applied font:" << font.family() << ", size:" << font.pointSize();
    } else {
        qDebug() << "FontBrick: Font dialog canceled";
    }
}

