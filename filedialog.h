#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QDialog>

class QLineEdit;
class QPushButton;

class FileDialog : public QDialog {
    Q_OBJECT
public:
    enum FileMode { Import, Export };
    explicit FileDialog(QWidget *parent = nullptr);
    void configureForMode(FileMode mode);
    QString getSelectedFile();

private:
    FileMode mode;
    QString selectedFile;
    QLineEdit *fileInput;
    QPushButton *okButton;
};

#endif // FILEDIALOG_H
