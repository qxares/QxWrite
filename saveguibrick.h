#ifndef SAVEGUIBRICK_H
#define SAVEGUIBRICK_H

#include <QObject>
#include <QTextEdit>

class DialogBrick;

class SaveGUIBrick : public QObject {
    Q_OBJECT
public:
    explicit SaveGUIBrick(QTextEdit *edit, QObject *parent = nullptr);

public slots:
    void save(bool forcePrompt);  // Add this slot to handle save requests

signals:
    void fileSelected(const QString &filePath);  // Add this signal to emit the selected file path

private:
    QTextEdit *m_edit;
    DialogBrick *m_dialog;
    QString m_currentFilePath;  // Track the current file path
};

#endif // SAVEGUIBRICK_H
