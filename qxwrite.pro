QT       += core gui widgets printsupport

TARGET = qxwrite
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindowbrick.cpp \
    toolbarbrick.cpp \
    menumanagerbrick.cpp \
    newfilebrick.cpp \
    openfilebrick.cpp \
    savemanagerbrick.cpp \
    boldbrick.cpp \
    italicbrick.cpp \
    fontbrick.cpp \
    colorbrick.cpp \
    insertbrick.cpp \
    alignbrick.cpp \
    dialogbrick.cpp \
    documentwindow.cpp \
    savefunctionbrick.cpp \
    saveguibrick.cpp \
    savehandlerbrick.cpp \
    iconbrick.cpp

HEADERS += \
    mainwindowbrick.h \
    toolbarbrick.h \
    menumanagerbrick.h \
    newfilebrick.h \
    openfilebrick.h \
    savemanagerbrick.h \
    boldbrick.h \
    italicbrick.h \
    fontbrick.h \
    colorbrick.h \
    insertbrick.h \
    alignbrick.h \
    dialogbrick.h \
    documentwindow.h \
    savefunctionbrick.h \
    saveguibrick.h \
    savehandlerbrick.h \
    iconbrick.h

RESOURCES += \
    icons.qrc
