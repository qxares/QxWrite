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
- **Features**: Sets up 800x600 UI, toolbar, menu bar, and text edit area.
- **Status**: Fully implemented.

### IconBrick
- **Purpose**: Manages toolbar/menu icons.
- **Features**: Loads 8 SVG icons (new, open, save, bold, italic, font, color, image).
- **Status**: Implemented, icons registered and loaded.

### ToolBarBrick
- **Purpose**: Builds and manages toolbar.
- **Features**: Adds actions with icons for text formatting and file ops.
- **Status**: Implemented, 8 actions set up. (Note: May evolve into GUI Manager subtype.)

### MenuManagerBrick
- **Purpose**: Constructs menu bar.
- **Features**: File, Edit, Format menus with actions.
- **Status**: Fully implemented. Supports "File > New," "File > Open," "File > Save," "File > Save As," "Format > Bold/Italic/Font/Color," and "Insert > Image."
- **Recent Changes**: Fixed connect bug with `OpenFileBrick::openFile()` using modern `connect()` syntax. Added "File > Save As" action.

### InsertBrick
- **Purpose**: Inserts images into text.
- **Features**: Uses `DialogBrick` to select and insert images (e.g., PNGs).
- **Status**: Implemented, inserts images like `"aries.png"`.

### BoldBrick
- **Purpose**: Applies bold formatting.
- **Features**: Toggles bold on selected text.
- **Status**: Implemented, needs testing.

### ItalicBrick
- **Purpose**: Applies italic formatting.
- **Features**: Toggles italic on selected text.
- **Status**: Implemented, needs testing.

### NewFileBrick
- **Purpose**: Creates new documents.
- **Features**: Clears text edit for a fresh start.
- **Status**: Implemented, fully functional (confirmed via debug log).

### OpenFileBrick
- **Purpose**: Opens text files.
- **Features**: Uses `DialogBrick` to select `.txt`, `.md`, etc.
- **Status**: Fully implemented. "File > Open" opens a custom dialog and loads files (e.g., `test45.txt`).
- **Recent Changes**: Fixed menu connect bug for `openFile()` by adding `public slots:` and using modern `connect()` syntax.

### SaveManagerBrick
- **Purpose**: Manages save operations.
- **Features**: Delegates to `SaveFunctionBrick`, `SaveHandlerBrick`, and `SaveGuiBrick`. Supports "File > Save" and "File > Save As".
- **Status**: Fully implemented. "File > Save" and "File > Save As" both functional (e.g., saved `test 0001.txt`).
- **Architecture**:
  - **SaveFunctionBrick**: Writes the file.
  - **SaveHandlerBrick**: Decides when to prompt for a file path.
  - **SaveGuiBrick**: Shows the file dialog via `DialogBrick`.
  - **SaveManagerBrick**: Coordinates the save process, logs actions.

### SaveFunctionBrick
- **Purpose**: Core save logic.
- **Features**: Writes text to file.
- **Status**: Implemented.

### SaveHandlerBrick
- **Purpose**: Initiates save process.
- **Features**: Coordinates with `SaveGuiBrick` to get file path.
- **Status**: Implemented.

### SaveGuiBrick
- **Purpose**: Save UI interaction.
- **Features**: Triggers `DialogBrick` for save path.
- **Status**: Implemented.

### FontBrick
- **Purpose**: Changes font.
- **Features**: Opens font dialog, applies to text.
- **Status**: Implemented, needs testing.

### ColorBrick
- **Purpose**: Changes text color.
- **Features**: Opens color dialog, applies to text.
- **Status**: Implemented, needs testing.

### DialogBrick
- **Purpose**: Custom file dialog with three-pane navigation.
- **Features**: 
  - Left: Drive list (root dirs, 200px min width).
  - Middle: Directory tree.
  - Right: File list with filter support.
  - Filename input with QLineEdit and extension dropdown via QComboBox.
  - Size: 700x500.
- **Status**: Fully implemented. Supports open/save operations.
- **Recent Changes**: Added `lastDir` to persist directory, updated `getOpenFileName()` debug log to show `Open cancelled`.

## Next Steps
- Test formatting bricks (`BoldBrick`, `ItalicBrick`, `FontBrick`, `ColorBrick`).
- Add error handling (e.g., show a `QMessageBox` if file operations fail).
- Consider adding "Recent Files" to the `DialogBrick` for quicker access.
