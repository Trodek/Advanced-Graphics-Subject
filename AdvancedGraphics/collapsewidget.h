#ifndef COLLAPSEWIDGET_H
#define COLLAPSEWIDGET_H

#include <QWidget>

namespace Ui {
class CollapseWidget;
}

class CollapseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CollapseWidget(QWidget *parent = 0);
    ~CollapseWidget();

private:
    Ui::CollapseWidget *ui;
};

#endif // COLLAPSEWIDGET_H
