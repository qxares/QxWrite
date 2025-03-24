#include "saveguibrick.h"
#include <QIcon>

SaveGUIBrick::SaveGUIBrick(QObject *parent) : QObject(parent) {
    m_saveAction = new QAction(QIcon(":/icons/icons/save.svg"), "Save", this);
    m_saveAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
}
