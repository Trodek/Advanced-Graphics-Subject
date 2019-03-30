#include "inspector.h"
#include "ui_inspector.h"
#include"ui_transform.h"
#include"transformwidget.h"
Inspector::Inspector(QWidget *parent) :
    QWidget(parent){

    //Create Widgets
    TransformWidget *m_TransformWidget = new TransformWidget;

    //Create the vertical Layout
    QVBoxLayout *layout = new QVBoxLayout;


    layout->addWidget(m_TransformWidget);
    setLayout(layout);

}

Inspector::~Inspector()
{
}
