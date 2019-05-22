#include "inspector.h"
#include "ui_inspector.h"
#include"transformwidget.h"
#include "gameobject.h"

Inspector::Inspector(QWidget *parent) :
    QWidget(parent), ui(new Ui::Inspector()){

    ui->setupUi(this);

    TransformWidget* trans = new TransformWidget();
    ui->verticalLayout_2->insertWidget(ui->verticalLayout_2->count()-4, trans);

}

Inspector::~Inspector()
{
}
//Call when Clicked GameOBject on Hierarchy
void Inspector::SetNewGameObject(GameObject * newActiveGO)
{
    m_ActiveGameObject = newActiveGO;
    m_TransformWidget->UpdateUIValues();
}
