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
    connect(addTorusAct, &QAction::triggered, this, &DrawerWindow::addTorus);
    addPointAct = new QAction(tr("&Point"),this);
    connect(addPointAct, &QAction::triggered, this, &DrawerWindow::addPoint);
    addCurveAct = new QAction(tr("&Curve"),this);
    connect(addCurveAct, &QAction::triggered, this, &DrawerWindow::addBezierCurve);

    stereoscopyAct = new QAction(tr("&Stereoscopy"),this);
    connect(stereoscopyAct, &QAction::triggered, this, &DrawerWindow::openStereoscopySettingsDialog);
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
    screenPosition = new QLabel;
    xRealCord = new QLabel;
    yRealCord = new QLabel;
    zRealCord = new QLabel;

    scaleLabel = new QLabel("Scale");

    scaleSlider = new QSlider(Qt::Horizontal);
    scaleSlider->setMaximum(100);
    scaleSlider->setMinimum(10);
    oglWidget = new OGlWidget();
    objectListsWidget = new ObjectListsWidget();
    connect(this,SIGNAL(drawableDataChanged()),objectListsWidget,SLOT(updateListsContent()));

    //connection between on scene click and item list
    connect(oglWidget,SIGNAL(pointOnScreenClick(Point*)),objectListsWidget,SLOT(pointOnSceneSelection(Point*)));
    connect(oglWidget,SIGNAL(pointOnScreenDoubleClick(Point*)),objectListsWidget,SLOT(pointOnSceneDoubleClick(Point*)));

    settingsDialog = new SettingsDialog;

    connect(scaleSlider,SIGNAL(valueChanged(int)),oglWidget,SLOT(changeScale(int)));
    connect(settingsDialog,SIGNAL(turnOnOffStereoscopy(bool)),oglWidget,SLOT(checkBoxStateChanged(bool)));
    connect(settingsDialog,SIGNAL(eyeDistanceValueChanged(int)),oglWidget,SLOT(changeEyeDistance(int)));

}

void DrawerWindow::initLayout()
{
    leftLayout = new QHBoxLayout;
    leftLayout->addWidget(oglWidget);

    rightLayout = new QVBoxLayout;
    rightLayout->addWidget(objectListsWidget);
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

void DrawerWindow::openStereoscopySettingsDialog()
{
    settingsDialog->show();
}

void DrawerWindow::addPoint()
{
    //items in lists are deseleted while adding new element (?)

    Point* point = new Point(drawableObjectsData.camera);
    glm::vec4 position = drawableObjectsData.cursor->getCursorPos();
    point->xPos = position.x;
    point->updateTranslationMatX();
    point->yPos = position.y;
    point->updateTranslationMatY();
    point->zPos = position.z;
    point->updateTranslationMatZ();
    drawableObjectsData.addPoint(point);

    drawableObjectsData.deselectToruses();
    drawableObjectsData.deselectPoints();
    drawableObjectsData.deselectBezierCurves();

    emit drawableDataChanged();
}

void DrawerWindow::addTorus()
{
    //items in lists are deseleted while adding new element (?)
    drawableObjectsData.deselectToruses();
    drawableObjectsData.deselectPoints();
    drawableObjectsData.deselectBezierCurves();

    Torus* torus = new Torus(drawableObjectsData.camera);
    glm::vec4 position = drawableObjectsData.cursor->getCursorPos();
    torus->xPos = position.x;
    torus->updateTranslationMatX();
    torus->yPos = position.y;
    torus->updateTranslationMatY();
    torus->zPos = position.z;
    torus->updateTranslationMatZ();
    drawableObjectsData.addTorus(torus);
    emit drawableDataChanged();
}

void DrawerWindow::addBezierCurve()
{
    //items in lists are deseleted while adding new element (?)
    drawableObjectsData.deselectToruses();
    drawableObjectsData.deselectPoints();
    drawableObjectsData.deselectBezierCurves();

    BezierCurve* bezierCurve = new BezierCurve(drawableObjectsData.camera);
    drawableObjectsData.addBezierCurve(bezierCurve);
    emit drawableDataChanged();
}

void DrawerWindow::updateCursorInfo(int screenWidth, int screenHeight)
{

}




