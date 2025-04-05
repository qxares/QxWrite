#ifndef TRANSLATORBRICK_H
#define TRANSLATORBRICK_H

#include <QObject>
#include <QTextEdit>
#include <QComboBox>
#include "resetbrick.h"

class TranslatorBrick : public QObject {
    Q_OBJECT
public:
    explicit TranslatorBrick(QTextEdit *textEdit, QObject *parent = nullptr);
    ~TranslatorBrick();  // Destructor to clean up
    void setTextEdit(QTextEdit *edit);
    QComboBox* getSourceLanguageComboBox() const;  // Access to source combo box
    QComboBox* getTargetLanguageComboBox() const;  // Renamed for clarity
    void populateLanguages();  // Fetch and populate available languages

public slots:
    void translateText();
    void resetTranslation();  // Added to reset to neutral state

private:
    QTextEdit *textEdit;
    QComboBox *sourceLanguageComboBox;  // Dropdown for source language
    QComboBox *targetLanguageComboBox;  // Dropdown for target language
    ResetBrick *resetBrick;  // Reusable reset logic
};

#endif // TRANSLATORBRICK_H
