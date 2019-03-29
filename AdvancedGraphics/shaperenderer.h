#ifndef SHAPERENDERER_H
#define SHAPERENDERER_H

#include "component.h"
#include <qcolor.h>
#include <qpen.h>
#include <qbrush.h>

class ShapeRenderer : public Component
{
public:
    enum Shape
    {
        Background,
        Rectangle,
        Circle,
    };

public:
    ShapeRenderer();

    QColor GetLineColor()const;
    QColor GetShapeColor() const;
    Qt::PenStyle GetLineStyle() const;
    Qt::BrushStyle GetBrushStyle()const;
    Shape GetShape() const;

    void SetLineColor(QColor c);
    void SetShapeColor(QColor c);
    void SetLineStyle(Qt::PenStyle s);
    void SetBrushStyle(Qt::BrushStyle s);
    void SetShape(Shape s);

private:
    QColor line_color = QColor::fromRgb(0,0,0);
    QColor shape_color = QColor::fromRgb(3,2,232);
    Qt::PenStyle line_style = Qt::PenStyle::SolidLine;
    Qt::BrushStyle brush_style = Qt::BrushStyle::SolidPattern;

    Shape shape = Rectangle;

};

#endif // SHAPERENDERER_H
