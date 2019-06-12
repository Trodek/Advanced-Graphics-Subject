#include "materialwidget.h"
#include "ui_materialwidget.h"
#include "texture.h"
#include "scene.h"
#include "gameobject.h"
#include "modelrender.h"
#include "model.h"
#include "mesh.h"
#include "material.h"

MaterialWidget::MaterialWidget(uint index, QWidget *parent) :
    QWidget(parent), index(index),
    ui(new Ui::MaterialWidget)
{
    ui->setupUi(this);
    UpdateUI();
}

MaterialWidget::~MaterialWidget()
{
    delete ui;
}

void MaterialWidget::UpdateUI()
{
    QVector<Texture*> textures = ResourceManager::Instance()->GetAllTextures();
    ui->AlbedoCombo->clear();
    ui->normalCombo->clear();
    ui->specularCombo->clear();
    ui->heightCombo->clear();
    ui->AlbedoCombo->addItem("None");
    ui->normalCombo->addItem("None");
    ui->specularCombo->addItem("None");
    ui->heightCombo->addItem("None");

    for(Texture* t : textures)
    {
        ui->AlbedoCombo->addItem(t->name);
        ui->normalCombo->addItem(t->name);
        ui->specularCombo->addItem(t->name);
        ui->heightCombo->addItem(t->name);
    }

    GameObject *go = Scene::Instance()->GetSelectedGameObject();
    if(go!=nullptr)
    {
        ModelRender* mr = (ModelRender*)go->GetComponentByType(Component::Type::ModelRenderer);

        if(mr != nullptr && mr->GetModel()->meshes[index]->material != nullptr)
        {
            int id;
            if(mr->GetModel()->meshes[index]->material->normal != nullptr)
            {
                id = ui->normalCombo->findText(mr->GetModel()->meshes[index]->material->normal->name);
                if(id != -1)
                    ui->normalCombo->setCurrentIndex(id);
            }

            if(mr->GetModel()->meshes[index]->material->albedo != nullptr)
            {
                id = ui->AlbedoCombo->findText(mr->GetModel()->meshes[index]->material->albedo->name);
                if(id != -1)
                    ui->AlbedoCombo->setCurrentIndex(id);

            }

            if(mr->GetModel()->meshes[index]->material->height != nullptr)
            {
                id = ui->normalCombo->findText(mr->GetModel()->meshes[index]->material->height->name);
                if(id != -1)
                    ui->heightCombo->setCurrentIndex(id);
            }

            if(mr->GetModel()->meshes[index]->material->specular != nullptr)
            {
                id = ui->normalCombo->findText(mr->GetModel()->meshes[index]->material->specular->name);
                if(id != -1)
                    ui->specularCombo->setCurrentIndex(id);
            }
        }
    }
}

void MaterialWidget::on_AlbedoCombo_activated(const QString &arg1)
{
    GameObject *go = Scene::Instance()->GetSelectedGameObject();
    if(go!=nullptr)
    {
        ModelRender* mr = (ModelRender*)go->GetComponentByType(Component::Type::ModelRenderer);

        if(mr != nullptr && mr->GetModel()->meshes[index]->material != nullptr)
        {
            mr->GetModel()->meshes[index]->material->albedo = ResourceManager::Instance()->GetTexture(arg1);
        }
    }
}

void MaterialWidget::on_normalCombo_activated(const QString &arg1)
{
    GameObject *go = Scene::Instance()->GetSelectedGameObject();
    if(go!=nullptr)
    {
        ModelRender* mr = (ModelRender*)go->GetComponentByType(Component::Type::ModelRenderer);

        if(mr != nullptr && mr->GetModel()->meshes[index]->material != nullptr)
        {
            mr->GetModel()->meshes[index]->material->normal = ResourceManager::Instance()->GetTexture(arg1);
        }
    }
}

void MaterialWidget::on_specularCombo_activated(const QString &arg1)
{
    GameObject *go = Scene::Instance()->GetSelectedGameObject();
    if(go!=nullptr)
    {
        ModelRender* mr = (ModelRender*)go->GetComponentByType(Component::Type::ModelRenderer);

        if(mr != nullptr && mr->GetModel()->meshes[index]->material != nullptr)
        {
            mr->GetModel()->meshes[index]->material->specular = ResourceManager::Instance()->GetTexture(arg1);
        }
    }
}

void MaterialWidget::on_heightCombo_activated(const QString &arg1)
{
    GameObject *go = Scene::Instance()->GetSelectedGameObject();
    if(go!=nullptr)
    {
        ModelRender* mr = (ModelRender*)go->GetComponentByType(Component::Type::ModelRenderer);

        if(mr != nullptr && mr->GetModel()->meshes[index]->material != nullptr)
        {
            mr->GetModel()->meshes[index]->material->height = ResourceManager::Instance()->GetTexture(arg1);
        }
    }
}
