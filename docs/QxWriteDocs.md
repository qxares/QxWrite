# QxWrite Documentation

## Overview
QxWrite is a modular, Qt-based text and document editor built in C++ with a focus on rich text, image handling, and extensibility. This rebuild (March 19, 2025) starts fresh with a Lego-style modular design.

## Current Structure (Rebuild - March 19, 2025)
Starting from scratch—files will be added as we rebuild.

### Planned Classes and Files
- **main.cpp**: Entry point, launches `QxWrite`.
- **qxwrite.h/.cpp**: Main window (MDI area, menus, toolbars).
- **toolbarsetup.h/.cpp**: Toolbar initialization and actions.
- **filedialog.h/.cpp**: Modular file dialog for open/save/import/export.
- **imagehandler.h/.cpp**: Manages image insertion and resizing.
- **documenteditor.h/.cpp**: Core editor with rich text and image support.
- **tabledialog.h/.cpp**: Table insertion dialog (to be re-added later).

### Key Functions/Features (Target)
- **DocumentEditor**:
  - Constructor: Sets up rich text, default font (Times New Roman, 12).
  - `contextMenuEvent`: Right-click menu with 'Insert Image' and 'Resize Image'.
  - `insertImage`: Uses `FileDialog` and `ImageHandler` to insert images.
  - `mousePressEvent`, `mouseMoveEvent`, `mouseReleaseEvent`: Smooth image resizing.
- **QxWrite**:
  - Menu setup: File (New, Open, Save), Edit, Format, etc.
  - Toolbar: Bold, italic, etc.
  - MDI subwindows: Multiple document support.
- **FileDialog**: Reusable file selection with modes (Open, Save, Import, Export).
- **ImageHandler**: Encapsulates image loading, placeholders, and size management.

### Previous Issues (To Fix in Rebuild)
- Right-click image resize was inconsistent.
- Menu bar visibility toggled incorrectly.
- File dialog wasn’t reusable.

### Wishlist
- Save/load rich text documents.
- Undo/redo stack.
- Table resizing.
- Context menu handler for all elements.

## Build Instructions
```bash
qmake qxwrite.pro -spec linux-g++ CONFIG+=debug
make clean
make
./QxWrite
```

## Notes
- Rebuild started fresh on March 19, 2025.
- Linux Mint keybindings (e.g., `Ctrl+O`) previously interfered—fixed by using default terminal (`gnome-terminal`) after removing `xterm`.
- Target: Modular, maintainable code with clear class responsibilities.

