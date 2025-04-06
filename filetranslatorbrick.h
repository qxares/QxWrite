#ifndef FILETRANSLATORBRICK_H
#define FILETRANSLATORBRICK_H

#include <QObject>
#include <QTextEdit>
#include <QComboBox>

class FileTranslatorBrick : public QObject {
    Q_OBJECT
public:
    explicit FileTranslatorBrick(QTextEdit *textEdit, QObject *parent = nullptr);
    ~FileTranslatorBrick();
    void setTextEdit(QTextEdit *edit);
    QComboBox* getFormatComboBox() const;
    void populateFormats();

public slots:
    QString importFile(const QString &filePath);
    void exportFile(const QString &filePath, const QString &format);

private:
    QTextEdit *textEdit;
    QComboBox *formatComboBox;
    QString convertToHtml(const QString &inputFile, const QString &inputFormat);
    bool convertFromHtml(const QString &htmlFile, const QString &outputFile, const QString &outputFormat);
};

#endif // FILETRANSLATORBRICK_H
