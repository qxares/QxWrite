QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

SOURCES += \
    boldbrick.cpp \
    colorbrick.cpp \
    dialogbrick.cpp \
    fontbrick.cpp \
    iconbrick.cpp \
    insertbrick.cpp \
    italicbrick.cpp \
    main.cpp \
    mainwindowbrick.cpp \
    menumanagerbrick.cpp \
    newfilebrick.cpp \
    openfilebrick.cpp \
    savefunctionbrick.cpp \
    saveguibrick.cpp \
    savehandlerbrick.cpp \
    savemanagerbrick.cpp \
    toolbarbrick.cpp \
    alignbrick.cpp  # Added

HEADERS += \
    boldbrick.h \
    colorbrick.h \
    dialogbrick.h \
    fontbrick.h \
    iconbrick.h \
    insertbrick.h \
    italicbrick.h \
    mainwindowbrick.h \
    menumanagerbrick.h \
    newfilebrick.h \
    openfilebrick.h \
    savefunctionbrick.h \
    saveguibrick.h \
    savehandlerbrick.h \
    savemanagerbrick.h \
    toolbarbrick.h \
    alignbrick.h  # Added

RESOURCES += \
    icons.qrc
