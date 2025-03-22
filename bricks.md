# QxWrite Bricks

## Overview
QxWrite is built with modular "bricks"—classes handling specific editor features. Each brick ties into the Qt framework for a tight, functional text editor.

## ToolBarBrick
- **Purpose:** Manages the toolbar with actions for file ops, formatting, and extras.
- **Constructor:** `ToolBarBrick(QToolBar *toolBar, QTextEdit *edit, InsertBrick *insert, SaveBrick *save, BoldBrick *bold, NewFileBrick *newFile, ItalicBrick *italic, OpenFileBrick *openFile, IconBrick *icon, FontBrick *font, ColorBrick *color, QObject *parent = nullptr)`
  - Takes a `QToolBar`, `QTextEdit`, and pointers to all feature bricks, plus an optional parent.
- **Key Methods:**
  - `setupToolBar()`: Adds actions (new, open, save, bold, italic, font, color, image) with icons from `IconBrick::loadIcon()`, connects them to brick methods.
  - `updateToggleStates()`: Syncs bold/italic toggle states with the `QTextEdit`’s current format.
- **Features:**
  - New/Open/Save: Tied to `NewFileBrick`, `OpenFileBrick`, `SaveBrick`.
  - Bold/Italic: Toggles via `BoldBrick`, `ItalicBrick`, checkable actions.
  - Font/Color: Dialogs via `FontBrick`, `ColorBrick`.
  - Image: Inserts via `InsertBrick`.
- **Status:** Fully functional—icons load, actions trigger, toggles sync. Clean build achieved March 22, 2025.

## Other Bricks
- **InsertBrick:** Handles image insertion.
- **SaveBrick:** Manages file saving.
- **BoldBrick:** Toggles bold formatting.
- **NewFileBrick:** Creates new files.
- **ItalicBrick:** Toggles italic formatting.
- **OpenFileBrick:** Opens existing files.
- **IconBrick:** Loads SVG icons (e.g., `loadIcon("new")`).
- **FontBrick:** Shows font dialog, applies fonts.
- **ColorBrick:** Shows color dialog, applies colors.

## Notes
- Built with Qt5 on Linux (x86_64).
- Debug output via `qDebug()` tracks init and state changes.
- Next steps: Add features, refine UI, optimize.
