#ifndef MENUMANAGERBRICK_H
#define MENUMANAGERBRICK_H

#include <QObject>
#include <QMenuBar>

class QAction;

class MenuManagerBrick : public QObject {
    Q_OBJECT
public:
    explicit MenuManagerBrick(QWidget *parent = nullptr);
    ~MenuManagerBrick();
    void setupMenus(QAction *openAction, QAction *saveAction,
                    QAction *boldAction, QAction *italicAction, QAction *fontAction,
                    QAction *colorAction, QAction *imageAction, QAction *alignLeftAction,
                    QAction *alignCenterAction, QAction *alignRightAction,
                    QAction *numberingAction, QAction *bulletsAction); // Added actions
    QMenuBar* getMenuBar() const;

signals:
    void newFileTriggered(int type);
    void saveAsTriggered();
    void numberingTriggered();  // New signal
    void bulletsTriggered();    // New signal

private:
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
};

#endif // MENUMANAGERBRICK_H
