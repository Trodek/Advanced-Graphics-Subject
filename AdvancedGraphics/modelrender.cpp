#include "modelrender.h"
#include "model.h"
#include "shaderprogram.h"
#include <QString>

ModelRender::ModelRender() : Component (Component::Type::ModelRenderer)
{

}

ModelRender::~ModelRender()
{

}

void ModelRender::SetModel(Model *model)
{
    if(model != nullptr)
        this->model = model;
}

Model *ModelRender::GetModel()
{
    return model;
}

void ModelRender::SetShader(ShaderProgram *shader)
{
    if(shader != nullptr)
        this->shader = shader;
}

ShaderProgram *ModelRender::GetShaderProgram()
{
    return shader;
}

void ModelRender::Save(QJsonObject &file) const
{
    file["type"] = GetType();

    if(model != nullptr)
        file["model_path"] = model->path;
    else
        file["model_path"] = "";

    if(shader != nullptr)
    {
        file["vert_path"] = shader->vertPath;
        file["frag_path"] = shader->fragPath;
    }
    else
    {
        file["vert_path"] = "";
        file["frag_path"] = "";
    }


}

void ModelRender::Load(const QJsonObject &file)
{
    std::string model_path = file["model_path"].toString().toStdString();

    if(model_path != "")
    {
        //check if resource is loaded
        Model* m = ResourceManager::Instance()->GetModel(model_path.c_str());

        if(m == nullptr)
        {
            // model not loaded
            m = ResourceManager::Instance()->CreateModel();
            m->loadModel(model_path);
        }

        model = m;
    }

    std::string vert_path = file["vert_path"].toString().toStdString();
    std::string frag_path = file["frag_path"].toString().toStdString();

    if(vert_path != "" && frag_path != vert_path)
    {
        // check if loaded
        ShaderProgram* sp = ResourceManager::Instance()->GetShaderProgram(ResourceManager::Instance()->GetNameFrom(vert_path.c_str()).c_str());

        if(sp == nullptr)
        {
            sp = ResourceManager::Instance()->CreateShaderProgram();
            sp->SetShaders(vert_path.c_str(),frag_path.c_str());
        }

        shader = sp;
    }
}
