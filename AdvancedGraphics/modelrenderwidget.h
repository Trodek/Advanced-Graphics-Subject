#ifndef MODELRENDERWIDGET_H
#define MODELRENDERWIDGET_H

#include <QWidget>

namespace Ui {
class ModelRenderWidget;
}

class ModelRenderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModelRenderWidget(QWidget *parent = nullptr);
    ~ModelRenderWidget();

private slots:
    void on_ModelComboBox_currentIndexChanged(const QString &arg1);

    void on_ShaderComboBox_currentIndexChanged(const QString &arg1);

    void on_AlbedoComboBox_currentIndexChanged(const QString &arg1);

    void on_NormalComboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::ModelRenderWidget *ui;

    void UpdateUI();
};

#endif // MODELRENDERWIDGET_H
