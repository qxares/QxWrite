#include "savemanagerbrick.h"
#include <QDebug>

SaveManagerBrick::SaveManagerBrick(QTextEdit *edit, QObject *parent)
    : QObject(parent), m_edit(edit) {
    m_function = new SaveFunctionBrick(m_edit, this);
    m_gui = new SaveGUIBrick(m_edit, this);
    m_handler = new SaveHandlerBrick(m_function, m_gui, this);
    m_saveAction = new QAction("Save", this);
    m_saveAsAction = new QAction("Save As", this);

    // Connect Save action
    connect(m_saveAction, &QAction::triggered, m_handler, &SaveHandlerBrick::save);
    // Connect Save As action
    connect(m_saveAsAction, &QAction::triggered, this, &SaveManagerBrick::saveAs);
    // Connect Handler to GUI (prompt for file path if needed)
    connect(m_handler, &SaveHandlerBrick::saveRequested, m_gui, &SaveGUIBrick::save);
    // Connect GUI to Function (write the file)
    connect(m_gui, &SaveGUIBrick::fileSelected, m_function, &SaveFunctionBrick::save);

    qDebug() << "SaveManagerBrick initialized";
}

QAction *SaveManagerBrick::saveAction() const {
    return m_saveAction;
}

QAction *SaveManagerBrick::saveAsAction() const {
    return m_saveAsAction;
}

void SaveManagerBrick::saveAs() {
    qDebug() << "SaveManagerBrick: saveAs triggered";
    emit m_handler->saveRequested(true);  // Force SaveGUIBrick to prompt for a new file path
}
