#include "lightwidget.h"
#include "ui_lightwidget.h"
#include "scene.h"
#include "gameobject.h"
#include "light.h"

LightWidget::LightWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LightWidget)
{
    ui->setupUi(this);
    UpdateUI();
}

LightWidget::~LightWidget()
{
    delete ui;
}

void LightWidget::on_comboBox_currentIndexChanged(int index)
{
    GameObject *go = Scene::Instance()->GetSelectedGameObject();
    if(go!=nullptr)
    {
        Light* light = (Light*)go->GetComponentByType(Component::Light);

        if(light != nullptr)
        {
            light->type = (Light::Type)index;
        }
    }
}

void LightWidget::on_Red_valueChanged(int arg1)
{
    GameObject *go = Scene::Instance()->GetSelectedGameObject();
    if(go!=nullptr)
    {
        Light* light = (Light*)go->GetComponentByType(Component::Light);

        if(light != nullptr)
        {
            light->color.setRed(arg1);
        }
    }
}

void LightWidget::on_Green_valueChanged(int arg1)
{
    GameObject *go = Scene::Instance()->GetSelectedGameObject();
    if(go!=nullptr)
    {
        Light* light = (Light*)go->GetComponentByType(Component::Light);

        if(light != nullptr)
        {
            light->color.setGreen(arg1);
        }
    }
}

void LightWidget::on_Blue_valueChanged(int arg1)
{
    GameObject *go = Scene::Instance()->GetSelectedGameObject();
    if(go!=nullptr)
    {
        Light* light = (Light*)go->GetComponentByType(Component::Light);

        if(light != nullptr)
        {
            light->color.setBlue(arg1);
        }
    }
}

void LightWidget::on_doubleSpinBox_valueChanged(double arg1)
{
    GameObject *go = Scene::Instance()->GetSelectedGameObject();
    if(go!=nullptr)
    {
        Light* light = (Light*)go->GetComponentByType(Component::Light);

        if(light != nullptr)
        {
            light->intensity = arg1;
        }
    }
}

void LightWidget::UpdateUI()
{
    GameObject *go = Scene::Instance()->GetSelectedGameObject();
    if(go!=nullptr)
    {
        Light* light = (Light*)go->GetComponentByType(Component::Light);
        if(light != nullptr)
        {
            ui->comboBox->setCurrentIndex((int)light->type);
            ui->Red->setValue(light->color.red());
            ui->Green->setValue(light->color.green());
            ui->Blue->setValue(light->color.blue());
            ui->doubleSpinBox->setValue(light->intensity);
        }
    }
}
