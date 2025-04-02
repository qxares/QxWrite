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
                    QAction *numberingAction, QAction *bulletsAction,
                    QAction *tableAction = nullptr);
    QMenuBar* getMenuBar() const;

signals:
    void newFileTriggered(int type);
    void saveAsTriggered();
    void importTriggered();  // New signal
    void exportTriggered();  // New signal
    void numberingTriggered();
    void bulletsTriggered();
    void insertTableTriggered();
    void insertRowBeforeTriggered();
    void insertRowAfterTriggered();
    void insertRowAboveTriggered();
    void insertRowBelowTriggered();
    void insertColumnBeforeTriggered();
    void insertColumnAfterTriggered();
    void insertColumnAboveTriggered();
    void insertColumnBelowTriggered();
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

private:
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *tableMenu;
};

#endif // MENUMANAGERBRICK_H
