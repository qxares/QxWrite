#include "exportbrick.h"
#include "htmlfilebrick.h"
#include "docxfilebrick.h"
#include "odtfilebrick.h"
#include <QTextEdit>
#include <QDebug>
#include <QFile>
#include <QApplication>
#include <QDir>

ExportBrick::ExportBrick(QTextEdit *edit, QObject *parent) 
    : QObject(parent), 
      m_textEdit(edit), 
      guiBrick(new ExportGUIBrick(this)),
      htmlBrick(new HtmlFileBrick(edit, this)),
      docxBrick(new DocxFileBrick(edit, this)),
      odtBrick(new OdtFileBrick(edit, this)) {
    qDebug() << "ExportBrick initialized, target edit:" << m_textEdit;
}

void ExportBrick::setTextEdit(QTextEdit *edit) {
    m_textEdit = edit;
    htmlBrick->setTextEdit(edit);
    docxBrick->setTextEdit(edit);
    odtBrick->setTextEdit(edit);
    qDebug() << "ExportBrick: TextEdit updated to:" << m_textEdit;
}

void ExportBrick::exportFile() {
    if (!m_textEdit) {
        qDebug() << "ExportBrick: No text edit set, cannot export";
        return;
    }

    QString fileName;
    QString format;
    if (!guiBrick->getExportDetails(fileName, format)) {
        qDebug() << "ExportBrick: No file selected or dialog cancelled";
        return;
    }

    QFileInfo fileInfo(fileName);
    QString absoluteFilePath = fileInfo.absoluteFilePath();
    if (!fileName.startsWith("/home/ares/test/")) {
        absoluteFilePath = "/home/ares/test/" + fileInfo.fileName();
    }
    qDebug() << "ExportBrick: Exporting to absolute path:" << absoluteFilePath << "with format:" << format;

    QApplication::setOverrideCursor(Qt::WaitCursor);
    bool success = false;
    if (format == "html") {
        htmlBrick->exportFile(absoluteFilePath);
        success = QFile::exists(absoluteFilePath);
    } else if (format == "docx") {
        docxBrick->exportFile(absoluteFilePath);
        success = QFile::exists(absoluteFilePath);
    } else if (format == "odt") {
        odtBrick->exportFile(absoluteFilePath);
        success = QFile::exists(absoluteFilePath);
    }
    QApplication::restoreOverrideCursor();

    if (success) {
        m_textEdit->document()->setModified(false);
        qDebug() << "ExportBrick: Successfully exported to:" << absoluteFilePath;
    } else {
        qDebug() << "ExportBrick: Export failed, file not found at:" << absoluteFilePath;
    }
}
