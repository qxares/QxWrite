# QxWrite Bricks Documentation

## Overview
Pure brick system for QxWrite—modular, reusable, clean slate.

### 1. MainWindowBrick
- **Purpose**: Core app window with QTextEdit.
- **Files**: `mainwindowbrick.h`, `mainwindowbrick.cpp`

### 2. InsertBrick
- **Purpose**: Inserts images into QTextEdit via QTextDocument.
- **Files**: `insertbrick.h`, `insertbrick.cpp`

### 3. SaveBrick
- **Purpose**: Saves QTextEdit content to a text file.
- **Files**: `savebrick.h`, `savebrick.cpp`

### 4. MenuManagerBrick
- **Purpose**: Sets up menus, wires bricks to actions with toggle support.
- **Files**: `menumanagerbrick.h`, `menumanagerbrick.cpp`

### 5. BoldBrick
- **Purpose**: Toggles bold formatting on selected text.
- **Files**: `boldbrick.h`, `boldbrick.cpp`

### 6. NewFileBrick
- **Purpose**: Clears the editor for a new document.
- **Files**: `newfilebrick.h`, `newfilebrick.cpp`

### 7. ToolBarBrick
- **Purpose**: Adds a toolbar with Feather icons, toggle indicators for bold/italic.
- **Files**: `toolbarbrick.h`, `toolbarbrick.cpp`

### 8. ItalicBrick
- **Purpose**: Toggles italic formatting on selected text.
- **Files**: `italicbrick.h`, `italicbrick.cpp`

## Notes
- **Current Features**: New doc, save to .txt, insert images, bold/italic with toolbar/menu toggles.
- **Next Steps**: OpenFileBrick, ShortcutsBrick, SDI polish.
- **Future**: More formats, tables, spellcheck.
