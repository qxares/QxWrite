QT       += core gui widgets printsupport

TARGET = QxWrite
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindowbrick.cpp \
    insertbrick.cpp \
    savebrick.cpp \
    menumanagerbrick.cpp \
    boldbrick.cpp \
    newfilebrick.cpp \
    toolbarbrick.cpp \
    italicbrick.cpp \
    openfilebrick.cpp \
    iconbrick.cpp

HEADERS += \
    mainwindowbrick.h \
    insertbrick.h \
    savebrick.h \
    menumanagerbrick.h \
    boldbrick.h \
    newfilebrick.h \
    toolbarbrick.h \
    italicbrick.h \
    openfilebrick.h \
    iconbrick.h

RESOURCES += \
    icons.qrc
