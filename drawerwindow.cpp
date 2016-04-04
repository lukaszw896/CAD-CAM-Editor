#include "drawerwindow.h"

DrawerWindow::DrawerWindow(QWidget *parent) : QMainWindow(parent)
{
    createActions();
    createMenus();
    initObjects();
    initLayout();
}


void DrawerWindow::createActions()
{
    addTorusAct = new QAction(tr("&Torus"),this);
    addPointAct = new QAction(tr("&Point"),this);
    addCurveAct = new QAction(tr("&Curve"),this);

    stereoscopyAct = new QAction(tr("&Stereoscopy"),this);
}

void DrawerWindow::createMenus()
{
    addMenu = menuBar()->addMenu(tr("&Add"));
    addMenu->addAction(addTorusAct);
    addMenu->addAction(addPointAct);
    addMenu->addAction(addCurveAct);

    settingsMenu = menuBar()->addMenu(tr("&Settings"));
    settingsMenu->addAction(stereoscopyAct);
}

void DrawerWindow::initObjects()
{
    scaleLabel = new QLabel("Scale");

    scaleSlider = new QSlider(Qt::Horizontal);
    scaleSlider->setMaximum(100);
    scaleSlider->setMinimum(10);
    oglWidget = new OGlWidget();

    connect(scaleSlider,SIGNAL(valueChanged(int)),oglWidget,SLOT(changeScale(int)));


}

void DrawerWindow::initLayout()
{
    leftLayout = new QHBoxLayout;
    leftLayout->addWidget(oglWidget);

    rightLayout = new QVBoxLayout;
    rightLayout->addWidget(scaleLabel);
    rightLayout->addWidget(scaleSlider);
    rightLayout->addStretch();

    QWidget *rightContainer = new QWidget();
    rightContainer->setMaximumWidth(200);
    rightContainer->setLayout(rightLayout);

    mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(rightContainer);

    centralWidget = new QWidget(this);
    this->setCentralWidget( centralWidget );
    centralWidget->setLayout(mainLayout);

}


