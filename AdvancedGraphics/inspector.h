#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>
#include "component.h"

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

public slots:
   void OnSelectedGoChange();

private:
   void AddComponentUI(Component::Type type);

signals:
    void UpdateName();

private slots:
    void on_AddComponent_clicked();

private:
    Ui::Inspector* ui;
};

#endif // INSPECTOR_H
