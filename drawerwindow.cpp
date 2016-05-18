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
    addBSplineAct = new QAction(tr("&BSpline"),this);
    connect(addBSplineAct, &QAction::triggered, this, &DrawerWindow::addBSpline);
    addInterBSplineAct = new QAction(tr("&InterBSpline"),this);
    connect(addInterBSplineAct,&QAction::triggered,this,&DrawerWindow::addInterBSpline);

    addBezierFlatSurface = new QAction(tr("&Flat surface"),this);
    connect(addBezierFlatSurface,&QAction::triggered,this,&DrawerWindow::openAddC0FlatSurfaceDialog);
    addBezierCylinderSurface = new QAction(tr("&Cylinder surface"),this);
    connect(addBezierCylinderSurface,&QAction::triggered,this,&DrawerWindow::openAddC0CylinderSurfaceDialog);

    stereoscopyAct = new QAction(tr("&Stereoscopy"),this);
    connect(stereoscopyAct, &QAction::triggered, this, &DrawerWindow::openStereoscopySettingsDialog);

}

void DrawerWindow::createMenus()
{
    addMenu = menuBar()->addMenu(tr("&Add"));
    addMenu->addAction(addTorusAct);
    addMenu->addAction(addPointAct);
    addMenu->addAction(addCurveAct);
    addMenu->addAction(addBSplineAct);
    addMenu->addAction(addInterBSplineAct);
    addBezierSurfaceMenu = new QMenu(tr("&Add surface"));
    addMenu->addMenu(addBezierSurfaceMenu);
    addBezierSurfaceMenu->addAction(addBezierFlatSurface);
    addBezierSurfaceMenu->addAction(addBezierCylinderSurface);

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

    patchParamSlider = new QSlider(Qt::Horizontal);
    patchParamSlider->setMaximum(10);
    patchParamSlider->setMinimum(4);

    oglWidget = new OGlWidget();
    objectListsWidget = new ObjectListsWidget();
    connect(this,SIGNAL(drawableDataChanged()),objectListsWidget,SLOT(updateListsContent()));
    connect(this,SIGNAL(heightChanged(int)),objectListsWidget,SLOT(updateLayoutHeight(int)));
    //connection between on scene click and item list
    connect(oglWidget,SIGNAL(pointOnScreenClick(Point*)),objectListsWidget,SLOT(pointOnSceneSelection(Point*)));
    connect(oglWidget,SIGNAL(pointOnScreenDoubleClick(Point*)),objectListsWidget,SLOT(pointOnSceneDoubleClick(Point*)));
    connect(oglWidget,SIGNAL(cursorPositionChanged()),this,SLOT(updateCursorInfo()));

    settingsDialog = new SettingsDialog(this);
    addC0FlatSurfaceDialog = new AddC0FlatSurfaceDialog(this);
    connect(addC0FlatSurfaceDialog,SIGNAL(bezFlatSurfAdded()),objectListsWidget,SLOT(updateListsContent()));

    connect(scaleSlider,SIGNAL(valueChanged(int)),oglWidget,SLOT(changeScale(int)));
    connect(patchParamSlider,SIGNAL(valueChanged(int)),this,SLOT(updatePatchParam(int)));
    connect(settingsDialog,SIGNAL(turnOnOffStereoscopy(bool)),oglWidget,SLOT(checkBoxStateChanged(bool)));
    connect(settingsDialog,SIGNAL(eyeDistanceValueChanged(int)),oglWidget,SLOT(changeEyeDistance(int)));

    cordsBox = new QGroupBox(tr("Cords"));

    screenPosition = new QLabel();
    xRealCord = new QLabel();
    yRealCord = new QLabel();
    zRealCord = new QLabel();

}

void DrawerWindow::initLayout()
{
    leftLayout = new QHBoxLayout;
    leftLayout->addWidget(oglWidget);

    rightLayout = new QVBoxLayout;
    rightLayout->addWidget(cordsBox);
    rightLayout->addWidget(objectListsWidget);
    rightLayout->addWidget(scaleLabel);
    rightLayout->addWidget(scaleSlider);
    rightLayout->addWidget(patchParamSlider);
    rightLayout->addStretch();

    QWidget *rightContainer = new QWidget();
    rightContainer->setMaximumWidth(250);
    rightContainer->setLayout(rightLayout);

    mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(rightContainer);

    centralWidget = new QWidget(this);
    this->setCentralWidget( centralWidget );
    centralWidget->setLayout(mainLayout);

    cordsLayout = new QVBoxLayout;
    cordsLayout->addWidget(screenPosition);
    cordsLayout->addWidget(xRealCord);
    cordsLayout->addWidget(yRealCord);
    cordsLayout->addWidget(zRealCord);
    cordsBox->setLayout(cordsLayout);


}

void DrawerWindow::openStereoscopySettingsDialog()
{
    settingsDialog->show();
}

void DrawerWindow::openAddC0FlatSurfaceDialog()
{
    addC0FlatSurfaceDialog->isAddingFlat = true;
    addC0FlatSurfaceDialog->show();
}

void DrawerWindow::openAddC0CylinderSurfaceDialog(){
    addC0FlatSurfaceDialog->isAddingFlat = false;
    addC0FlatSurfaceDialog->show();
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

void DrawerWindow::addBSpline()
{
    //items in lists are deseleted while adding new element (?)
    drawableObjectsData.deselectToruses();
    drawableObjectsData.deselectPoints();
    drawableObjectsData.deselectBezierCurves();

    BSpline* bSpline = new BSpline(drawableObjectsData.camera);
    drawableObjectsData.addBSpline(bSpline);
    emit drawableDataChanged();
}

void DrawerWindow::addInterBSpline()
{
    //items in lists are deseleted while adding new element (?)
    drawableObjectsData.deselectToruses();
    drawableObjectsData.deselectPoints();
    drawableObjectsData.deselectBezierCurves();

    InterBSpline* interBSpline = new InterBSpline(drawableObjectsData.camera);
    drawableObjectsData.addInterBSpline(interBSpline);
    emit drawableDataChanged();
}

void DrawerWindow::updateCursorInfo()
{
    int screenXPos = (1.f+drawableObjectsData.cursor->centerOnScreenPos.x)/2*drawableObjectsData.camera->screenWidth;
    int screenYPos = (1.f+drawableObjectsData.cursor->centerOnScreenPos.y)/2*(-drawableObjectsData.camera->screenHeight)
                        +drawableObjectsData.camera->screenHeight;
    vec4 realPosition = drawableObjectsData.cursor->getCursorPos();

    screenPosition->setText(QString::fromStdString("ScrPos:"+std::to_string(screenXPos)+"::"+std::to_string(screenYPos)));
    xRealCord->setText(QString::fromStdString("Real X: "+ std::to_string(realPosition.x)));
    yRealCord->setText(QString::fromStdString("Real Y: "+ std::to_string(realPosition.y)));
    zRealCord->setText(QString::fromStdString("Real Z: "+ std::to_string(realPosition.z)));

}

void DrawerWindow::updatePatchParam(int n)
{
    drawableObjectsData.updatePatchParam(n);
}

void DrawerWindow::resizeEvent(QResizeEvent * resizeEvent)
{
    int currentHeight = this->size().height();
    if(oldHeight == 200)
    {
        oldHeight = currentHeight;
         emit heightChanged(600);
        return;
    }
    if(oldHeight == currentHeight) return;
    /*int currentHeight = resizeEvent->size().height();
    int patchParamHeight = patchParamSlider->size().height();
    int cordsBoxHeight = cordsBox->size().height();*/
    oldHeight = currentHeight;
    int listObjectHeight = this->height() - cordsBox->size().height()
            - patchParamSlider->size().height() - 170;
    emit heightChanged(listObjectHeight);
}




