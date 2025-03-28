#include "mainwindowbrick.h"
// ... other includes ...
#include "resizebrick.h"

MainWindowBrick::MainWindowBrick(QWidget *parent) : QMainWindow(parent) {
    // ... existing setup ...

    connect(menuManagerBrick, &MenuManagerBrick::newFileTriggered, this, [this](int type) {
        QTextEdit *textEdit = documentHandler->newDocument(static_cast<NewFileBrick::DocType>(type));
        if (!textEdit) return;

        auto *newFileBrick = new NewFileBrick(textEdit, this);
        auto *openFileBrick = new OpenFileBrick(textEdit, this);
        auto *saveManagerBrick = new SaveManagerBrick(textEdit, this);
        auto *boldBrick = new BoldBrick(textEdit, this);
        auto *italicBrick = new ItalicBrick(textEdit, this);
        auto *fontBrick = new FontBrick(textEdit, this);
        auto *colorBrick = new ColorBrick(textEdit, this);
        auto *insertBrick = new InsertBrick(textEdit, this);
        auto *alignBrick = new AlignBrick(textEdit, this);
        auto *listBrick = new ListBrick(textEdit, this);
        auto *tableBrick = new TableBrick(textEdit, this);
        auto *resizeBrick = new ResizeBrick(textEdit, this);
        resizeBrick->enableResize();

        // Menu connections (unchanged except new ones)
        connect(menuManagerBrick, &MenuManagerBrick::saveAsTriggered, this, [saveManagerBrick]() {
            saveManagerBrick->triggerSave();
        });
        connect(menuManagerBrick, &MenuManagerBrick::moveTriggered, this, [resizeBrick]() {
            resizeBrick->moveObject();
        });
        // ... other existing connections ...

        // Add "Move" to table menu
        QMenu *tableMenu = menuManagerBrick->getMenuBar()->findChild<QMenu*>("tableMenu");
        if (tableMenu) {
            tableMenu->addAction("Move", [resizeBrick]() { resizeBrick->moveObject(); });
        }
    });

    // ... rest unchanged ...
}
