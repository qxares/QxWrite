#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QFileDialog>
#include <QString>

class FileDialog : public QFileDialog {
    Q_OBJECT
public:
    enum Mode { Open, Save, Import, Export };
    explicit FileDialog(QWidget *parent, const QString &initialDir = QDir::homePath(), Mode mode = Open);
    QString getSelectedFile() const;

private:
    void configureForMode(Mode mode);
};

#endif // FILEDIALOG_H
