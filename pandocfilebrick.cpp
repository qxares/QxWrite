#include "pandocfilebrick.h"
#include <QProcess>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

PandocHandlerBrick::PandocHandlerBrick(QObject *parent)
    : QObject(parent) {
    qDebug() << "PandocHandlerBrick initialized";
}

QString PandocHandlerBrick::convertToHtml(const QString &inputFile, const QString &format) {
    QString tempHtml = "/tmp/qxwrite_pandoc_import_" + format + ".html";
    QProcess process;

    QStringList args = {
        "--headless",
        "--convert-to", "html",
        inputFile,
        "--outdir", "/tmp"
    };
    qDebug() << "PandocHandlerBrick: Running soffice command: soffice" << args.join(" ");
    process.start("soffice", args);

    if (!process.waitForFinished(15000) || process.exitCode() != 0) {
        qDebug() << "PandocHandlerBrick: soffice conversion failed:" << process.errorString()
                 << "Output:" << process.readAllStandardError();
        QFile::remove(tempHtml);
        return "";
    }

    QFileInfo inputFileInfo(inputFile);
    QString expectedHtml = "/tmp/" + inputFileInfo.baseName() + ".html";
    if (!QFile::exists(expectedHtml)) {
        qDebug() << "PandocHandlerBrick: HTML file not created by soffice:" << expectedHtml;
        QFile::remove(tempHtml);
        return "";
    }

    QFile file(expectedHtml);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "PandocHandlerBrick: Failed to read temp HTML:" << expectedHtml;
        QFile::remove(expectedHtml);
        return "";
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();
    QFile::remove(expectedHtml);

    // Inject CSS to enforce tight spacing and visible text
    QString styledContent = "<!DOCTYPE html><html><head><meta charset=\"UTF-8\">"
                            "<style>"
                            "body { font-family: 'Ubuntu', sans-serif; margin: 0; padding: 0; color: black; background: white; }"
                            "p { margin: 0; padding: 0; line-height: 1; color: black; }"
                            "div { margin: 0; padding: 0; }"
                            "b { font-weight: bold; }"
                            "i { font-style: italic; }"
                            "* { display: block; visibility: visible; }"
                            "</style></head><body>"
                            + content + "</body></html>";

    qDebug() << "PandocHandlerBrick: Converted to HTML with tight spacing:" << inputFile;
    return styledContent;
}

bool PandocHandlerBrick::convertFromHtml(const QString &htmlFile, const QString &outputFile, const QString &format) {
    QProcess process;
    QFileInfo fileInfo(outputFile);
    QString absoluteOutputFile = fileInfo.absoluteFilePath();
    qDebug() << "PandocHandlerBrick: Converting HTML to" << absoluteOutputFile;

    QStringList args = {
        "--standalone",
        "--from", "html",
        "-t", format,
        "--metadata", "margin-top=1em",
        "--metadata", "margin-bottom=1em",
        "--metadata", "fontfamily=Ubuntu",
        htmlFile,
        "-o", absoluteOutputFile
    };
    qDebug() << "PandocHandlerBrick: Running Pandoc command: pandoc" << args.join(" ");
    process.start("pandoc", args);

    if (!process.waitForFinished(15000)) {
        qDebug() << "PandocHandlerBrick: Pandoc export failed:" << process.errorString()
                 << "Output:" << process.readAllStandardError();
        QFile::remove(absoluteOutputFile);
        return false;
    }

    if (process.exitCode() != 0) {
        qDebug() << "PandocHandlerBrick: Pandoc export failed with exit code:" << process.exitCode();
        QFile::remove(absoluteOutputFile);
        return false;
    }

    if (!QFile::exists(absoluteOutputFile)) {
        qDebug() << "PandocHandlerBrick: Output file not created:" << absoluteOutputFile;
        return false;
    }
    return true;
}
