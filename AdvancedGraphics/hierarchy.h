#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <QWidget>

namespace Ui {
class HierarchyDock;
}

class Hierarchy : public QWidget
{
    Q_OBJECT

public:
    explicit Hierarchy(QWidget *parent = 0);
    ~Hierarchy();
public slots:
    void AddGameObject();
    void DeleteGameObject();

    void NewScene();

signals:
    void UpdateInspector();

private:
    Ui::HierarchyDock *ui;
};

#endif // HIERARCHY_H
