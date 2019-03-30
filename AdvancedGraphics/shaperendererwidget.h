#ifndef SHAPERENDERERWIDGEt_H
#define SHAPERENDERERWIDGET_H

#include <QWidget>

namespace Ui {
class ShapeRendererWidget;
}

class ShapeRendererWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShapeRendererWidget(QWidget *parent = nullptr);
    ~ShapeRendererWidget();

private:
    Ui::ShapeRendererWidget *ui;
};

#endif // SHAPERENDERER_H
