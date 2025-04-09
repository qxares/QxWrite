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
                    QAction *tableAction = nullptr,
                    QAction *translateAction = nullptr);
    QMenuBar* getMenuBar() const;

signals:
    void newFileTriggered(int type);
    void saveAsTriggered();
    void importTriggered();
    void exportTriggered();
    void numberingTriggered();
    void bulletsTriggered();
    void insertImageTriggered();
    void insertTableTriggered();
    void insertRowAboveTriggered();
    void insertRowBelowTriggered();
    void insertColumnBeforeTriggered();
    void insertColumnAfterTriggered();
    void deleteRowTriggered();
    void deleteColumnTriggered();
    void mergeCellsTriggered();
    void splitCellsTriggered();
    void deleteTableTriggered();
    void alignTableLeftTriggered();
    void alignTableCenterTriggered();
    void alignTableRightTriggered();
    void moveTriggered();
    void exitTriggered();
    void translateTriggered();
    void aboutTriggered();

private:
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *tableMenu;
    QMenu *toolsMenu;
    QMenu *helpMenu;
};

#endif // MENUMANAGERBRICK_H
