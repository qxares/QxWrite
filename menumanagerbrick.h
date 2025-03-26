#ifndef MENUMANAGERBRICK_H
#define MENUMANAGERBRICK_H

#include <QObject>
#include <QMenuBar>
#include <QAction>

class QMenu;

class MenuManagerBrick : public QObject {
    Q_OBJECT
public:
    explicit MenuManagerBrick(QWidget *parent = nullptr);
    ~MenuManagerBrick();
    void setupMenus(QAction *newAction, QAction *openAction, QAction *saveAction,
                    QAction *boldAction, QAction *italicAction, QAction *fontAction,
                    QAction *colorAction, QAction *imageAction, QAction *alignLeftAction,
                    QAction *alignCenterAction, QAction *alignRightAction);
    QMenuBar* getMenuBar() const;

Q_SIGNALS:
    void newFileTriggered(int type);

private:
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
};

#endif // MENUMANAGERBRICK_H
