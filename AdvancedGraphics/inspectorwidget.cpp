#include "inspectorwidget.h"
#include <QLayout>
#include <QVBoxLayout>
#include <QSpacerItem>

InspectorWidget::InspectorWidget(QWidget *parent) : QWidget(parent)
{

    //TransformWidget *transformWidget = new TransformWidget;
    //MeshRendererWidget *meshRendererWidget = meshRendererWidget;
    QSpacerItem *spacer = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::ExpandFlag);

    //Vertical Layout
    QVBoxLayout *layout = new QVBoxLayout;

    //Add all elements to the layout
   // layout->addWidget(transformWidget);
   // layout->addWidget();
    layout->addItem(spacer);

    //see the layour for this widget
    setLayout(layout);
}
