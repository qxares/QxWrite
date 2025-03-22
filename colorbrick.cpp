#include "colorbrick.h"
#include <QTextEdit>
#include <QColorDialog>
#include <QAction>
#include <QDebug>

ColorBrick::ColorBrick(QTextEdit *edit, QObject *parent)
    : QObject(parent), targetEdit(edit), colorAct(new QAction(tr("Color"), this)), currentColor(Qt::black) {
    qDebug() << "ColorBrick initialized, target edit:" << edit;
    colorAct->setToolTip(tr("Change text color"));
    connect(colorAct, &QAction::triggered, this, &ColorBrick::showColorDialog);
}

void ColorBrick::showColorDialog() {
    qDebug() << "ColorBrick: showColorDialog triggered";
    QColor color = QColorDialog::getColor(currentColor, targetEdit->window(), tr("Select Text Color"));
    if (color.isValid()) {
        currentColor = color;
        QTextCursor cursor = targetEdit->textCursor();
        if (cursor.hasSelection()) {
            QString html = QString("<span style=\"color:%1\">%2</span>").arg(color.name(), cursor.selectedText());
            cursor.insertHtml(html);
        }
        QTextCharFormat format;
        format.setForeground(color);
        targetEdit->setCurrentCharFormat(format);
        qDebug() << "ColorBrick: Applied color:" << color.name();
    } else {
        qDebug() << "ColorBrick: Color dialog canceled";
    }
}

