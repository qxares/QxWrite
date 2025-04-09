#include "htmlfilebrick.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QRegularExpression>

HtmlFileBrick::HtmlFileBrick(QTextEdit *textEdit, QObject *parent)
    : QObject(parent), textEdit(textEdit) {
    qDebug() << "HtmlFileBrick initialized, target edit:" << textEdit;
}

void HtmlFileBrick::setTextEdit(QTextEdit *edit) {
    textEdit = edit;
    qDebug() << "HtmlFileBrick: TextEdit set to:" << textEdit;
}

QString HtmlFileBrick::importFile(const QString &filePath) {
    if (!textEdit) {
        qDebug() << "HtmlFileBrick: No text edit set!";
        QMessageBox::warning(nullptr, "Import Error", "No active document to import into.");
        return "";
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "HtmlFileBrick: Failed to open html:" << filePath;
        QMessageBox::warning(nullptr, "Import Failed", "Couldn’t open " + filePath);
        return "";
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    QRegularExpression bodyStartRegex("<body[^>]*>", QRegularExpression::CaseInsensitiveOption);
    QRegularExpression bodyEndRegex("</body>", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch bodyStartMatch = bodyStartRegex.match(content);
    QRegularExpressionMatch bodyEndMatch = bodyEndRegex.match(content);
    if (bodyStartMatch.hasMatch() && bodyEndMatch.hasMatch()) {
        int bodyStart = bodyStartMatch.capturedEnd();
        int bodyEnd = bodyEndMatch.capturedStart();
        content = content.mid(bodyStart, bodyEnd - bodyStart).trimmed();
    } else {
        qDebug() << "HtmlFileBrick: No <body> tags found, using raw content";
        content = content.trimmed();
    }

    textEdit->setHtml(content);
    qDebug() << "HtmlFileBrick: Imported html:" << filePath;
    return content;
}

void HtmlFileBrick::exportFile(const QString &filePath) {
    if (!textEdit) {
        qDebug() << "HtmlFileBrick: No text edit set!";
        QMessageBox::critical(nullptr, "Export Error", "No active document to export from.");
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "HtmlFileBrick: Failed to write html:" << filePath;
        QMessageBox::critical(nullptr, "Export Error", "Failed to write " + filePath);
        return;
    }

    QString htmlContent = textEdit->toHtml();
    QRegularExpression qtStyleRegex("style=\"-qt-[^\"]*\"", QRegularExpression::CaseInsensitiveOption);
    htmlContent.remove(qtStyleRegex);
    QRegularExpression paraStyleRegex("<p[^>]*style=\"([^\"]*?)\"[^>]*>", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatchIterator paraIter = paraStyleRegex.globalMatch(htmlContent);
    QString newHtmlContent;
    int lastPos = 0;
    while (paraIter.hasNext()) {
        QRegularExpressionMatch match = paraIter.next();
        int start = match.capturedStart();
        int end = match.capturedEnd();
        QString style = match.captured(1);

        newHtmlContent += htmlContent.mid(lastPos, start - lastPos);
        QString alignStyle = "margin: 0; line-height: 1em;";
        if (style.contains("text-align: center")) {
            alignStyle += " text-align: center;";
        } else if (style.contains("text-align: right")) {
            alignStyle += " text-align: right;";
        } else {
            alignStyle += " text-align: left;";
        }
        newHtmlContent += "<p style=\"" + alignStyle + "\">";
        lastPos = end;
    }
    newHtmlContent += htmlContent.mid(lastPos);
    htmlContent = newHtmlContent;

    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"><style>body { font-family: Ubuntu, sans-serif; margin: 1em; } p { margin: 0; line-height: 1em; }</style></head><body>" << htmlContent << "</body></html>";
    file.close();
    qDebug() << "HtmlFileBrick: Exported html to:" << filePath;
}
