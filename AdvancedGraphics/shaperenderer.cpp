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

int ShapeRenderer::GetLineSize() const
{
    return  line_size;
}

ShapeRenderer::Shape ShapeRenderer::GetShape() const
{
    return shape;
}

QVector2D ShapeRenderer::GetSize() const
{
    return size;
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

void ShapeRenderer::SetLineSize(int s)
{
    line_size = s;
}

void ShapeRenderer::SetShape(ShapeRenderer::Shape s)
{
    shape = s;
}

void ShapeRenderer::SetSize(QVector2D s)
{
    size = s;
}
