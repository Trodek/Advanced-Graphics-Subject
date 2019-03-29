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
};

#endif // SHAPEDRAWERWIDGET_H
