#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>


namespace Ui {
class Inspector;
}
class GameObject;
class TransformWidget;
class Inspector : public QWidget
{
    Q_OBJECT
 public:
   TransformWidget *m_TransformWidget;
public:
    explicit Inspector(QWidget *parent = nullptr);
    ~Inspector();
    void SetNewGameObject(GameObject* new_go);
public:
    GameObject *m_ActiveGameObject;

private:
    Ui::Inspector* ui;
};

#endif // INSPECTOR_H
