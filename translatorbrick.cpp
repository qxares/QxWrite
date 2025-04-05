#include "translatorbrick.h"
#include <QProcess>
#include <QDebug>
#include <QMessageBox>
#include <QMap>

TranslatorBrick::TranslatorBrick(QTextEdit *textEdit, QObject *parent) 
    : QObject(parent), textEdit(textEdit), 
      sourceLanguageComboBox(new QComboBox()), 
      targetLanguageComboBox(new QComboBox()),
      resetBrick(new ResetBrick(this)) {
    qDebug() << "TranslatorBrick initialized, target edit:" << textEdit;
    populateLanguages();  // Populate both combo boxes
    connect(targetLanguageComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &TranslatorBrick::translateText);  // Trigger on target change
    connect(sourceLanguageComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &TranslatorBrick::translateText);  // Trigger on source change
}

TranslatorBrick::~TranslatorBrick() {
    delete sourceLanguageComboBox;
    delete targetLanguageComboBox;
    delete resetBrick;
    qDebug() << "TranslatorBrick destroyed";
}

void TranslatorBrick::setTextEdit(QTextEdit *edit) {
    textEdit = edit;
    qDebug() << "TranslatorBrick: TextEdit set to:" << textEdit;
}

void TranslatorBrick::populateLanguages() {
    QProcess process;
    process.start("trans", QStringList() << "-R");  // Get reference languages
    if (!process.waitForFinished(5000)) {
        qDebug() << "TranslatorBrick: Failed to fetch languages:" << process.errorString();
        QMessageBox::warning(nullptr, "Language Fetch Failed", 
                             "Could not retrieve language list.\nEnsure 'translate-shell' is installed (sudo apt install translate-shell).");
    }

    QString output = process.readAllStandardOutput();
    QStringList lines = output.split('\n', Qt::SkipEmptyParts);
    sourceLanguageComboBox->clear();  // Clear existing items
    targetLanguageComboBox->clear();  // Clear existing items

    QMap<QString, QString> languageMap;  // Name -> Code for sorting
    for (const QString &line : lines) {
        if (line.contains("┌") || line.contains("└")) {
            continue;
        }

        QString mutableLine = line;
        QString cleanedLine = mutableLine
            .replace(QRegExp("\\x1B\\[[0-9;]*[mK]"), "")
            .trimmed();

        QStringList segments = cleanedLine.split("│", Qt::SkipEmptyParts);
        for (const QString &segment : segments) {
            QString trimmedSegment = segment.trimmed();
            if (trimmedSegment.isEmpty()) {
                continue;
            }

            QStringList parts = trimmedSegment.split(QRegExp("\\s+-\\s+"), Qt::SkipEmptyParts);
            if (parts.size() >= 2) {
                QString code = parts.last().trimmed();
                QString name = parts.mid(0, parts.size() - 1).join(" ").trimmed();
                if (!name.isEmpty() && !code.isEmpty()) {
                    languageMap[name + " (" + code + ")"] = code;
                }
            }
        }
    }

    QStringList sortedNames = languageMap.keys();
    sortedNames.sort(Qt::CaseInsensitive);
    for (const QString &name : sortedNames) {
        QString code = languageMap[name];
        sourceLanguageComboBox->addItem(name, code);
        targetLanguageComboBox->addItem(name, code);
    }

    if (targetLanguageComboBox->count() == 0) {
        qDebug() << "TranslatorBrick: No languages from trans, adding fallback options";
        sourceLanguageComboBox->addItem("Spanish (es)", "es");
        sourceLanguageComboBox->addItem("French (fr)", "fr");
        sourceLanguageComboBox->addItem("German (de)", "de");
        targetLanguageComboBox->addItem("Spanish (es)", "es");
        targetLanguageComboBox->addItem("French (fr)", "fr");
        targetLanguageComboBox->addItem("German (de)", "de");
    }

    sourceLanguageComboBox->setCurrentText("English (en)");
    targetLanguageComboBox->setCurrentText("Spanish (es)");
    qDebug() << "TranslatorBrick: Populated" << targetLanguageComboBox->count() << "languages";
}

QComboBox* TranslatorBrick::getSourceLanguageComboBox() const {
    return sourceLanguageComboBox;
}

QComboBox* TranslatorBrick::getTargetLanguageComboBox() const {
    return targetLanguageComboBox;
}

void TranslatorBrick::translateText() {
    if (!textEdit) {
        qDebug() << "TranslatorBrick: No text edit set!";
        return;
    }

    QTextCursor cursor = textEdit->textCursor();
    QString selectedText = cursor.selectedText();
    
    if (selectedText.isEmpty()) {
        cursor.select(QTextCursor::Document);
        selectedText = cursor.selectedText();
        if (selectedText.isEmpty()) {
            qDebug() << "TranslatorBrick: No text available to translate";
            return;
        }
        qDebug() << "TranslatorBrick: Selected all text for translation:" << selectedText;
    }

    QString targetLang = targetLanguageComboBox->currentData().toString();
    QStringList args;
    args << "-b" << "--no-cache" << (":" + targetLang) << selectedText;  // Always auto-detect source
    qDebug() << "TranslatorBrick: Translation args:" << args;

    QProcess *process = new QProcess(this);
    process->start("trans", args);

    if (!process->waitForFinished(5000)) {
        qDebug() << "TranslatorBrick: Translation failed:" << process->errorString();
        QMessageBox::warning(nullptr, "Translation Failed", 
                             "Translation process timed out or failed.\nEnsure 'translate-shell' is installed.");
        resetBrick->resetProcess(process);
        delete process;
        return;
    }

    if (process->exitCode() != 0) {
        qDebug() << "TranslatorBrick: Translation error:" << process->readAllStandardError();
        QMessageBox::warning(nullptr, "Translation Failed", 
                             "Translation error: " + process->readAllStandardError());
        resetBrick->resetProcess(process);
        delete process;
        return;
    }

    QString rawOutput = process->readAllStandardOutput();
    QStringList outputLines = rawOutput.split('\n', Qt::SkipEmptyParts);
    QString translatedText;
    for (const QString &line : outputLines) {
        QString mutableLine = line;  // Make a mutable copy
        QString trimmedLine = mutableLine.replace(QRegExp("\\x1B\\[[0-9;]*[mK]"), "").trimmed();
        if (!trimmedLine.isEmpty()) {
            translatedText = trimmedLine;  // Last non-empty line is the translation
        }
    }
    
    cursor.beginEditBlock();  // Group edits for cleaner undo
    cursor.removeSelectedText();
    cursor.insertText(translatedText);
    cursor.endEditBlock();
    cursor.setPosition(cursor.position(), QTextCursor::KeepAnchor);
    textEdit->setTextCursor(cursor);
    
    qDebug() << "TranslatorBrick: Translated text inserted:" << translatedText;

    resetBrick->resetProcess(process);
    delete process;
}

void TranslatorBrick::resetTranslation() {
    if (textEdit) {
        textEdit->clear();
        qDebug() << "TranslatorBrick: Text cleared";
    }
    sourceLanguageComboBox->setCurrentText("English (en)");
    targetLanguageComboBox->setCurrentText("Spanish (es)");
    qDebug() << "TranslatorBrick: Reset to English -> Spanish";
}
