#include "filedialog.h"

FileDialog::FileDialog(QWidget *parent, const QString &initialDir, Mode mode)
    : QFileDialog(parent, "File Dialog", initialDir) {
    configureForMode(mode);
    setOption(QFileDialog::DontUseNativeDialog, true);
}

void FileDialog::configureForMode(Mode mode) {
    switch (mode) {
        case Open:
            setFileMode(QFileDialog::ExistingFile);
            setAcceptMode(QFileDialog::AcceptOpen);
            break;
        case Save:
            setFileMode(QFileDialog::AnyFile);
            setAcceptMode(QFileDialog::AcceptSave);
            break;
        case Import:
            setFileMode(QFileDialog::ExistingFile);
            setAcceptMode(QFileDialog::AcceptOpen);
            setNameFilter("Images (*.png *.jpg *.bmp)");
            break;
        case Export:
            setFileMode(QFileDialog::AnyFile);
            setAcceptMode(QFileDialog::AcceptSave);
            setNameFilter("Images (*.png *.jpg)");
            break;
    }
}

QString FileDialog::getSelectedFile() const {
    return selectedFiles().value(0, QString());
}
