#include "inspector.h"
#include "ui_inspector.h"
#include"ui_transform.h"
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
   // QSpacerItem *spacer = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::expandingDirections());



    layout->addWidget(m_TransformWidget);
    layout->addWidget(m_ShapeRendererWidget);
    layout->addItem(spacer);
    setLayout(layout);

}

Inspector::~Inspector()
{
}
//Call when Clicked GameOBject on Hierarchy
void Inspector::SetNewGameObject(GameObject * newActiveGO)
{
    m_ActiveGameObject = newActiveGO;
    m_TransformWidget->UpdateUIValues(newActiveGO);
    //m_ShapeRenderer->UpdateUIValues(newActiveGO);
}
