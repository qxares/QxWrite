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
- **Status**: Implemented, connect bug with `OpenFileBrick::openFile()` pending.

### InsertBrick
- **Purpose**: Inserts images into text.
- **Features**: Uses `DialogBrick` to select and insert images (e.g., PNGs).
- **Status**: Implemented, inserts images like `"aries.png"`.

### BoldBrick
- **Purpose**: Applies bold formatting.
- **Features**: Toggles bold on selected text.
- **Status**: Implemented.

### ItalicBrick
- **Purpose**: Applies italic formatting.
- **Features**: Toggles italic on selected text.
- **Status**: Implemented.

### NewFileBrick
- **Purpose**: Creates new documents.
- **Features**: Clears text edit for a fresh start.
- **Status**: Implemented.

### OpenFileBrick
- **Purpose**: Opens text files.
- **Features**: Uses `DialogBrick` to select `.txt`, `.md`, etc.
- **Status**: Implemented, menu connect bug (`openFile()`) to fix.

### SaveManagerBrick
- **Purpose**: Manages save operations.
- **Features**: Delegates to `SaveFunctionBrick`, `SaveGuiBrick`, etc.
- **Status**: Implemented.

### SaveFunctionBrick
- **Purpose**: Core save logic.
- **Features**: Writes text to file.
- **Status**: Implemented.

### SaveGuiBrick
- **Purpose**: Save UI interaction.
- **Features**: Triggers `DialogBrick` for save path.
- **Status**: Implemented.

### FontBrick
- **Purpose**: Changes font.
- **Features**: Opens font dialog, applies to text.
- **Status**: Implemented.

### ColorBrick
- **Purpose**: Changes text color.
- **Features**: Opens color dialog, applies to text.
- **Status**: Implemented.

### DialogBrick
- **Purpose**: Custom file dialog with three-pane navigation.
- **Features**: 
  - Left: Drive list (root dirs, 200px min width).
  - Middle: Directory tree.
  - Right: File list with filter support.
  - Filename input with QLineEdit and extension dropdown via QComboBox.
  - Size: 700x500.
- **Status**: Implemented, fully functional for open/save.
