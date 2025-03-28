# QxWrite Brick Documentation

## Brick Architecture
Every action, no matter how simple or small, follows this 4-brick structure:

1. **Function Brick**
   - **Purpose**: Creates the core function (e.g., bolding text, saving a file).
   - **Role**: Pure logic—takes inputs, delivers outputs, no side effects.

2. **Handler Brick**
   - **Purpose**: Manages interaction if an action requires multiple bricks.
   - **Role**: Coordinates Function Bricks, handles dependencies, sequences execution.

3. **GUI Brick**
   - **Purpose**: Controls and provides the GUI output (e.g., buttons, dialogs).
   - **Role**: Displays UI, emits signals—keeps logic light.

4. **Manager Brick**
   - **Purpose**: Ensures the action runs smoothly and does what it’s supposed to.
   - **Role**: Supervises, validates, logs, and catches errors.

### Special Brick: GUI Manager Brick
- **Purpose**: Regulates all GUI functions for consistency.
- **Role**: Centralizes toolbar/menu layout, ensures everything looks sharp.

## Overview
QxWrite is a modular text editor built with Qt, using the brick system for features.

## Bricks

### MainWindowBrick
- **Purpose**: Core application window.
- **Features**: Sets up 800x600 UI, toolbar, menu bar, and MDI area for multiple documents.
- **Status**: Fully implemented.
- **Recent Changes**: Updated `setupMenus` call to match new signature after removing `newAction` parameter (March 2025). Modified to delegate file opening to `DocumentHandlerBrick` for proper window management (March 2025).

### IconBrick
- **Purpose**: Manages toolbar/menu icons.
- **Features**: Loads 8 SVG icons (new, open, save, bold, italic, font, color, image).
- **Status**: Implemented, icons registered and loaded.

### ToolBarBrick
- **Purpose**: Builds and manages toolbar.
- **Features**: Adds actions with icons for text formatting and file ops.
- **Status**: Implemented, 8 actions set up. (Note: May evolve into GUI Manager subtype.)
- **Recent Changes**: Removed "New" icon from toolbar while retaining the action for menu use (March 2025).

### MenuManagerBrick
- **Purpose**: Constructs menu bar.
- **Features**: File, Edit, Format menus with actions.
- **Status**: Fully implemented. Supports "File > New," "File > Open," "File > Save," "File > Save As," "Format > Bold/Italic/Font/Color," and "Insert > Image."
- **Recent Changes**: Fixed connect bug with `OpenFileBrick::openFile()` using modern `connect()` syntax. Added "File > Save As" action. Attempted to add icons to "New" submenu and "Save As" but reverted due to missing icon file and user preference (March 2025). Added icons to "File > New" and "File > Save As" in the File menu, updated `icons.qrc` to include `save-as.svg` (March 2025). Switched "New" to a `QAction` with a submenu, used `plus.svg` for "New" and `save.svg` for "Save As", updated `icons.qrc` to remove `save-as.svg` and use `plus.svg` (March 2025). Fixed icon visibility by using a stylesheet in `main.cpp` to force menu icons to display (March 2025). Removed stylesheet from `main.cpp`, set icon sizes and visibility directly in `menumanagerbrick.cpp` to restore default menu styling, removed unused `newAction` parameter (March 2025). Reverted icon size and visibility settings in `menumanagerbrick.cpp` to rely on Qt defaults, fixed `setupMenus` declaration in `menumanagerbrick.h` to match implementation (March 2025). Set Qt style to "Fusion" in `main.cpp` to ensure polished menu rendering (March 2025).

### InsertBrick
- **Purpose**: Inserts images into text.
- **Features**: Uses `DialogBrick` to select and insert images (e.g., PNGs).
- **Status**: Implemented, inserts images like `"aries.png"`.

### BoldBrick
- **Purpose**: Applies bold formatting.
- **Features**: Toggles bold on selected text.
- **Status**: Fully implemented and tested. Toggles bold formatting correctly.

### ItalicBrick
- **Purpose**: Applies italic formatting.
- **Features**: Toggles italic on selected text.
- **Status**: Fully implemented and tested. Toggles italic formatting correctly.

### NewFileBrick
- **Purpose**: Creates new documents.
- **Features**: Clears text edit for a fresh start.
- **Status**: Implemented, fully functional (confirmed via debug log).

### OpenFileBrick
- **Purpose**: Opens text files.
- **Features**: Uses `DialogBrick` to select `.txt`, `.md`, etc. Supports rich text via `setHtml()`.
- **Status**: Fully implemented. "File > New" opens a submenu, "File > Open" opens a custom dialog and loads files (e.g., `test45.txt`).
- **Recent Changes**: Fixed menu connect bug for `openFile()` by ensuring it’s under `public slots:` and using modern `connect()` syntax. Verified fix—connect error resolved. Added error handling with `QMessageBox` for failed file opens. Updated `openFile` to support rich text by trying `setHtml()` first, falling back to plain text, added UTF-8 encoding and improved error handling (March 2025).

### SaveManagerBrick
- **Purpose**: Manages save operations.
- **Features**: Delegates to `SaveFunctionBrick`, `SaveHandlerBrick`, and `SaveGuiBrick`. Supports "File > Save" and "File > Save As".
- **Status**: Fully implemented. "File > Save" and "File > Save As" both functional (e.g., saved `test 0001.txt`).
- **Architecture**:
  - **SaveFunctionBrick**: Writes the file.
  - **SaveHandlerBrick**: Decides when to prompt for a file path.
  - **SaveGuiBrick**: Shows the file dialog via `DialogBrick`.
  - **SaveManagerBrick**: Coordinates the save process, logs actions.
- **Recent Changes**: Added `setTextEdit` method to dynamically update the text edit target (March 2025).

### SaveFunctionBrick
- **Purpose**: Core save logic.
- **Features**: Writes text to file. Supports rich text via `toHtml()`.
- **Status**: Implemented. Added error handling with `QMessageBox` for failed file saves.
- **Recent Changes**: Added null check for `m_textEdit` to prevent crashes during save (March 2025).

### SaveHandlerBrick
- **Purpose**: Initiates save process.
- **Features**: Coordinates with `SaveGuiBrick` to get file path.
- **Status**: Implemented.

### SaveGuiBrick
- **Purpose**: Save UI interaction.
- **Features**: Triggers `DialogBrick` for save path.
- **Status**: Implemented.
- **Recent Changes**: Added `setTextEdit` method to dynamically update the text edit target (March 2025).

### FontBrick
- **Purpose**: Changes font.
- **Features**: Opens font dialog, applies to text.
- **Status**: Fully implemented and tested. Applies selected font (e.g., "Ubuntu Sans").

### ColorBrick
- **Purpose**: Changes text color.
- **Features**: Opens color dialog, applies to text.
- **Status**: Fully implemented and tested. Applies selected color (e.g., "#e01b24").

### DialogBrick
- **Purpose**: Custom file dialog with three-pane navigation.
- **Features**: 
  - Left: File list with filter support, includes directories and `..` for navigation.
  - Middle: Directory tree.
  - Right: Drive list (root dirs, 200px min width).
  - Filename input with QLineEdit and extension dropdown via QComboBox.
  - Size: 700x500.
- **Status**: Fully implemented. Supports open/save operations with navigation to parent directories and subdirectories.
- **Recent Changes**: Added `lastDir` to persist directory, updated `getOpenFileName()` debug log to show `Open cancelled`. Added parent directory (`..`) and subdirectory navigation in file list, fixed visibility of directories by adjusting name filter behavior, resolved variable shadowing error in `getSaveFileName` and `getOpenFileName`, fixed `..` visibility in file view (left pane), added root directory check to prevent navigation above `/`.

### DocumentHandlerBrick
- **Purpose**: Manages multiple document windows within a QMdiArea, supporting QxNotes (type 0), QxDocuments (type 1), and QxGrids (type 2).
- **Features**:
  - Creates new document windows with `newDocument(DocType type)`.
  - Opens existing files via `openDocument(OpenFileBrick*)`.
  - Cascades windows of the same type with `cascadeWindows(DocType type)`.
  - Moves cascades interactively via right-click "Move Cascade" with `moveCascade(QMdiSubWindow*)`.
  - Context menu with Undo, Redo, Cut, Copy, Paste, and Move Cascade options.
- **Status**: Stable as of March 26, 2025—tested with up to 7 Documents, 6 Notes, 4 Grids; no segfaults after null checks added. Fixed `¬eWindows` typo to `noteWindows` in `cascadeWindows` and `moveCascade`.
- **Files**: `documenthandlerbrick.h`, `documenthandlerbrick.cpp`
- **Recent Changes**: Added support for cascading windows by document type (QxDocuments, QxNotes, QxSheets) with separate stacks, implemented `openDocument` to create new windows for opened files, added null checks to `cascadeWindows` to prevent segfaults, enhanced debugging with window counts and anchor logging (March 2025).

## Next Steps
- Consider adding "Recent Files" to the `DialogBrick` for quicker access.
- Plan for table support with a new `TableBrick` for QxGrid integration (March 2025).
