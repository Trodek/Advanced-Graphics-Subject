#ifndef MATERIALWIDGET_H
#define MATERIALWIDGET_H

#include <QWidget>

namespace Ui {
class MaterialWidget;
}

class MaterialWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialWidget(uint index, QWidget *parent = nullptr);
    ~MaterialWidget();

private slots:
    void on_AlbedoCombo_currentIndexChanged(const QString &arg1);

    void on_normalCombo_currentIndexChanged(const QString &arg1);

    void on_specularCombo_currentIndexChanged(const QString &arg1);

    void on_heightCombo_currentIndexChanged(const QString &arg1);

private:
    Ui::MaterialWidget *ui;
    uint index;

    void UpdateUI();
};

#endif // MATERIALWIDGET_H
