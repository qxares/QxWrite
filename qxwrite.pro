QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

SOURCES += \
    boldbrick.cpp \
    colorbrick.cpp \
    dialogbrick.cpp \
    documentwindow.cpp \  # Added for new architecture
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
    alignbrick.cpp

HEADERS += \
    boldbrick.h \
    colorbrick.h \
    dialogbrick.h \
    documentwindow.h \    # Added for new architecture
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
    alignbrick.h

RESOURCES += \
    icons.qrc
