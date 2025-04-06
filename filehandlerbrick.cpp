#include "filehandlerbrick.h"
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QDir>

FileHandlerBrick::FileHandlerBrick(QObject *parent) 
    : QObject(parent), translator(new FileTranslatorBrick(nullptr, this)) {
    qDebug() << "FileHandlerBrick initialized";
}

bool FileHandlerBrick::handleExport(const QString &filePath, const QString &format, QTextEdit *textEdit) {
    qDebug() << "FileHandlerBrick: Handling export to:" << filePath << "format:" << format;

    // Create a temp file path in /tmp
    QString tempFilePath = "/tmp/qxwrite_export_temp." + format;
    translator->setTextEdit(textEdit);
    translator->exportFile(tempFilePath, format);

    if (!QFile::exists(tempFilePath)) {
        qDebug() << "FileHandlerBrick: Temp export failed, file missing at:" << tempFilePath;
        return false;
    }

    // Ensure the destination directory exists
    QFileInfo fileInfo(filePath);
    QDir dir = fileInfo.absoluteDir();
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qDebug() << "FileHandlerBrick: Failed to create directory:" << dir.absolutePath();
            QFile::remove(tempFilePath);
            return false;
        }
    }

    // Move the temp file to the final destination
    if (QFile::exists(filePath)) {
        QFile::remove(filePath);  // Remove existing file if any
    }
    if (!QFile::rename(tempFilePath, filePath)) {
        qDebug() << "FileHandlerBrick: Failed to move temp file from" << tempFilePath << "to" << filePath;
        QFile::remove(tempFilePath);
        return false;
    }

    if (QFile::exists(filePath)) {
        qDebug() << "FileHandlerBrick: Export confirmed at:" << filePath;
        return true;
    } else {
        qDebug() << "FileHandlerBrick: Export failed, file missing at:" << filePath;
        return false;
    }
}
