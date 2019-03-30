#include "shapedrawerwidget.h"
#include <qpen.h>
#include <qbrush.h>
#include <qpainter.h>
#include <qvector2d.h>
#include "scene.h"
#include "gameobject.h"
#include "shaperenderer.h"
#include "transform.h"

ShapeDrawerWidget::ShapeDrawerWidget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
}

QSize ShapeDrawerWidget::sizeHint() const
{
    return QSize(256,256);
}

QSize ShapeDrawerWidget::minimumSizeHint() const
{
    return QSize(64,64);
}

void ShapeDrawerWidget::paintEvent(QPaintEvent *event)
{
    //Create the painter
    QPainter painter(this);

    //Draw the background
    for(int i = 0; i < Scene::Instance()->NumGameObjects();++i)
    {
        GameObject* go = Scene::Instance()->GetGameObject(i);
        ShapeRenderer* sr = (ShapeRenderer*)go->GetComponentByType(Component::Type::ShapeRender);
        if(sr != nullptr)
        {
             if(sr->GetShape() == ShapeRenderer::Shape::Background)
                 paintBackground(painter,sr->GetShapeColor(),sr->GetBrushStyle(),rect());
        }
    }

    //Draw shapes
    for(int i = 0; i < Scene::Instance()->NumGameObjects();++i)
    {
        GameObject* go = Scene::Instance()->GetGameObject(i);
        ShapeRenderer* sr = (ShapeRenderer*)go->GetComponentByType(Component::Type::ShapeRender);
        if(sr != nullptr)
        {
            Transform* trans = (Transform*)go->GetComponentByType(Component::Type::Transform);

            switch (sr->GetShape()) {
            case ShapeRenderer::Shape::Circle:
                paintCircle(painter,sr->GetLineColor(),sr->GetShapeColor(),sr->GetLineSize(),sr->GetLineStyle(),sr->GetBrushStyle(),trans->GetPosition(),sr->GetSize(),trans->GetScale());
                break;
            case ShapeRenderer::Shape::Rectangle:
                paintRectangle(painter,sr->GetLineColor(),sr->GetShapeColor(),sr->GetLineSize(),sr->GetLineStyle(),sr->GetBrushStyle(),trans->GetPosition(),sr->GetSize(),trans->GetScale());
                break;
            default:
                break;
            }
        }
    }


}

void ShapeDrawerWidget::paintCircle(QPainter& painter, QColor line_color, QColor shape_color, int line_size,
                                    Qt::PenStyle pen_style, Qt::BrushStyle brush_style, QVector2D pos, QVector2D size, QVector2D scale)
{
    QBrush brush;
    QPen pen;

    brush.setColor(shape_color);
    brush.setStyle(brush_style);
    pen.setWidth(line_size);
    pen.setColor(line_color);
    pen.setStyle(pen_style);
    painter.setBrush(brush);
    painter.setPen(pen);

    //Transform pos is the center of the shape
    int w = size.x() * scale.x();
    int h = size.y() * scale.y();
    int x = pos.x() - w/2;
    int y = pos.y() - h/2;

    painter.drawEllipse(x,y,w,h);
}

void ShapeDrawerWidget::paintBackground(QPainter &painter, QColor color, Qt::BrushStyle brush_style, QRect background)
{
    QBrush brush;
    QPen pen;

    brush.setColor(color);
    brush.setStyle(brush_style);
    pen.setStyle(Qt::PenStyle::NoPen);
    painter.setBrush(brush);
    painter.setPen(pen);

    painter.drawRect(background);
}

void ShapeDrawerWidget::paintRectangle(QPainter& painter, QColor line_color, QColor shape_color, int line_size, Qt::PenStyle pen_style, Qt::BrushStyle brush_style, QVector2D pos, QVector2D size, QVector2D scale)
{
    QBrush brush;
    QPen pen;

    brush.setColor(shape_color);
    brush.setStyle(brush_style);
    pen.setWidth(line_size);
    pen.setColor(line_color);
    pen.setStyle(pen_style);
    painter.setBrush(brush);
    painter.setPen(pen);

    //Transform pos is the center of the shape
    int w = size.x() * scale.x();
    int h = size.y() * scale.y();
    int x = pos.x() - w/2;
    int y = pos.y() - h/2;

    painter.drawRect(x,y,w,h);
}
