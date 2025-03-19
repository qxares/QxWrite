# QxWrite Bricks Documentation

## Overview
This document tracks the modular "bricks" in QxWrite, detailing their purpose and functionality for future feature development.

### 1. ImageSceneManager
- **Purpose**: Manages the graphics scene for displaying and positioning images.
- **Key Functions**:
  - `addImage(QUrl, QPixmap, QPoint)`: Adds an image to the scene at a position.
  - `getImageItem(QUrl)`: Retrieves a specific image item by URL.
  - `itemAt(QPoint)`: Finds the item at a given position.
- **Files**: `imagescenemanager.h`, `imagescenemanager.cpp`

### 2. ImagePlaceholderInserter
- **Purpose**: Handles image insertion via menu or context menu.
- **Key Functions**:
  - `insertImage()`: Opens a file dialog and inserts the selected image into the scene.
- **Files**: `imageplaceholderinserter.h`, `imageplaceholderinserter.cpp`

### 3. ImageDragHandler
- **Purpose**: Enables dragging images within the scene using left-click.
- **Key Functions**:
  - `eventFilter()`: Captures mouse events to move images.
- **Files**: `imagedraghandler.h`, `imagedraghandler.cpp`

### 4. MouseEventHandler
- **Purpose**: Manages resizing events after context menu selection.
- **Key Functions**:
  - `eventFilter()`: Handles mouse move/release for resizing.
- **Files**: `mouseeventhandler.h`, `mouseeventhandler.cpp`

### 5. ImageResizer
- **Purpose**: Resizes images in the scene when triggered.
- **Key Functions**:
  - `startResizing(QUrl, QGraphicsPixmapItem*, QPoint)`: Begins resizing process.
  - `updateResizing(QPoint)`: Adjusts image size during drag.
  - `finishResizing()`: Completes resizing.
- **Files**: `imageresizer.h`, `imageresizer.cpp`

### 6. ImageSelector
- **Purpose**: Detects if an image is selected at a given position.
- **Key Functions**:
  - `selectImage(QPoint)`: Returns the URL of the image at the point.
  - `isImageSelected()`: Checks if an image is selected.
- **Files**: `imageselector.h`, `imageselector.cpp`

### 7. FileDialog
- **Purpose**: Provides a file dialog for importing/exporting files.
- **Key Functions**:
  - `getSelectedFile()`: Returns the chosen file path.
- **Files**: `filedialog.h`, `filedialog.cpp`

### 8. ImagePlaceholder
- **Purpose**: Wraps image data with a URL for scene management.
- **Key Functions**:
  - `getUrl()`: Returns the placeholder URL.
  - `getImage()`: Returns the QImage.
  - `isValid()`: Checks if the image loaded correctly.
- **Files**: `imageplaceholder.h`, `imageplaceholder.cpp`

### 9. ContextMenuHandler (New)
- **Purpose**: Manages the right-click context menu and triggers actions like resizing.
- **Key Functions**:
  - `showContextMenu(QContextMenuEvent*)`: Displays the menu and handles selections.
- **Files**: `contextmenuhandler.h`, `contextmenuhandler.cpp`

## Notes
- **Current Features**: Image insertion (menu), dragging (left-click).
- **Pending Fixes**: Right-click resizing via context menu not fully triggering.
- **Future Potential**: Toolbar icons, multi-image handling, undo/redo.
