#include "menumanager.h"
#include <QMenu>
#include <QAction>
#include <QDebug>

MenuManager::MenuManager(QMenuBar *menuBar, QWidget *parent)
    : QObject(parent), menuBar(menuBar) {}

void MenuManager::addFileMenu() {
    qDebug() << "Setting up file menu...";
    QMenu *fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(tr("&New"), this, &MenuManager::newFileRequested);
    fileMenu->addAction(tr("&Open"), this, &MenuManager::openFileRequested);
    fileMenu->addAction(tr("&Save"), this, &MenuManager::saveFileRequested);
    fileMenu->addSeparator();
    fileMenu->addAction(tr("&Quit"), this, &MenuManager::quitRequested);
}

QMenu* MenuManager::addCustomMenu(const QString &title, const QList<QAction*> &actions) {
    QMenu *menu = getCustomMenu(title);
    if (!menu) {
        menu = menuBar->addMenu(title);
    } else {
        menu->clear();
    }
    menu->addActions(actions);
    return menu;
}

QMenu* MenuManager::getCustomMenu(const QString &title) {
    for (QMenu *menu : menuBar->findChildren<QMenu*>()) {
        if (menu->title() == title) {
            return menu;
        }
    }
    return nullptr;
}
