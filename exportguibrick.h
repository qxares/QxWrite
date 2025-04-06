#ifndef EXPORTGUIBRICK_H
#define EXPORTGUIBRICK_H

#include <QObject>
#include <QString>

class ExportGUIBrick : public QObject {
    Q_OBJECT
public:
    explicit ExportGUIBrick(QObject *parent = nullptr);
    bool getExportDetails(QString &fileName, QString &format);

private:
    QString lastDir;
};

#endif // EXPORTGUIBRICK_H
