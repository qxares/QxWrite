#ifndef TOOLBARBRICK_H
#define TOOLBARBRICK_H

#include <QObject>
#include <QToolBar>
#include <QAction>
#include <QMap>

class ToolBarBrick : public QObject {
    Q_OBJECT
public:
    explicit ToolBarBrick(QWidget *parent = nullptr);
    QToolBar* getToolBar() const;
    QAction* getAction(const QString &name) const;
    void addToolBarAction(const QString &name, const QString &text, const QString &iconPath);

private:
    QToolBar *toolBar;
    QMap<QString, QAction*> actions;  // Store all actions in a map
};

#endif // TOOLBARBRICK_H
