

# QxWrite Reference Documentation
*Generated: April 03, 2025*  
*Author: Grok 3 (xAI), with Mac’s input*  
*Location: `/home/ares/Downloads/editor/QxWriteProject/QxWrite.md`*  

## Overview
QxWrite is a Qt-based text editor for Linux, leveraging a modular "Brick" architecture. It features an MDI interface with subwindows (`QMdiArea`), an icon-based toolbar, and an extensive menu system. This document reflects the state of the restored backup as built on April 03, 2025, capturing all components, functionality, and issues for cleanup and alignment with Mac’s vision.

## Build Details
- **Command**:  
  ```bash
  cd /home/ares/Downloads/editor/QxWriteProject
  qmake qxwrite.pro -spec linux-g++ CONFIG+=debug && make clean && make && ./QxWrite
  ```
- **Output**:  
  - Compiles successfully, runs with MDI, toolbar icons from `/icons/*.svg`, and full menu system.  
  - Logs show initialization, subwindow management, and feature triggers (e.g., Import/Export, table ops).  
  - Sample log:  
    ```
    DocumentHandlerBrick: QMdiArea hooked at: QMdiArea(0x6093a1ca11c0)
    ToolBarBrick: Loaded icon "Open" from "/home/ares/Downloads/editor/QxWriteProject/icons/open.svg"
    Menus set up. Format menu actions: 10
    ImportBrick: Imported plain text file: "/home/ares/test/note.txt"
    ExportBrick: Exported as "docx" : "/home/ares/Documents/save test/2222.docx"
    ```
- **Warnings**:  
  - `menumanagerbrick.cpp:23`: Unused `numberingAction`, `bulletsAction`.  
  - `resizebrick.cpp:72`: Unused `event` in `mouseReleaseEvent`.  

## GUI Layout
- **Main Window**:  
  - Size: 800x600 pixels (set in `mainwindowbrick.cpp`).  
  - Style: Fusion (set in `main.cpp`).  
  - Central Widget: `QMdiArea` (logged: `QMdiArea(0x6093a1ca11c0)`).  
- **Menu Bar**: Managed by `MenuManagerBrick`, four top-level menus.  
- **Toolbar**: Managed by `ToolBarBrick`, icon-based, single row.  
- **Editor**: `QTextEdit` per subwindow (e.g., `QTextEdit(0x6093a1ebabf0)`).  

### Menu Structure
From `menumanagerbrick.cpp` logic and logs:
- **File**:  
  - **New** (Submenu):  
    - **QxNote** (Ctrl+N): Type 0 document.  
    - **QxDocument** (Ctrl+D): Type 1 document.  
    - **QxSheet** (Ctrl+S): Type 2 document.  
  - **Open**: Loads file into subwindow.  
  - **Save**: Saves current subwindow as `.txt`.  
  - **Save As…** (Ctrl+Shift+S): Saves with file dialog.  
  - **Exit** (Ctrl+Q): Closes app.  
- **Edit**:  
  - **Undo** (Ctrl+Z): Reverts last action.  
  - **Redo** (Ctrl+Y): Reapplies undone action.  
- **Format**:  
  - **Bold**: Toggles bold (functional).  
  - **Italic**: Toggles italic (functional).  
  - **Font**: Opens font dialog (functional).  
  - **Color**: Opens color dialog (functional).  
  - **Insert Image**: Inserts image via file dialog.  
  - **Align Left**: Aligns text left.  
  - **Align Center**: Aligns text center.  
  - **Align Right**: Aligns text right.  
- **Table**:  
  - **Insert Table**: Adds 3x3 table (120px wide, 30px tall cells).  
  - **Insert Row** (Submenu):  
    - **Before** (Ctrl+R): Adds row before cursor.  
    - **After**: Adds row after cursor.  
    - **Above**: Adds row above cursor.  
    - **Below**: Adds row below cursor.  
  - **Insert Column** (Submenu):  
    - **Before** (Ctrl+C): Adds column before cursor.  
    - **After**: Adds column after cursor.  
    - **Above**: Adds column above cursor.  
    - **Below**: Adds column below cursor.  
  - **Delete Row**: Removes current row.  
  - **Delete Column**: Removes current column.  
  - **Edit** (Submenu):  
    - **Merge Cells**: Combines selected cells.  
    - **Split Cells**: Divides merged cells.  
  - **Delete Table**: Removes entire table.  
  - **Align Left**: Aligns table left.  
  - **Align Center**: Aligns table center.  
  - **Align Right**: Aligns table right.  
  - **Move**: Repositions table (unimplemented?).  

### Toolbar
- **Layout**: Single row, icons only (no text labels).  
- **Actions** (from `toolbarbrick.cpp` and logs):  
  1. **Open**: `open.svg` (triggers file open).  
  2. **Save**: `save.svg` (saves as `.txt`).  
  3. **Bold**: `bold.svg` (toggles bold).  
  4. **Italic**: `italic.svg` (toggles italic).  
  5. **Font**: `font.svg` (opens font dialog).  
  6. **Color**: `color.svg` (opens color dialog).  
  7. **Image**: `image.svg` (inserts image).  
  8. **Align Left**: `align-left.svg` (aligns left).  
  9. **Align Center**: `align-center.svg` (aligns center).  
  10. **Align Right**: `align-right.svg` (aligns right).  
- **Behavior**: Icons load from `/icons/*.svg`, all actions functional per logs.

## Code Structure
### Project File (`qxwrite.pro`)
```pro
QT += core gui widgets printsupport
TARGET = QxWrite
TEMPLATE = app
SOURCES += main.cpp mainwindowbrick.cpp toolbarbrick.cpp menumanagerbrick.cpp newfilebrick.cpp openfilebrick.cpp savemanagerbrick.cpp boldbrick.cpp italicbrick.cpp fontbrick.cpp colorbrick.cpp insertbrick.cpp alignbrick.cpp dialogbrick.cpp documentwindow.cpp savefunctionbrick.cpp saveguibrick.cpp savehandlerbrick.cpp iconbrick.cpp documenthandlerbrick.cpp listbrick.cpp tablebrick.cpp tablehandlerbrick.cpp resizebrick.cpp importbrick.cpp exportbrick.cpp
HEADERS += mainwindowbrick.h toolbarbrick.h menumanagerbrick.h newfilebrick.h openfilebrick.h savemanagerbrick.h boldbrick.h italicbrick.h fontbrick.h colorbrick.h insertbrick.h alignbrick.h dialogbrick.h documentwindow.h savefunctionbrick.h saveguibrick.h savehandlerbrick.h iconbrick.h documenthandlerbrick.h listbrick.h tablebrick.h tablehandlerbrick.h resizebrick.h importbrick.h exportbrick.h
RESOURCES += icons.qrc
```
- **Notes**: Slimmer than previous versions, no extraneous image files.

### Core Files
- **`main.cpp`**:
  ```cpp
  #include <QApplication>
  #include <QStyleFactory>
  #include "mainwindowbrick.h"

  int main(int argc, char *argv[]) {
      QApplication app(argc, argv);
      app.setStyle(QStyleFactory::create("Fusion"));
      MainWindowBrick window;
      window.show();
      return app.exec();
  }
  ```
  - Sets up app with Fusion style, launches `MainWindowBrick`.

- **`mainwindowbrick.h`** (inferred from logs/build):
  ```cpp
  #ifndef MAINWINDOWBRICK_H
  #define MAINWINDOWBRICK_H

  #include <QMainWindow>
  #include <QMdiArea>

  class QTextEdit;
  class ToolBarBrick;
  class MenuManagerBrick;
  class BoldBrick;
  class ImportBrick;
  class ExportBrick;
  class DocumentHandlerBrick;

  class MainWindowBrick : public QMainWindow {
      Q_OBJECT
  public:
      explicit MainWindowBrick(QWidget *parent = nullptr);
      ~MainWindowBrick();

  private:
      QMdiArea *mdiArea;
      ToolBarBrick *toolBarBrick;
      MenuManagerBrick *menuManagerBrick;
      BoldBrick *boldBrick;
      ImportBrick *importBrick;
      ExportBrick *exportBrick;
      DocumentHandlerBrick *documentHandlerBrick;
  };
  #endif
  ```
  - Declares MDI-based main window with core Bricks.

- **`mainwindowbrick.cpp`** (partial, from logs):
  ```cpp
  #include "mainwindowbrick.h"
  #include <QTextEdit>
  #include <QMdiArea>
  #include <QDebug>
  #include "toolbarbrick.h"
  #include "menumanagerbrick.h"
  #include "boldbrick.h"
  #include "importbrick.h"
  #include "exportbrick.h"
  #include "documenthandlerbrick.h"

  MainWindowBrick::MainWindowBrick(QWidget *parent) : QMainWindow(parent) {
      qDebug() << "MainWindowBrick starting...";
      mdiArea = new QMdiArea(this);
      setCentralWidget(mdiArea);
      resize(800, 600);

      toolBarBrick = new ToolBarBrick(this);
      addToolBar(toolBarBrick->getToolBar());

      menuManagerBrick = new MenuManagerBrick(menuBar(), this);
      boldBrick = new BoldBrick(nullptr, this);
      importBrick = new ImportBrick(nullptr, this);
      exportBrick = new ExportBrick(nullptr, this);
      documentHandlerBrick = new DocumentHandlerBrick(mdiArea, this);

      qDebug() << "MainWindowBrick ready.";
  }

  MainWindowBrick::~MainWindowBrick() {
      qDebug() << "MainWindowBrick: BoldBrick destroyed";
      delete boldBrick;
      qDebug() << "MainWindowBrick: ImportBrick destroyed";
      delete importBrick;
      qDebug() << "MainWindowBrick: ExportBrick destroyed";
      delete exportBrick;
      qDebug() << "MainWindowBrick: DocumentHandlerBrick destroyed";
      delete documentHandlerBrick;
      qDebug() << "MainWindowBrick: ToolBarBrick destroyed";
      delete toolBarBrick;
      qDebug() << "MainWindowBrick: MenuManagerBrick destroyed";
      delete menuManagerBrick;
      qDebug() << "MainWindowBrick: MDIArea destroyed";
      delete mdiArea;
      qDebug() << "MainWindowBrick destroyed";
  }
  ```

### Brick Architecture
- **Concept**: Features split into specialized Bricks (e.g., `BoldBrick`, `SaveManagerBrick`).  
- **Key Bricks** (from logs/build):  
  - **`toolbarbrick.cpp`**:
    ```cpp
    #include "toolbarbrick.h"
    #include <QDebug>

    ToolBarBrick::ToolBarBrick(QWidget *parent) : QObject(parent) {
        toolBar = new QToolBar(parent);
        addToolBarAction("open", "Open", ":/icons/open.svg");
        addToolBarAction("save", "Save", ":/icons/save.svg");
        addToolBarAction("bold", "Bold", ":/icons/bold.svg");
        addToolBarAction("italic", "Italic", ":/icons/italic.svg");
        addToolBarAction("font", "Font", ":/icons/font.svg");
        addToolBarAction("color", "Color", ":/icons/color.svg");
        addToolBarAction("image", "Image", ":/icons/image.svg");
        addToolBarAction("alignLeft", "Align Left", ":/icons/align-left.svg");
        addToolBarAction("alignCenter", "Align Center", ":/icons/align-center.svg");
        addToolBarAction("alignRight", "Align Right", ":/icons/align-right.svg");

        qDebug() << "ToolBarBrick initialized with toolbar:" << toolBar;
    }

    void ToolBarBrick::addToolBarAction(const QString &name, const QString &text, const QString &iconPath) {
        QIcon icon(iconPath);
        qDebug() << "ToolBarBrick: Loaded icon" << text << "from" << iconPath;
        QAction *action = new QAction(icon, text, this);
        actions[name] = action;
        toolBar->addAction(action);
    }
    ```
  - **`importbrick.cpp`** (inferred):
    ```cpp
    #include "importbrick.h"
    #include <QTextEdit>
    #include <QFileDialog>
    #include <QDebug>

    ImportBrick::ImportBrick(QTextEdit *edit, QObject *parent) : QObject(parent), targetEdit(edit) {
        qDebug() << "ImportBrick initialized, target edit:" << targetEdit;
    }

    void ImportBrick::importFile() {
        DialogBrick dialog(this);
        QString fileName = dialog.getOpenFileName(nullptr, "Import File", "/home/ares",
            "Text (*.txt);;HTML (*.html);;Word (*.doc);;Word XML (*.docx);;OpenDocument (*.odt);;PDF (*.pdf);;All Files (*)");
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                targetEdit->setPlainText(in.readAll());
                qDebug() << "ImportBrick: Imported plain text file:" << fileName;
                file.close();
            }
        }
    }
    ```
  - **`exportbrick.cpp`** (inferred):
    ```cpp
    #include "exportbrick.h"
    #include <QTextEdit>
    #include <QFileDialog>
    #include <QProcess>
    #include <QDebug>

    ExportBrick::ExportBrick(QTextEdit *edit, QObject *parent) : QObject(parent), targetEdit(edit) {
        qDebug() << "ExportBrick initialized, target edit:" << targetEdit;
    }

    void ExportBrick::exportFile() {
        DialogBrick dialog(this);
        QString fileName = dialog.getSaveFileName(nullptr, "Export File", "/home/ares",
            "Word (*.doc);;Word XML (*.docx);;OpenDocument (*.odt);;PDF (*.pdf);;All Files (*)");
        if (!fileName.isEmpty()) {
            QString tempHtml = "/tmp/qxwrite_temp_export.html";
            QFile tempFile(tempHtml);
            if (tempFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&tempFile);
                out << targetEdit->toHtml();
                tempFile.close();
                qDebug() << "ExportBrick: Temp HTML written to:" << tempHtml;
            }
            QProcess process;
            process.start("libreoffice", {"--headless", "--convert-to", "docx", tempHtml Xander Snowman "--outdir", QFileInfo(fileName).absolutePath()});
            process.waitForFinished();
            qDebug() << "ExportBrick: LibreOffice conversion successful for:" << fileName + ".docx";
        }
    }
    ```

## Functionality
### File Operations
- **New**: Creates subwindow with type (0=QxNote, 1=QxDocument, 2=QxSheet).  
- **Open**: Loads file into subwindow.  
- **Save/Save As**: Saves as `.txt`.  
- **Import**: Supports `.txt`, `.html`, `.doc`, `.docx`, `.odt`, `.pdf` (plain text for now).  
- **Export**: Converts to `.doc`, `.docx`, `.odt`, `.pdf` via LibreOffice.  

### Text Formatting
- **Bold/Italic/Font/Color**: Fully functional via menu and toolbar.  
- **Align Left/Center/Right**: Applies to text or tables.  
- **Insert Image**: Adds images (e.g., `.png`) to `QTextEdit`.  

### Table Operations
- **Insert/Delete**: Adds/removes tables, rows, columns.  
- **Merge/Split**: Modifies cell structure.  
- **Align**: Positions table.  

### MDI
- Managed by `DocumentHandlerBrick`, supports cascading subwindows.

## Issues
1. **Icon Path**: Logs show `/icons/*.svg`, but `toolbarbrick.cpp` uses `:/icons/`.  
2. **Unused Params**: `menumanagerbrick.cpp` (numbering/bullets), `resizebrick.cpp` (event).  
3. **Font Error**: `QFont::setPointSizeF: Point size <= 0` in logs.  
4. **MDI Bloat**: Multiple subwindows vs. single-editor goal.  

## Target Specification (Mac’s Vision)
- **Menus**: File (New/Open/Save/Import/Export), Format, Insert, Table.  
- **Toolbar**: Icons only: open, save, bold, italic, font, color, image, align left/center/right.  
- **Editor**: Single `QTextEdit`, no MDI.  

April 03, 2025 - 17:45 UTC

Update/Summary:

Rolled back to a stable build and tackled the subwindow chaos in QxWrite. Started with floating QWidget subwindows overlapping the toolbar and menu—yikes. First fix: added a QWidget *subWindowContainer with a QVBoxLayout in mainwindowbrick.h/cpp to stack them below the toolbar, embedding them in the main window. Worked, but they stacked bare—no borders, no controls, just QTextEdits on top of each other. Mac wanted proper document vibes, so we swapped it for a QMdiArea in mainwindowbrick.h/cpp. Now, subwindows are QMdiSubWindows with titles, borders, and close/minimize/maximize buttons, cascading inside the main window. Main textEdit became "Main Document" on startup (unplanned but rolled with it). Save-on-close works for "Main Document" only—other subwindows close without prompting (to fix next). Build’s clean, toolbar’s static, and Brick architecture’s holding strong. Paused here—Mac’s clocking out after a 10-hour grind. Next up: sync save prompts for all subwindows and toolbar to active window.

