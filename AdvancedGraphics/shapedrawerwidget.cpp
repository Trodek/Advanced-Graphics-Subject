#include "shapedrawerwidget.h"
#include <qpen.h>
#include <qbrush.h>
#include <qpainter.h>

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
    QColor white = QColor::fromRgb(255,255,255);
    QColor blue = QColor::fromRgb(127,190,220);
    QColor black = QColor::fromRgb(0,0,0);

    QPainter painter(this);

    QBrush brush;
    QPen pen;

    brush.setColor(blue);
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    pen.setStyle(Qt::PenStyle::NoPen);
    painter.setBrush(brush);
    painter.setPen(pen);

    painter.drawRect(rect());

    brush.setColor(white);
    pen.setWidth(4);
    pen.setColor(black);
    pen.setStyle(Qt::PenStyle::DashLine);
    painter.setBrush(brush);
    painter.setPen(pen);

    int r = 64;
    int w = r*2;
    int h = r*2;
    int x = rect().width()/2-r;
    int y = rect().height()/2-r;
    QRect circleRect(x,y,w,h);
    painter.drawEllipse(circleRect);

}
