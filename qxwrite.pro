TARGET = QxWrite

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    alignbrick.cpp \
    boldbrick.cpp \
    colorbrick.cpp \
    dialogbrick.cpp \
    docxfilebrick.cpp \
    documenthandlerbrick.cpp \
    documentwindow.cpp \
    exportbrick.cpp \
    exportguibrick.cpp \
    filehandlerbrick.cpp \
    filetranslatorbrick.cpp \
    fontbrick.cpp \
    htmlfilebrick.cpp \
    importbrick.cpp \
    insertbrick.cpp \
    italicbrick.cpp \
    listbrick.cpp \
    main.cpp \
    mainwindowbrick.cpp \
    menumanagerbrick.cpp \
    newfilebrick.cpp \
    odtfilebrick.cpp \
    openfilebrick.cpp \
    pandocfilebrick.cpp \
    resetbrick.cpp \
    resizebrick.cpp \
    savefunctionbrick.cpp \
    saveguibrick.cpp \
    savehandlerbrick.cpp \
    savemanagerbrick.cpp \
    tablebrick.cpp \
    toolbarbrick.cpp \
    translatorbrick.cpp

HEADERS += \
    alignbrick.h \
    boldbrick.h \
    colorbrick.h \
    dialogbrick.h \
    docxfilebrick.h \
    documenthandlerbrick.h \
    documentwindow.h \
    exportbrick.h \
    exportguibrick.h \
    filehandlerbrick.h \
    filetranslatorbrick.h \
    fontbrick.h \
    htmlfilebrick.h \
    importbrick.h \
    insertbrick.h \
    italicbrick.h \
    listbrick.h \
    mainwindowbrick.h \
    menumanagerbrick.h \
    newfilebrick.h \
    odtfilebrick.h \
    openfilebrick.h \
    pandocfilebrick.h \
    resetbrick.h \
    resizebrick.h \
    savefunctionbrick.h \
    saveguibrick.h \
    savehandlerbrick.h \
    savemanagerbrick.h \
    tablebrick.h \
    toolbarbrick.h \
    translatorbrick.h

# Assuming icons.qrc exists for your icons
RESOURCES += \
    icons.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
