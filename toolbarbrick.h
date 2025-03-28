#ifndef TOOLBARBRICK_H
#define TOOLBARBRICK_H

#include <QObject>
#include <QToolBar>
#include <QAction>

class ToolBarBrick : public QObject {
    Q_OBJECT
public:
    explicit ToolBarBrick(QWidget *parent = nullptr);
    QToolBar* getToolBar() const;
    QAction* getAction(const QString &name) const;
    QAction* addAction(const QString &name, const QString &text, const QString &iconPath);

private:
    QToolBar *toolBar;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *boldAction;
    QAction *italicAction;
    QAction *fontAction;
    QAction *colorAction;
    QAction *imageAction;
    QAction *alignLeftAction;
    QAction *alignCenterAction;
    QAction *alignRightAction;
    QAction *tableAction; // Added table action
};

#endif // TOOLBARBRICK_H
