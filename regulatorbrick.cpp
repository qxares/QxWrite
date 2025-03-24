#include "regulatorbrick.h"
#include "iconbrick.h"
#include <QToolBar>
#include <QAction>
#include <QDebug>

RegulatorBrick::RegulatorBrick(IconBrick *iconBrick, QToolBar *toolBar, QObject *parent)
    : QObject(parent), iconBrick(iconBrick), toolBar(toolBar) {
    qDebug() << "RegulatorBrick initialized, iconBrick:" << iconBrick << ", toolBar:" << toolBar;
    verifyIcon("test-color"); // Changed from "color"
    QAction *testAction = toolBar->addAction(iconBrick->loadIcon("test-color"), tr("Test color"));
    qDebug() << "RegulatorBrick: Added test action for \"test-color\" at" << testAction;
}

void RegulatorBrick::verifyIcon(const QString &name) {
    QIcon icon = iconBrick->loadIcon(name);
    if (!icon.isNull()) {
        qDebug() << "RegulatorBrick: Icon" << name << "loaded successfully";
    } else {
        qDebug() << "RegulatorBrick: Icon" << name << "failed to load";
    }
}

