#ifndef SHAPERENDERER_H
#define SHAPERENDERER_H

#include "component.h"
#include <qcolor.h>
#include <qpen.h>
#include <qbrush.h>

class ShapeRenderer : public Component
{
public:
    ShapeRenderer();

    QColor GetLineColor()const;
    QColor GetShapeColor() const;
    Qt::PenStyle GetLineStyle() const;
    Qt::BrushStyle GetBrushStyle()const;

    void SetLineColor(QColor c);
    void SetShapeColor(QColor c);
    void SetLineStyle(Qt::PenStyle s);
    void SetBrushStyle(Qt::BrushStyle s);

private:
    QColor line_color;
    QColor shape_color;
    Qt::PenStyle line_style;
    Qt::BrushStyle brush_style;

};

#endif // SHAPERENDERER_H
