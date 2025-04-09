#ifndef PANDOCFILEBRICK_H
#define PANDOCFILEBRICK_H

#include <QObject>
#include <QString>

class PandocHandlerBrick : public QObject {
    Q_OBJECT
public:
    explicit PandocHandlerBrick(QObject *parent = nullptr);
    QString convertToHtml(const QString &inputFile, const QString &format);
    bool convertFromHtml(const QString &htmlFile, const QString &outputFile, const QString &format);
};

#endif // PANDOCFILEBRICK_H
