# QxWrite Documentation

## Overview
QxWrite is a modular, Qt-based text and document editor built in C++ with a focus on rich text, image handling, and extensibility. Rebuild started fresh on March 19, 2025.

## Current Structure (Rebuild - March 19, 2025)
Live at https://github.com/qxares/QxWrite/tree/main.

### Classes and Files
- **main.cpp**: Entry point, launches `QxWrite`.
- **qxwrite.h/.cpp**: Main window (MDI area, menus).
- **documenteditor.h/.cpp**: Core editor with rich text and image support.
- **filedialog.h/.cpp**: Modular file dialog.
- **imageplaceholder.h/.cpp**: Manages image insertion via placeholders.
- **imageselector.h/.cpp**: Detects images under cursor.
- **imagepositioner.h/.cpp**: Finds image bounds in document.
- **imageresizer.h/.cpp**: Resizes images with visual feedback.

### Key Features
- **ImageResizer**: Scales images with rubber band, in progress.

### Issues
- Menu bar visibility logs false initially but shows (Qt timing quirk).
- Image resizing offset to selection (fixing).

### Wishlist
- Toolbar with formatting options.
- Save/load rich text documents.
- Undo/redo stack.

## Build Instructions
```bash
qmake qxwrite.pro -spec linux-g++ CONFIG+=debug
make clean
make
./QxWrite
```

## Development Workflow
- **Code Style**: Use copy-paste commands in terminal (e.g., `echo "..." > file.cpp`) to avoid typos and simplify updates, per qxares’ preference.
- **Brick Philosophy**: Favor many small, focused bricks over large, complex ones to isolate issues and enhance modularity (qxares’ directive).
- **GitHub Push**: To avoid branch mismatches:
  1. `git init`
  2. `git add .`
  3. `git commit -m "Message"`
  4. `git remote add origin https://github.com/qxares/QxWrite.git`
  5. `git push -f origin main` (force if rebuilding)
  6. `git push origin main` (normal)

## Notes
- Date: March 19, 2025
- Keybindings fixed by using `gnome-terminal` after removing `xterm`.

