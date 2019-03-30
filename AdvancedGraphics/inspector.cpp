#include "inspector.h"
#include "ui_inspector.h"
#include"transformwidget.h"
#include "gameobject.h"
#include "shaperendererwidget.h"

Inspector::Inspector(QWidget *parent) :
    QWidget(parent){

    //Create Widgets
    m_TransformWidget = new TransformWidget;
    m_ShapeRendererWidget = new ShapeRendererWidget;
    //Create the vertical Layout
    QVBoxLayout *layout = new QVBoxLayout;
   // QSpacerItem *spacer = new QSpacerItem(1,1,QSizePolicy::Expanding);



    layout->addWidget(m_TransformWidget);
    layout->addWidget(m_ShapeRendererWidget);
    //layout->addSpacerItem(spacer);
    setLayout(layout);

}

Inspector::~Inspector()
{
}
//Call when Clicked GameOBject on Hierarchy
void Inspector::SetNewGameObject(GameObject * newActiveGO)
{
    m_ActiveGameObject = newActiveGO;
    m_TransformWidget->UpdateUIValues();
    m_ShapeRendererWidget->UpdateUIValues();
}
