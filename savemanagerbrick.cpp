#include "savemanagerbrick.h"
#include "savefunctionbrick.h"
#include "dialogbrick.h"

SaveManagerBrick::SaveManagerBrick(QTextEdit *textEdit, QObject *parent) : QObject(parent) {
    SaveFunctionBrick *function = new SaveFunctionBrick(this);
    DialogBrick *dialog = new DialogBrick(this);
    m_gui = new SaveGUIBrick(this);
    m_handler = new SaveHandlerBrick(textEdit, function, dialog, this);
    connect(m_gui->saveAction(), &QAction::triggered, m_handler, &SaveHandlerBrick::handleSave);
}

QAction *SaveManagerBrick::saveAction() const {
    return m_gui->saveAction();
}
