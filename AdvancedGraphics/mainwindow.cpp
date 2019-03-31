#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <iostream>
#include "shapedrawerwidget.h"
#include "transformwidget.h"
//Test
#include "scene.h"
#include "gameobject.h"
#include "transform.h"
#include "shaperenderer.h"
#include "shaperendererwidget.h"
#include "hierarchy.h"
#include "collapsewidget.h"
#include "gameobject.h"
#include "inspector.h"
#include "scene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QFile file(":/stylesheets/DarkStyle.css");
    if(file.open(QIODevice::ReadOnly)){
        QString contents = file.readAll();
        setStyleSheet(contents);
    }
    ui->setupUi(this);

    // TEST -- REMOVE WHEN NOT NEEDED
    std::cout <<"Num objects: "<< Scene::Instance()->NumGameObjects() << std::endl;
    GameObject* test = Scene::Instance()->GetGameObject(0);
    ShapeRenderer* sr = (ShapeRenderer*)test->AddComponent(Component::Type::ShapeRender);
    std::cout << "Object components: " << test->NumComponents() << std::endl;
    Transform* t = (Transform*)test->GetComponentByType(Component::Type::Transform);
    std::cout << "Transform Pos: " << t->GetPosition().x() << " " << t->GetPosition().y() << std::endl;
    // Rectangle
    sr->SetShape(ShapeRenderer::Shape::Rectangle);
    sr->SetLineStyle(Qt::PenStyle::DashDotLine);
    sr->SetLineColor(QColor(251,41,134));
    sr->SetBrushStyle(Qt::BrushStyle::SolidPattern);
    sr->SetShapeColor(QColor(100,150,69));
    sr->SetLineSize(3);
    sr->SetSize(QVector2D(30,15));
    t->SetPosition(QVector2D(60,25));
    t->SetScale(QVector2D(3,3));

    //Circle
    test = new GameObject();
    test->SetName("SimonLaXupa");
    sr = (ShapeRenderer*)test->AddComponent(Component::Type::ShapeRender);
    t = (Transform*)test->GetComponentByType(Component::Type::Transform);
    sr->SetShape(ShapeRenderer::Shape::Circle);
    sr->SetLineStyle(Qt::PenStyle::SolidLine);
    sr->SetLineColor(QColor(51,241,34));
    sr->SetBrushStyle(Qt::BrushStyle::SolidPattern);
    sr->SetShapeColor(QColor(100,50,69));
    sr->SetLineSize(2);
    sr->SetSize(QVector2D(90,60));
    t->SetPosition(QVector2D(130,105));
    Scene::Instance()->AddGameObject(test);

    // Background
    test = new GameObject();
    test->SetName("SimonLaXupa");
    sr = (ShapeRenderer*)test->AddComponent(Component::Type::ShapeRender);
    t = (Transform*)test->GetComponentByType(Component::Type::Transform);
    sr->SetShape(ShapeRenderer::Shape::Background);
    sr->SetBrushStyle(Qt::BrushStyle::SolidPattern);
    sr->SetShapeColor(QColor(0,100,255));
    Scene::Instance()->AddGameObject(test);
    // ------------------------------

    // Create Hierarchy & Inspector
    m_Hierarchy = new Hierarchy();
    m_Inspector = new Inspector();

    m_ShapeDrawer = ui->widget;
    m_Trans = m_Inspector->m_TransformWidget;

    connect(m_Trans,SIGNAL(UpdateDrawer()),this,SLOT(Redraw()));
    connect(m_Inspector->m_ShapeRendererWidget,SIGNAL(UpdateDrawer()),this,SLOT(Redraw()));

    //Add the Widget
    ui->dockHierarchy->setWidget(m_Hierarchy);
    ui->dockInspector->setWidget(m_Inspector);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Redraw()
{
    m_ShapeDrawer->update();
}
