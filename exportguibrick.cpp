#include "exportguibrick.h"
#include <QFileDialog>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QFileInfo>

ExportGUIBrick::ExportGUIBrick(QObject *parent) 
    : QObject(parent), lastDir("/home/ares") {
    qDebug() << "ExportGUIBrick initialized with lastDir:" << lastDir;
}

bool ExportGUIBrick::getExportDetails(QString &fileName, QString &format) {
    QFileDialog dialog(nullptr, "Export File", lastDir);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setOption(QFileDialog::DontUseNativeDialog, true);
    dialog.setWindowTitle("QxWrite Export");

    // Add logo
    QLabel *logoLabel = new QLabel(&dialog);
    QPixmap logo("/home/ares/Downloads/editor/QxWriteProject/icons/qxwrite-logo.png");
    if (!logo.isNull()) {
        logoLabel->setPixmap(logo.scaled(50, 50, Qt::KeepAspectRatio));
        QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(dialog.layout());
        if (layout) {
            layout->insertWidget(0, logoLabel);
        }
    } else {
        qDebug() << "ExportGUIBrick: Failed to load logo";
    }

    // Green borders vibe
    dialog.setStyleSheet("QFileDialog { border: 2px solid #00FF00; }");

    QString filter = "Text (*.txt);;HTML (*.html);;Word (*.docx);;OpenDocument (*.odt);;PDF (*.pdf);;All Files (*)";
    dialog.setNameFilter(filter);

    qDebug() << "ExportGUIBrick: Dialog opened with dir:" << lastDir << "filter:" << filter;

    if (dialog.exec() != QDialog::Accepted) {
        return false;
    }

    fileName = dialog.selectedFiles().first();
    QString selectedFilter = dialog.selectedNameFilter();

    if (selectedFilter.contains("*.txt")) format = "txt";
    else if (selectedFilter.contains("*.html")) format = "html";
    else if (selectedFilter.contains("*.docx")) format = "docx";
    else if (selectedFilter.contains("*.odt")) format = "odt";
    else if (selectedFilter.contains("*.pdf")) format = "pdf";
    else format = "txt"; // Default

    QFileInfo fileInfo(fileName);
    QString ext = fileInfo.suffix().toLower();
    if (ext.isEmpty() || ext != format) {
        fileName = fileInfo.completeBaseName() + "." + format;
    }

    lastDir = fileInfo.absolutePath();
    qDebug() << "ExportGUIBrick: Selected file:" << fileName << "format:" << format << "new lastDir:" << lastDir;
    return true;
}
