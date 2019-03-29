#include "shaperenderer.h"

ShapeRenderer::ShapeRenderer() : Component(Component::Type::ShapeRender)
{

}

QColor ShapeRenderer::GetLineColor() const
{
    return line_color;
}

QColor ShapeRenderer::GetShapeColor() const
{
    return shape_color;
}

Qt::PenStyle ShapeRenderer::GetLineStyle() const
{
    return line_style;
}

Qt::BrushStyle ShapeRenderer::GetBrushStyle() const
{
    return brush_style;
}

ShapeRenderer::Shape ShapeRenderer::GetShape() const
{
    return shape;
}

void ShapeRenderer::SetLineColor(QColor c)
{
    line_color = c;
}

void ShapeRenderer::SetShapeColor(QColor c)
{
    shape_color = c;
}

void ShapeRenderer::SetLineStyle(Qt::PenStyle s)
{
    line_style = s;
}

void ShapeRenderer::SetBrushStyle(Qt::BrushStyle s)
{
    brush_style = s;
}

void ShapeRenderer::SetShape(ShapeRenderer::Shape s)
{
    shape = s;
}
