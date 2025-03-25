#ifndef MENUMANAGERBRICK_H
#define MENUMANAGERBRICK_H

#include <QObject>
#include <QMenuBar>
#include <QAction>

class MenuManagerBrick : public QObject {
    Q_OBJECT
public:
    explicit MenuManagerBrick(QWidget *parent = nullptr);
    void setupMenus(QAction *newAction, QAction *openAction, QAction *saveAction,
                    QAction *boldAction, QAction *italicAction, QAction *fontAction,
                    QAction *colorAction, QAction *imageAction, QAction *alignLeftAction,
                    QAction *alignCenterAction, QAction *alignRightAction);
    QMenuBar* getMenuBar() const;

private:
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
};

#endif // MENUMANAGERBRICK_H
