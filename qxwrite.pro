QT       += core gui widgets printsupport

TARGET = QxWrite
TEMPLATE = app

SOURCES += main.cpp \
           qxwrite.cpp \
           documenteditor.cpp \
           filedialog.cpp \
           imageplaceholder.cpp \
           imageselector.cpp \
           imagepositioner.cpp \
           imageresizer.cpp

HEADERS += qxwrite.h \
           documenteditor.h \
           filedialog.h \
           imageplaceholder.h \
           imageselector.h \
           imagepositioner.h \
           imageresizer.h
