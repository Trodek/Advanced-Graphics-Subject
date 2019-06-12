#ifndef LIGHTWIDGET_H
#define LIGHTWIDGET_H

#include <QWidget>

namespace Ui {
class LightWidget;
}

class LightWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LightWidget(QWidget *parent = nullptr);
    ~LightWidget();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_Red_valueChanged(int arg1);

    void on_Green_valueChanged(int arg1);

    void on_Blue_valueChanged(int arg1);

    void on_doubleSpinBox_valueChanged(double arg1);

private:
    Ui::LightWidget *ui;
    void UpdateUI();
};

#endif // LIGHTWIDGET_H
