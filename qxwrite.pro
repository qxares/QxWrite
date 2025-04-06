# qxwrite.pro
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
    documenthandlerbrick.cpp \
    documentwindow.cpp \
    exportbrick.cpp \
    exportguibrick.cpp \
    filehandlerbrick.cpp \
    filetranslatorbrick.cpp \
    fontbrick.cpp \
    importbrick.cpp \
    insertbrick.cpp \
    italicbrick.cpp \
    main.cpp \
    mainwindowbrick.cpp \
    menumanagerbrick.cpp \
    newfilebrick.cpp \
    openfilebrick.cpp \
    resetbrick.cpp \
    resizebrick.cpp \
    savefunctionbrick.cpp \
    saveguibrick.cpp \
    savehandlerbrick.cpp \
    savemanagerbrick.cpp \
    toolbarbrick.cpp \
    translatorbrick.cpp

HEADERS += \
    alignbrick.h \
    boldbrick.h \
    colorbrick.h \
    dialogbrick.h \
    documenthandlerbrick.h \
    documentwindow.h \
    exportbrick.h \
    exportguibrick.h \
    filehandlerbrick.h \
    filetranslatorbrick.h \
    fontbrick.h \
    importbrick.h \
    insertbrick.h \
    italicbrick.h \
    mainwindowbrick.h \
    menumanagerbrick.h \
    newfilebrick.h \
    openfilebrick.h \
    resetbrick.h \
    resizebrick.h \
    savefunctionbrick.h \
    saveguibrick.h \
    savehandlerbrick.h \
    savemanagerbrick.h \
    toolbarbrick.h \
    translatorbrick.h

RESOURCES += \
    icons.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Debug config
CONFIG(debug, debug|release) {
    DEFINES += QT_DEBUG
}
