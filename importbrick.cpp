#include "importbrick.h"
#include "dialogbrick.h"
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QDebug>

ImportBrick::ImportBrick(QTextEdit *textEdit, QObject *parent) : QObject(parent), textEdit(textEdit) {
    qDebug() << "ImportBrick initialized, target edit:" << textEdit;
}

void ImportBrick::setTextEdit(QTextEdit *edit) {
    textEdit = edit;
    qDebug() << "ImportBrick: TextEdit set to:" << textEdit;
}

void ImportBrick::importFile() {
    if (!textEdit) {
        qDebug() << "ImportBrick: No text edit set!";
        return;
    }

    DialogBrick dialog(this);
    QString fileName = dialog.getOpenFileName(nullptr, "Import File", "", "Text Files (*.txt *.html);;All Files (*)");
    if (fileName.isEmpty()) {
        qDebug() << "ImportBrick: No file selected";
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "ImportBrick: Failed to open file:" << fileName;
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    textEdit->setHtml(content);  // Assuming HTML import; adjust if plain text
    qDebug() << "ImportBrick: Imported file:" << fileName;
}
