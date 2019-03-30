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
    void UpdateUIOnShapeType();
    void UpdateUIValues(GameObject* new_GO);
    void UpdateShapeDimensions(int x,int y);
    void UpdateShapeColor(int r,int g,int b);
    void UpdateLineColor(int r, int g, int b);
    void UpdateLineSize(int size);
    void UpdateLineStyle(Qt::PenStyle s);

private:
    Ui::ShapeRendererWidget *ui;
    GameObject* my_GO;
    ShapeRenderer* shape_comp;
};

#endif // SHAPERENDERER_H
