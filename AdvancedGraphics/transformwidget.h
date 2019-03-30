#ifndef TRANSFORMWIDGET_H
#define TRANSFORMWIDGET_H

#include <QWidget>

namespace Ui {
class TransformWidget;
}
class GameObject;
class TransformWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TransformWidget(QWidget *parent = nullptr);
    ~TransformWidget();
    void TransformModified();

    void UpdateUIValues(GameObject* new_GO);
private:
    Ui::TransformWidget *ui;
    GameObject* activeGO;
};

#endif // TRANSFORMWIDGET_H
