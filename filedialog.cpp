#include "filedialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>

FileDialog::FileDialog(QWidget *parent) 
    : QDialog(parent), mode(Import), selectedFile("") {
    QVBoxLayout *layout = new QVBoxLayout(this);
    fileInput = new QLineEdit(this);
    okButton = new QPushButton(tr("OK"), this);
    layout->addWidget(fileInput);
    layout->addWidget(okButton);
    setLayout(layout);
    connect(okButton, &QPushButton::clicked, this, &FileDialog::accept);
}

void FileDialog::configureForMode(FileMode m) {
    mode = m;
    setWindowTitle(mode == Import ? tr("Import Image") : tr("Export Image"));
}

QString FileDialog::getSelectedFile() {
    exec();
    selectedFile = fileInput->text();
    qDebug() << "Selected file from dialog:" << selectedFile;
    return selectedFile;
}
