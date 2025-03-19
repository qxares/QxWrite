#ifndef QXWRITE_H
#define QXWRITE_H

#include <QMainWindow>
#include <QMdiArea>

class QxWrite : public QMainWindow {
    Q_OBJECT
public:
    QxWrite(QWidget *parent = nullptr);

private slots:
    void newDocument();

private:
    QMdiArea *mdiArea;
    void setupMenus();
};

#endif // QXWRITE_H
