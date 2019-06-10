#include "modelrenderwidget.h"
#include "ui_modelrenderwidget.h"
#include "gameobject.h"
#include "scene.h"
#include "model.h"
#include "texture.h"
#include "shaderprogram.h"
#include "resourcemanager.h"
#include "modelrender.h"

ModelRenderWidget::ModelRenderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModelRenderWidget)
{
    ui->setupUi(this);
    UpdateUI();
}

ModelRenderWidget::~ModelRenderWidget()
{
    delete ui;
}

void ModelRenderWidget::on_ModelComboBox_currentIndexChanged(const QString &arg1)
{
    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go!=nullptr)
    {
        ModelRender* mr = (ModelRender*)go->GetComponentByType(Component::Type::ModelRenderer);
        if(mr != nullptr)
        {
            mr->SetModel(ResourceManager::Instance()->GetModel(arg1));
        }
    }
}

void ModelRenderWidget::on_ShaderComboBox_currentIndexChanged(const QString &arg1)
{
    GameObject* go = Scene::Instance()->GetSelectedGameObject();
    if(go!=nullptr)
    {
        ModelRender* mr = (ModelRender*)go->GetComponentByType(Component::Type::ModelRenderer);
        if(mr != nullptr)
        {
            mr->SetShader(ResourceManager::Instance()->GetShaderProgram(arg1));
        }
    }
}

void ModelRenderWidget::on_AlbedoComboBox_currentIndexChanged(const QString &arg1)
{

}

void ModelRenderWidget::on_NormalComboBox_currentIndexChanged(const QString &arg1)
{

}

void ModelRenderWidget::UpdateUI()
{
    //Set all options to combo boxes
    QVector<Model*> models = ResourceManager::Instance()->GetAllModels();
    ui->ModelComboBox->clear();
    ui->ModelComboBox->addItem("None");

    for(Model* m : models)
    {
        ui->ModelComboBox->addItem(m->name);
    }

    QVector<ShaderProgram*> shaders = ResourceManager::Instance()->GetAllShaderPrograms();
    ui->ShaderComboBox->clear();
    ui->ShaderComboBox->addItem("None");

    for(ShaderProgram* s : shaders)
    {
        ui->ShaderComboBox->addItem(s->name);
    }

    QVector<Texture*> textures = ResourceManager::Instance()->GetAllTextures();
    ui->AlbedoComboBox->clear();
    ui->NormalComboBox->clear();
    ui->AlbedoComboBox->addItem("None");
    ui->NormalComboBox->addItem("None");

    for(Texture* t : textures)
    {
        ui->AlbedoComboBox->addItem(t->name);
        ui->NormalComboBox->addItem(t->name);
    }

    GameObject *go = Scene::Instance()->GetSelectedGameObject();
    if(go!=nullptr)
    {
        ModelRender* mr = (ModelRender*)go->GetComponentByType(Component::Type::ModelRenderer);

        if(mr != nullptr)
        {
            int index;
            if(mr->GetModel()!=nullptr)
            {
                index = ui->ModelComboBox->findText(mr->GetModel()->name);
                if(index != -1)
                    ui->ModelComboBox->setCurrentIndex(index);
            }

            if(mr->GetShaderProgram()!=nullptr)
            {
                index = ui->ShaderComboBox->findText(mr->GetShaderProgram()->name);
                if(index != -1)
                    ui->ShaderComboBox->setCurrentIndex(index);
            }

            if(mr->GetNormal() != nullptr)
            {
                index = ui->NormalComboBox->findText(mr->GetAlbedo()->name);
                if(index != -1)
                    ui->NormalComboBox->setCurrentIndex(index);
            }

            if(mr->GetAlbedo() != nullptr)
            {
                index = ui->AlbedoComboBox->findText(mr->GetAlbedo()->name);
                if(index != -1)
                    ui->AlbedoComboBox->setCurrentIndex(index);

            }
        }
    }
}
