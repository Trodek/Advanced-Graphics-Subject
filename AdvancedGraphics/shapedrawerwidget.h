#ifndef SHAPEDRAWERWIDGET_H
#define SHAPEDRAWERWIDGET_H

#include <QObject>
#include <QWidget>

class ShapeDrawerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShapeDrawerWidget(QWidget *parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

signals:

public slots:

private:

    void paintEvent(QPaintEvent* event) override;

    void paintCircle(QPainter& painter, QColor line_color, QColor shape_color, int line_size, Qt::PenStyle pen_style, Qt::BrushStyle brush_style, QVector3D pos, QVector3D size, QVector3D scale);
    void paintBackground(QPainter& painter, QColor color, Qt::BrushStyle brush_style, QRect background);
    void paintRectangle(QPainter& painter, QColor line_color, QColor shape_color, int line_size, Qt::PenStyle pen_style, Qt::BrushStyle brush_style, QVector3D pos, QVector3D size, QVector3D scale);

};
#endif // SHAPEDRAWERWIDGET_H
