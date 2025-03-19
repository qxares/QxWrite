# QxWrite Bricks Documentation

## Overview
Tracks modular components in QxWrite, now with reusable bricks.

### 1. ImageSceneManager
- **Purpose**: Manages graphics scene (standalone, future use).
- **Files**: `imagescenemanager.h`, `imagescenemanager.cpp`

### 2. ImagePlaceholderInserter
- **Purpose**: Inserts images into active editor via QTextDocument.
- **Files**: `imageplaceholderinserter.h`, `imageplaceholderinserter.cpp`

### 3. ImageDragHandler
- **Purpose**: Drags images with left-click.
- **Files**: `imagedraghandler.h`, `imagedraghandler.cpp`

### 4. MouseEventHandler
- **Purpose**: Legacy resizing.
- **Files**: `mouseeventhandler.h`, `mouseeventhandler.cpp`

### 5. ImageResizer
- **Purpose**: Resizes images.
- **Files**: `imageresizer.h`, `imageresizer.cpp`

### 6. ImageSelector
- **Purpose**: Detects selected images.
- **Files**: `imageselector.h`, `imageselector.cpp`

### 7. FileDialog
- **Purpose**: Custom file dialog (deprecated, using QFileDialog).
- **Files**: `filedialog.h`, `filedialog.cpp`

### 8. ImagePlaceholder
- **Purpose**: Wraps image data.
- **Files**: `imageplaceholder.h`, `imageplaceholder.cpp`

### 9. ImageManipulator
- **Purpose**: Moves/resizes via menu.
- **Files**: `imagemanipulator.h`, `imagemanipulator.cpp`

### 10. MenuManager
- **Purpose**: Generic menu management.
- **Files**: `menumanager.h`, `menumanager.cpp`

### 11. FileManager
- **Purpose**: Generic file operations.
- **Files**: `filemanager.h`, `filemanager.cpp`

### 12. DocumentWindow
- **Purpose**: Single-document window like Word/LibreOffice.
- **Files**: `documentwindow.h`, `documentwindow.cpp`

## Notes
- **Current Features**: Stable "New", image insertion with QFileDialog, single menu, images in QTextEdit.
- **Pending Fixes**: Full SDI transition, scene integration for drag/resize.
- **Future Potential**: Toolbar_Func, mouse resizing, undo/redo.
