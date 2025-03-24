# QxWrite Brick Documentation

## Overview
QxWrite is a modular text editor built with Qt, using a "brick" system for features.

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
- **Status**: Implemented, 8 actions set up.

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
  - Left: Drive list (root dirs, 150px wide).
  - Middle: Directory tree.
  - Right: File list with filter support.
  - Size: 600x400.
- **Status**: Implemented, navigation and selection working.### DialogBrick
- **Purpose**: Custom file dialog with three-pane navigation (drives, directories, files).
- **Features**: 
  - Left: Drive list (root dirs).
  - Middle: Directory tree.
  - Right: File list with filter support.
  - Size: 600x400.
- **Status**: Implemented, navigation and selection working.
