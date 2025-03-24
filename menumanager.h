#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <QObject>
#include <QMenuBar>

class QAction;
class QWidget;

class MenuManager : public QObject {
    Q_OBJECT
public:
    MenuManager(QMenuBar *menuBar, QWidget *parent = nullptr);
    void addFileMenu();
    QMenu* addCustomMenu(const QString &title, const QList<QAction*> &actions);
    QMenu* getCustomMenu(const QString &title);

signals:
    void newFileRequested();
    void openFileRequested();
    void saveFileRequested();
    void quitRequested();

private:
    QMenuBar *menuBar;
};

#endif // MENUMANAGER_H
