#include "colorbrick.h"
#include <QTextEdit>
#include <QColorDialog>
#include <QAction>
#include <QDebug>

ColorBrick::ColorBrick(QTextEdit *edit, QObject *parent)
    : QObject(parent), targetEdit(edit), colorAct(new QAction(tr("Color"), this)) {
    qDebug() << "ColorBrick initialized, target edit:" << edit;
    colorAct->setToolTip(tr("Change text color"));
    connect(colorAct, &QAction::triggered, this, &ColorBrick::showColorDialog);
}

void ColorBrick::showColorDialog() {
    qDebug() << "ColorBrick: showColorDialog triggered";
    QColor color = QColorDialog::getColor(Qt::black, targetEdit->window(), tr("Select Text Color"));
    if (color.isValid()) {
        QTextCursor cursor = targetEdit->textCursor();
        QString html = QString("<span style=\"color:%1\">%2</span>").arg(color.name(), cursor.selectedText().isEmpty() ? " " : cursor.selectedText());
        cursor.insertHtml(html);
        qDebug() << "ColorBrick: Applied color:" << color.name();
    } else {
        qDebug() << "ColorBrick: Color dialog canceled";
    }
}

