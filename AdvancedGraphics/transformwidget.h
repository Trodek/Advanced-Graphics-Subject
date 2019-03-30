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

public slots:
    void TransformModified();

    void UpdateUIValues();
private slots:
    void on_PosX_valueChanged(double arg1);

    void on_PosY_valueChanged(double arg1);

    void on_ScaleX_valueChanged(double arg1);

    void on_ScaleY_valueChanged(double arg1);

private:
    Ui::TransformWidget *ui;
};

#endif // TRANSFORMWIDGET_H
