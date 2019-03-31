#ifndef SHAPERENDERERWIDGEt_H
#define SHAPERENDERERWIDGET_H

#include <QWidget>

namespace Ui {
class ShapeRendererWidget;
}
class GameObject;
class ShapeRenderer;
class ShapeRendererWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShapeRendererWidget(QWidget *parent = nullptr);
    ~ShapeRendererWidget();

    //UI
public slots:
    void UpdateUIValues();

signals:
    void UpdateDrawer();

private:
    void ShapeUpdated();

private slots:
    void on_ShapeComboBox_currentIndexChanged(int index);

    void on_Shape_w_valueChanged(int arg1);

    void on_Shape_h_valueChanged(int arg1);

    void on_FillRedValue_valueChanged(int arg1);

    void on_FillGreenValue_valueChanged(int arg1);

    void on_FillBlueValue_valueChanged(int arg1);

    void on_StrokeRedValue_valueChanged(int arg1);

    void on_StrokeGreenValue_valueChanged(int arg1);

    void on_StrokeBlueValue_valueChanged(int arg1);

    void on_StrokeThicknessValue_valueChanged(int arg1);

    void on_StrokeTypeComboBox_currentIndexChanged(int index);

private:
    Ui::ShapeRendererWidget *ui;
    GameObject* my_GO;
    ShapeRenderer* shape_comp;
};

#endif // SHAPERENDERER_H
