#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>
class GameObject;
class TransformWidget;
class ShapeRendererWidget;
class Inspector : public QWidget
{
    Q_OBJECT
 public:
   TransformWidget *m_TransformWidget;
   ShapeRendererWidget *m_ShapeRendererWidget;
public:
    explicit Inspector(QWidget *parent = nullptr);
    ~Inspector();
    void SetNewGameObject(GameObject* new_go);
public:
    GameObject *m_ActiveGameObject;
};

#endif // INSPECTOR_H
