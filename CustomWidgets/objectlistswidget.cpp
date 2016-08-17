#include "objectlistswidget.h"

ObjectListsWidget::ObjectListsWidget()
{
    setupLayout();
    updateListsContent();

    pointList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(pointList,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showPointsContextMenu(QPoint)));

    bezierCurveTreeList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(bezierCurveTreeList,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showBezierCurvesContextMenu(QPoint)));

    bSplineCurveTreeList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(bSplineCurveTreeList,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showBSplineContextMenu(QPoint)));

    interBSplineCurveTreeList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(interBSplineCurveTreeList,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showInterBSplineContextMenu(QPoint)));

    bezierSurfaceTreeList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(bezierSurfaceTreeList,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showBezierSurfaceContextMenu(QPoint)));

    nameChangeDialog = new NameChangeDialog();
    connect(nameChangeDialog,SIGNAL(nameHasBeenChanged()),this,SLOT(drawableHasBeenRenamed()));
}

void ObjectListsWidget::setupLayout()
{
    scrollArea = new QScrollArea;

    torusListLabel = new QLabel(tr("Torus List"));
    pointListLabel = new QLabel(tr("Point List"));
    bezierListLabel = new QLabel(tr("Bezier List"));
    bSplineListLabel = new QLabel(tr("BSpline List"));
    interBSplineListLabel = new QLabel(tr("InterBSpline List"));
    bezierSurfaceListLabel = new QLabel(tr("Bezier Surface List"));

    widgetContainerLayout = new QVBoxLayout;
    torusLayout = new QVBoxLayout;
    pointLayout = new QVBoxLayout;
    curveLayout = new QVBoxLayout;
    bSplineLayout = new QVBoxLayout;
    interBSplineLayout = new QVBoxLayout;
    bezierSurfaceLayout = new QVBoxLayout;
    torusLayout->setMargin(0);
    pointLayout->setMargin(0);
    curveLayout->setMargin(0);
    bSplineLayout->setMargin(0);
    interBSplineLayout->setMargin(0);


    torusList = new QListWidget;
    torusList->setFixedHeight(150);
    connect(torusList,SIGNAL(clicked(QModelIndex)),this,SLOT(torusHasBeenSelected()));
    connect(torusList,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(torusHasBeenDoubleClicked()));
    pointList = new QListWidget;
    pointList->setFixedHeight(150);
    pointList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    connect(pointList,SIGNAL(clicked(QModelIndex)),this,SLOT(pointHasBeenSelected()));
    connect(pointList,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(pointHasBeenDoubleClicked()));
    bezierCurveTreeList = new QTreeWidget;
    bezierCurveTreeList->setFixedHeight(150);
    bezierCurveTreeList->header()->close();
    connect(bezierCurveTreeList, SIGNAL(clicked(QModelIndex)),this, SLOT(bezierCurveHasBeenClicked()));  
    bSplineCurveTreeList = new QTreeWidget;
    bSplineCurveTreeList->setFixedHeight(150);
    bSplineCurveTreeList->header()->close();
    connect(bSplineCurveTreeList,SIGNAL(clicked(QModelIndex)),this,SLOT(bSplineHasBeenClicked()));
    interBSplineCurveTreeList = new QTreeWidget;
    interBSplineCurveTreeList->setFixedHeight(150);
    interBSplineCurveTreeList->header()->close();
    connect(interBSplineCurveTreeList,SIGNAL(clicked(QModelIndex)),this,SLOT(interBSplineHasBeenClicked()));
    bezierSurfaceTreeList = new QTreeWidget;
    bezierSurfaceTreeList->setFixedHeight(150);
    bezierSurfaceTreeList->header()->close();
    connect(bezierSurfaceTreeList,SIGNAL(clicked(QModelIndex)),this,SLOT(bezierSurfaceHasBeenClicked()));
    //connect
    torusLayout->addWidget(torusListLabel);
    torusLayout->addWidget(torusList);

    pointLayout->addWidget(pointListLabel);
    pointLayout->addWidget(pointList);

    curveLayout->addWidget(bezierListLabel);
    curveLayout->addWidget(bezierCurveTreeList);

    bSplineLayout->addWidget(bSplineListLabel);
    bSplineLayout->addWidget(bSplineCurveTreeList);

    interBSplineLayout->addWidget(interBSplineListLabel);
    interBSplineLayout->addWidget(interBSplineCurveTreeList);

    bezierSurfaceLayout->addWidget(bezierSurfaceListLabel);
    bezierSurfaceLayout->addWidget(bezierSurfaceTreeList);

    mainLayout = new QVBoxLayout;


    widgetContainerLayout->minimumSize().setHeight(1000);
    widgetContainerLayout->addLayout(torusLayout);
    widgetContainerLayout->addLayout(pointLayout);
    widgetContainerLayout->addLayout(curveLayout);
    widgetContainerLayout->addLayout(bSplineLayout);
    widgetContainerLayout->addLayout(interBSplineLayout);
    widgetContainerLayout->addLayout(bezierSurfaceLayout);
    widgetContainerLayout->setMargin(0);
    scrollWidget = new QWidget;
    scrollWidget->setLayout(widgetContainerLayout);
    scrollWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //scrollArea->setFixedHeight(1000);
    QSizePolicy policy = scrollArea->sizePolicy();
    policy.setVerticalStretch(1);
    policy.setHorizontalStretch(1);

    updateLayoutHeight(600);

    QVBoxLayout* scrollLayout = new QVBoxLayout;
    scrollLayout->addWidget(scrollArea);
    mainLayout->addLayout(scrollLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);
}

///SLOTS

void ObjectListsWidget::updateListsContent()
{
    torusList->clear();
    pointList->clear();
    bezierCurveTreeList->clear();
    bSplineCurveTreeList->clear();
    interBSplineCurveTreeList->clear();
    bezierSurfaceTreeList->clear();

    for(int i=0;i<drawableObjectsData.torusList.size();i++)
    {
        torusList->addItem( QString::fromStdString(drawableObjectsData.torusList[i]->name));
    }

    for(int i=0; i<drawableObjectsData.pointList.size();i++)
    {
        pointList->addItem(QString::fromStdString(drawableObjectsData.pointList[i]->name));
    }

    for(int i=0; i<drawableObjectsData.bezierCurveList.size();i++)
    {
        addBezierCurveToList((BezierCurve*)drawableObjectsData.bezierCurveList[i],bezierCurveTreeList,
                             QString::fromStdString(drawableObjectsData.bezierCurveList[i]->name));
    }

    for(int i=0; i<drawableObjectsData.bSplineList.size(); i++)
    {
        addBSplineTolist((BSpline*)drawableObjectsData.bSplineList[i],bSplineCurveTreeList,
                         QString::fromStdString(drawableObjectsData.bSplineList[i]->name));
    }

    for(int i=0; i<drawableObjectsData.interBSplineList.size(); i++)
    {
        addInterBSplineTolist((InterBSpline*)drawableObjectsData.interBSplineList[i],interBSplineCurveTreeList,
                              QString::fromStdString(drawableObjectsData.interBSplineList[i]->name));
    }

    for(int i=0; i<drawableObjectsData.bezierSurfaceList.size();i++)
    {
        addBezierSurfaceTolist((BezierSurface*)drawableObjectsData.bezierSurfaceList[i],bezierSurfaceTreeList,
                               QString::fromStdString(drawableObjectsData.bezierSurfaceList[i]->name));
    }

}

void ObjectListsWidget::torusHasBeenSelected()
{
    drawableObjectsData.deselectObjects(TORUS);
    QList<QListWidgetItem *> itemList = torusList->selectedItems();
    for (int i=0; i<itemList.size(); i++) {
        drawableObjectsData.selectObjectByName(TORUS,itemList[i]->text().toStdString());
    }
}

void ObjectListsWidget::torusHasBeenDoubleClicked()
{
    drawableObjectsData.deselectObjects(TORUS);
    QList<QListWidgetItem *> itemList = torusList->selectedItems();
    for (int i=0; i<itemList.size(); i++) {
        drawableObjectsData.selectObjectByName(TORUS,itemList[i]->text().toStdString());
        drawableObjectsData.moveCursorToTorusByName(itemList[i]->text().toStdString());
    }
}

void ObjectListsWidget::pointHasBeenSelected()
{
    drawableObjectsData.deselectObjects(POINT);
    QList<QListWidgetItem *> itemList = pointList->selectedItems();
    for (int i=0; i<itemList.size(); i++) {
        drawableObjectsData.selectObjectByName(POINT,itemList[i]->text().toStdString());
    }
}

void ObjectListsWidget::pointHasBeenDoubleClicked()
{
    drawableObjectsData.deselectObjects(POINT);
    QList<QListWidgetItem *> itemList = pointList->selectedItems();
    for (int i=0; i<itemList.size(); i++) {
        drawableObjectsData.selectObjectByName(POINT,itemList[i]->text().toStdString());
        drawableObjectsData.moveCursorToPointByName(itemList[i]->text().toStdString());
    }
}

void ObjectListsWidget::bezierCurveHasBeenClicked()
{
    drawableObjectsData.deselectObjects(BEZIERCURVE);
    QList<QTreeWidgetItem*> itemList = bezierCurveTreeList->selectedItems();
    for(int i=0; i < itemList.size(); i++)
    {
        drawableObjectsData.selectObjectByName(BEZIERCURVE,itemList[i]->text(0).toStdString());
    }
}

void ObjectListsWidget::bSplineHasBeenClicked()
{
    drawableObjectsData.deselectObjects(BSPLINE);
    QList<QTreeWidgetItem*> itemList = bSplineCurveTreeList->selectedItems();
    for(int i=0; i < itemList.size(); i++)
    {
        drawableObjectsData.selectObjectByName(BSPLINE,itemList[i]->text(0).toStdString());
    }
}

void ObjectListsWidget::interBSplineHasBeenClicked()
{
    drawableObjectsData.deselectObjects(INTERPBSPLINE);
    QList<QTreeWidgetItem*> itemList = interBSplineCurveTreeList->selectedItems();
    for(int i=0; i < itemList.size(); i++)
    {
        drawableObjectsData.selectObjectByName(INTERPBSPLINE,itemList[i]->text(0).toStdString());
    }
}

void ObjectListsWidget::bezierSurfaceHasBeenClicked()
{
    drawableObjectsData.deselectObjects(BEZIERSURFACE);
    QList<QTreeWidgetItem*> itemList = bezierSurfaceTreeList->selectedItems();
    for(int i=0; i < itemList.size(); i++)
    {
        drawableObjectsData.selectObjectByName(BEZIERSURFACE,itemList[i]->text(0).toStdString());
    }
}

void ObjectListsWidget::deleteTorusButtonClicked()
{
    //items in lists are deseleted while deleting element (?)
    drawableObjectsData.deselectObjects(TORUS);
    drawableObjectsData.deselectObjects(POINT);
    drawableObjectsData.deselectObjects(BEZIERCURVE);


    QList<QListWidgetItem *> itemList = torusList->selectedItems();
    for (int i=0; i<itemList.size(); i++) {
            drawableObjectsData.removeObjectByName(TORUS,itemList[i]->text().toStdString());
            torusList->removeItemWidget(itemList[i]);
           // torusList->takeItem(torusList->indexFromItem(itemList[i]));
    }
    updateListsContent();
}
void ObjectListsWidget::deletePointButtonClicked()
{
    //items in lists are deseleted while deleting element (?)
    drawableObjectsData.deselectObjects(TORUS);
    drawableObjectsData.deselectObjects(POINT);

    QList<QListWidgetItem *> itemList = pointList->selectedItems();
    for (int i=0; i<itemList.size(); i++) {
        drawableObjectsData.removePointByName(itemList[i]->text().toStdString());
        pointList->removeItemWidget(itemList[i]);
      //   pointList->takeItem(pointList->indexFromItem(itemList[i]));
    }
    updateListsContent();
}

void ObjectListsWidget::deleteCurveButtonClicked()
{

    //items in lists are deseleted while deleting element (?)
    drawableObjectsData.deselectObjects(TORUS);
    drawableObjectsData.deselectObjects(POINT);

}

void ObjectListsWidget::deleteBSplineButtonClicked()
{

}

void ObjectListsWidget::deleteInterBSplineButtonClicked()
{

}

void ObjectListsWidget::deleteBezierSurfaceHasBeenClicked()
{

}

void ObjectListsWidget::pointOnSceneSelection(Point* point)
{
    for(int i=0;i<pointList->size().rheight();i++)
    {
        if(pointList->item(i)->text().toStdString() == point->name)
        {
            pointList->item(i)->setSelected(true);
            pointHasBeenSelected();
            break;
        }
    }
}

void ObjectListsWidget::pointOnSceneDoubleClick(Point * point)
{
    int height = pointList->count();
       for(int i=0;i<pointList->count();i++)
    {
        if(pointList->item(i)->text().toStdString() == point->name)
        {
            pointList->item(i)->setSelected(true);
            pointHasBeenDoubleClicked();
            break;
        }
    }
}

void ObjectListsWidget::showPointsContextMenu(const QPoint &pos)
{
        QList<QListWidgetItem *> itemList = pointList->selectedItems();
    // Handle global position
        QPoint globalPos = pointList->mapToGlobal(pos);

        // Create menu and insert some actions
        QMenu myMenu;
        if(itemList.count()>0)
        {
            QMenu* addToCurveMenu = new QMenu("Add to curve");
            ///BEZIER
            QString ch_name ;
            for(int j=0; j<bezierCurveTreeList->topLevelItemCount(); j++){
                ch_name = bezierCurveTreeList->topLevelItem(j)->text(0);
                QAction *subMenuAct = addToCurveMenu->addAction(ch_name);
                subMenuAct->setData(ch_name);
            }
            QAction *subMenuAct = addToCurveMenu->addAction(tr("Create New Bezier"));
            subMenuAct->setData(ch_name);

            connect(addToCurveMenu, SIGNAL(triggered(QAction *)),
                    this, SLOT(addToCurve(QAction *)), Qt::UniqueConnection);
            ///BSPLINE
            QMenu* addToBSplineMenu = new QMenu("Add to BSpline");
            for(int j=0; j<bSplineCurveTreeList->topLevelItemCount(); j++){
                ch_name = bSplineCurveTreeList->topLevelItem(j)->text(0);
                QAction *subMenuAct = addToBSplineMenu->addAction(ch_name);
                subMenuAct->setData(ch_name);
            }
            QAction* subMenu2Act = addToBSplineMenu->addAction(tr("Create new BSpline"));
            subMenu2Act->setData(ch_name);

            connect(addToBSplineMenu,SIGNAL(triggered(QAction*)),this,SLOT(addToBSpline(QAction*)), Qt::UniqueConnection);

            ///INTER BSPLINE
            QMenu* addToInterBSplineMenu = new QMenu("Add to InterBSpline");
            for(int j=0; j<interBSplineCurveTreeList->topLevelItemCount(); j++){
                ch_name = interBSplineCurveTreeList->topLevelItem(j)->text(0);
                QAction *subMenuAct = addToInterBSplineMenu->addAction(ch_name);
                subMenuAct->setData(ch_name);
            }
            QAction* subMenu3Act = addToInterBSplineMenu->addAction(tr("Create new InterBSpline"));
            subMenu2Act->setData(ch_name);

            connect(addToInterBSplineMenu,SIGNAL(triggered(QAction*)),this,SLOT(addToInterBSpline(QAction*)), Qt::UniqueConnection);

            myMenu.addMenu(addToCurveMenu);
            myMenu.addMenu(addToBSplineMenu);
            myMenu.addMenu(addToInterBSplineMenu);
            myMenu.addAction("Delete", this, SLOT(deletePointButtonClicked()));
        }
        if(itemList.count() == 1)
        {
            myMenu.addAction("Rename point", this, SLOT(renamePoint()));
        }

        // Show context menu at handling position
        myMenu.exec(globalPos);
}

void ObjectListsWidget::showBezierCurvesContextMenu(const QPoint &pos)
{
    QList<QTreeWidgetItem*> itemList = bezierCurveTreeList->selectedItems();
    if(itemList.size()>0){
    string name = itemList.at(0)->text(0).toStdString();

    // Handle global position
        QPoint globalPos = bezierCurveTreeList->mapToGlobal(pos);

        // Create menu and insert some actions
        QMenu myMenu;
        if(name[0] == 'B')
        {
            myMenu.addAction("RemoveCurve", this, SLOT(removeBezierCurve()));
            myMenu.addAction("Turn on/off polygon", this, SLOT(turnOnOffBezierPolygon()));

          //  myMenu.addAction("Erase",  this, SLOT(eraseBezierCurveListItem()));
        }
        else
        {
            string parentName = itemList.at(0)->parent()->text(0).toStdString();
            myMenu.addAction("Remove point", this, SLOT(removePointFromBezierCurve()));
        }


        // Show context menu at handling position
        myMenu.exec(globalPos);
    }
}

void ObjectListsWidget::showBSplineContextMenu(const QPoint &pos)
{
    QList<QTreeWidgetItem*> itemList = bSplineCurveTreeList->selectedItems();
    if(itemList.size()>0){
    string name = itemList.at(0)->text(0).toStdString();

    // Handle global position
        QPoint globalPos = bSplineCurveTreeList->mapToGlobal(pos);

        // Create menu and insert some actions
        QMenu myMenu;
        if(name[0] == 'B')
        {
            myMenu.addAction("Remove BSpline", this, SLOT(removeBSpline()));
            myMenu.addAction("Turn on/off polygon", this, SLOT(turnOnOffBSplinePolygon()));

          //  myMenu.addAction("Erase",  this, SLOT(eraseBezierCurveListItem()));
        }
        else
        {
            string parentName = itemList.at(0)->parent()->text(0).toStdString();
            myMenu.addAction("Remove point", this, SLOT(removePointFromBSpline()));
        }


        // Show context menu at handling position
        myMenu.exec(globalPos);
    }
}

void ObjectListsWidget::showInterBSplineContextMenu(const QPoint &pos)
{
    QList<QTreeWidgetItem*> itemList = interBSplineCurveTreeList->selectedItems();
    if(itemList.size()>0){
    string name = itemList.at(0)->text(0).toStdString();

    // Handle global position
        QPoint globalPos = interBSplineCurveTreeList->mapToGlobal(pos);

        // Create menu and insert some actions
        QMenu myMenu;
        if(name[0] == 'I')
        {
            myMenu.addAction("Remove BSpline", this, SLOT(removeInterBSpline()));
            myMenu.addAction("Turn on/off polygon", this, SLOT(turnOnOffInterBSplinePolygon()));

          //  myMenu.addAction("Erase",  this, SLOT(eraseBezierCurveListItem()));
        }
        else
        {
            string parentName = itemList.at(0)->parent()->text(0).toStdString();
            myMenu.addAction("Remove point", this, SLOT(removePointFromInterBSpline()));
        }


        // Show context menu at handling position
        myMenu.exec(globalPos);
    }
}

void ObjectListsWidget::showBezierSurfaceContextMenu(const QPoint &pos)
{
    QList<QTreeWidgetItem*> itemList = bezierSurfaceTreeList->selectedItems();
    if(itemList.size()>0){
    string name = itemList.at(0)->text(0).toStdString();

    // Handle global position
        QPoint globalPos = bezierSurfaceTreeList->mapToGlobal(pos);

        // Create menu and insert some actions
        QMenu myMenu;
        if(name[0] == 'C')
        {
            myMenu.addAction("Remove Bezier Surface", this, SLOT(removeBezierSurface()));
            myMenu.addAction("Turn on/off Bezier Net", this, SLOT(turnOnBezierNet()));

          //  myMenu.addAction("Erase",  this, SLOT(eraseBezierCurveListItem()));
        }
       /* else
        {
            string parentName = itemList.at(0)->parent()->text(0).toStdString();
            myMenu.addAction("Remove point", this, SLOT(removePointFromInterBSpline()));
        }*/


        // Show context menu at handling position
        myMenu.exec(globalPos);
    }
}

void ObjectListsWidget::drawableHasBeenRenamed()
{
    updateListsContent();
}

///POINT LIST SLOTS

void ObjectListsWidget::addToCurve(QAction * act)
{
    QList<QListWidgetItem*> listItem = pointList->selectedItems();
    Point* point = (Point*)drawableObjectsData.getObjectByName(POINT,listItem.at(0)->text().toStdString());
    string curveName = act->text().toStdString();
    if(curveName != "Create New Bezier")
    {
        BezierCurve* bezierCurve = (BezierCurve*)drawableObjectsData.getObjectByName(BEZIERCURVE,curveName);
        for(int i=0;i<listItem.count();i++)
        {
            point = (Point*)drawableObjectsData.getObjectByName(POINT,listItem.at(i)->text().toStdString());
            drawableObjectsData.addPointToBezierCurve(bezierCurve,point);
        }
    }
    else
    {
        BezierCurve* bezierCurve = new BezierCurve(drawableObjectsData.camera);
        drawableObjectsData.addObject(BEZIERCURVE,bezierCurve);
        for(int i=0;i<listItem.count();i++)
        {
            point = (Point*)drawableObjectsData.getObjectByName(POINT,listItem.at(i)->text().toStdString());
            drawableObjectsData.addPointToBezierCurve(bezierCurve,point);
        }
    }
     drawableObjectsData.deselectObjects(TORUS);
     drawableObjectsData.deselectObjects(POINT);
     drawableObjectsData.deselectObjects(BEZIERCURVE);
     updateListsContent();
}

void ObjectListsWidget::addToBSpline(QAction * act)
{
    QList<QListWidgetItem*> listItem = pointList->selectedItems();
    Point* point = (Point*)drawableObjectsData.getObjectByName(POINT,listItem.at(0)->text().toStdString());
    string bSplineName = act->text().toStdString();
    if(bSplineName != "Create new BSpline")
    {
        BSpline * bSpline = (BSpline*)drawableObjectsData.getObjectByName(BSPLINE,bSplineName);
        for(int i=0;i<listItem.count();i++)
        {
            point = (Point*)drawableObjectsData.getObjectByName(POINT,listItem.at(i)->text().toStdString());
            drawableObjectsData.addPointToBSpline(bSpline,point);
        }
    }
    else
    {
        BSpline* bSpline= new BSpline(drawableObjectsData.camera);
        drawableObjectsData.addObject(BSPLINE,bSpline);
        for(int i=0;i<listItem.count();i++)
        {
            point = (Point*)drawableObjectsData.getObjectByName(POINT,listItem.at(i)->text().toStdString());
            drawableObjectsData.addPointToBSpline(bSpline,point);
        }
    }
     drawableObjectsData.deselectObjects(TORUS);
     drawableObjectsData.deselectObjects(POINT);
     drawableObjectsData.deselectObjects(BEZIERCURVE);
     drawableObjectsData.deselectObjects(BSPLINE);
     updateListsContent();
}

void ObjectListsWidget::addToInterBSpline(QAction * act)
{
    QList<QListWidgetItem*> listItem = pointList->selectedItems();
    Point* point = (Point*)drawableObjectsData.getObjectByName(POINT,listItem.at(0)->text().toStdString());
    string interBSplineName = act->text().toStdString();
    if(interBSplineName != "Create new InterBSpline")
    {
        InterBSpline * interBSpline = (InterBSpline*)drawableObjectsData.getObjectByName(INTERPBSPLINE,interBSplineName);
        for(int i=0;i<listItem.count();i++)
        {
            point = (Point*)drawableObjectsData.getObjectByName(POINT,listItem.at(i)->text().toStdString());
            drawableObjectsData.addPointToInterBSpline(interBSpline,point);
        }
    }
    else
    {
        InterBSpline* interBSpline= new InterBSpline(drawableObjectsData.camera);
        drawableObjectsData.addObject(INTERPBSPLINE,interBSpline);
        for(int i=0;i<listItem.count();i++)
        {
            point = (Point*)drawableObjectsData.getObjectByName(POINT,listItem.at(i)->text().toStdString());
            drawableObjectsData.addPointToInterBSpline(interBSpline,point);
        }
    }
     drawableObjectsData.deselectObjects(TORUS);
     drawableObjectsData.deselectObjects(POINT);
     drawableObjectsData.deselectObjects(BEZIERCURVE);
     drawableObjectsData.deselectObjects(BSPLINE);
     drawableObjectsData.deselectObjects(INTERPBSPLINE);
     updateListsContent();
}

void ObjectListsWidget::renamePoint()
{
    QList<QListWidgetItem*> itemList = pointList->selectedItems();
    Point* point = (Point*)drawableObjectsData.getObjectByName(POINT,itemList.at(0)->text().toStdString());
    nameChangeDialog->setDrawable(point);
    nameChangeDialog->show();
}

//BEZIER CURVE TREE WIDGET SLOTS
void ObjectListsWidget::addBezierCurveListItem()
{

}

void ObjectListsWidget::removeBezierCurve()
{
    QList<QTreeWidgetItem*> itemList = bezierCurveTreeList->selectedItems();
    string name = itemList.at(0)->text(0).toStdString();

    drawableObjectsData.removeObjectByName(BEZIERCURVE,name);
    updateListsContent();
}

void ObjectListsWidget::removePointFromBezierCurve()
{
    QList<QTreeWidgetItem*> itemList = bezierCurveTreeList->selectedItems();
    string name = itemList.at(0)->text(0).toStdString();
    string parentName = itemList.at(0)->parent()->text(0).toStdString();


    BezierCurve* bezierCurve = (BezierCurve*)drawableObjectsData.getObjectByName(BEZIERCURVE,parentName);
    std::vector<Point*>::iterator position = bezierCurve->pointVector.begin();
    for(int i=0;i<bezierCurve->pointVector.size();i++)
    {

        if(bezierCurve->pointVector[i]->name == name)
        {
            position = position + i;
            bezierCurve->pointVector.erase(position);
        }
    }
    updateListsContent();
}

void ObjectListsWidget::turnOnOffBezierPolygon()
{
    QList<QTreeWidgetItem*> itemList = bezierCurveTreeList->selectedItems();
    string name = itemList.at(0)->text(0).toStdString();
    BezierCurve* bezierCurve = (BezierCurve*)drawableObjectsData.getObjectByName(BEZIERCURVE,name);
    if(bezierCurve->drawPolygon == true)
    {
        bezierCurve->drawPolygon = false;
    }
    else
    {
        bezierCurve->drawPolygon = true;
    }
}
//BSPLINE TREE WIDGET SLOTS

void ObjectListsWidget::addBSplineListItem()
{

}

void ObjectListsWidget::removeBSpline()
{
    QList<QTreeWidgetItem*> itemList = bSplineCurveTreeList->selectedItems();
    string name = itemList.at(0)->text(0).toStdString();

    drawableObjectsData.removeObjectByName(BSPLINE,name);
    updateListsContent();
}

void ObjectListsWidget::removePointFromBSpline()
{
    QList<QTreeWidgetItem*> itemList = bSplineCurveTreeList->selectedItems();
    string name = itemList.at(0)->text(0).toStdString();
    string parentName = itemList.at(0)->parent()->text(0).toStdString();


    BSpline* bSpline = (BSpline*)drawableObjectsData.getObjectByName(BSPLINE,parentName);
    std::vector<Point*>::iterator position = bSpline->deBoorPoints.begin();
    for(int i=0;i<bSpline->deBoorPoints.size();i++)
    {

        if(bSpline->deBoorPoints[i]->name == name)
        {
            position = position + i;
            bSpline->deBoorPoints.erase(position);
        }
    }
    updateListsContent();
}
void ObjectListsWidget::turnOnOffBSplinePolygon()
{
    QList<QTreeWidgetItem*> itemList = bSplineCurveTreeList->selectedItems();
    string name = itemList.at(0)->text(0).toStdString();
    BSpline* bSpline = (BSpline*)drawableObjectsData.getObjectByName(BSPLINE,name);
    if(bSpline->drawPolygon == true)
    {
        bSpline->drawPolygon = false;
    }
    else
    {
        bSpline->drawPolygon = true;
    }
}

//INTER BSPLINE TREE WIDGET SLOTS

void ObjectListsWidget::addInterBSplineListItem()
{

}

void ObjectListsWidget::removeInterBSpline()
{
    QList<QTreeWidgetItem*> itemList = interBSplineCurveTreeList->selectedItems();
    string name = itemList.at(0)->text(0).toStdString();

    drawableObjectsData.removeObjectByName(INTERPBSPLINE,name);
    updateListsContent();
}

void ObjectListsWidget::removePointFromInterBSpline()
{
    QList<QTreeWidgetItem*> itemList = interBSplineCurveTreeList->selectedItems();
    string name = itemList.at(0)->text(0).toStdString();
    string parentName = itemList.at(0)->parent()->text(0).toStdString();


    InterBSpline* interBSpline = (InterBSpline*)drawableObjectsData.getObjectByName(INTERPBSPLINE,parentName);
    std::vector<Point*>::iterator position = interBSpline->deBoorPoints.begin();
    for(int i=0;i<interBSpline->deBoorPoints.size();i++)
    {

        if(interBSpline->deBoorPoints[i]->name == name)
        {
            position = position + i;
            interBSpline->deBoorPoints.erase(position);
        }
    }
    updateListsContent();
}
void ObjectListsWidget::turnOnOffInterBSplinePolygon()
{
    QList<QTreeWidgetItem*> itemList = interBSplineCurveTreeList->selectedItems();
    string name = itemList.at(0)->text(0).toStdString();
    InterBSpline* interBSpline = (InterBSpline*)drawableObjectsData.getObjectByName(INTERPBSPLINE,name);
    if(interBSpline->drawPolygon == true)
    {
        interBSpline->drawPolygon = false;
    }
    else
    {
        interBSpline->drawPolygon = true;
    }
}
//BEZIER SURFACE TREE WIDGET SLOTS

void ObjectListsWidget::removeBezierSurface()
{
    QList<QTreeWidgetItem*> itemList = bezierSurfaceTreeList->selectedItems();
    string name = itemList.at(0)->text(0).toStdString();

    drawableObjectsData.removeBezierSurfaceByName(name);
    updateListsContent();
}

void ObjectListsWidget::turnOnBezierNet()
{
    QList<QTreeWidgetItem*> itemList = bezierSurfaceTreeList->selectedItems();
    string name = itemList.at(0)->text(0).toStdString();
    BezierSurface* bezierSurface = (BezierSurface*)drawableObjectsData.getObjectByName(BEZIERSURFACE,name);
    if(bezierSurface->drawBezierNet == true)
    {
        bezierSurface->drawBezierNet = false;
    }
    else
    {
        bezierSurface->drawBezierNet = true;
    }
}

///NORMAL METHODS

void ObjectListsWidget::addBezierCurveToList(BezierCurve* bezierCurve, QTreeWidget* parent, QString name)
{
    QTreeWidgetItem* treeWidgetItem = new QTreeWidgetItem(parent);
    treeWidgetItem->setText(0, name);
    for(int i=0;i<bezierCurve->pointVector.size();i++)
    {
        addPointToCurve(treeWidgetItem,QString::fromStdString(bezierCurve->pointVector[i]->name));
    }
    parent->addTopLevelItem(treeWidgetItem);

}

void ObjectListsWidget::addPointToCurve(QTreeWidgetItem* parent, QString name)
{
    QTreeWidgetItem* treeWidgetItem = new QTreeWidgetItem(parent);
    treeWidgetItem->setText(0, name);
    parent->addChild(treeWidgetItem);
}


void ObjectListsWidget::addBSplineTolist(BSpline *bSpline, QTreeWidget *parent, QString name)
{
    QTreeWidgetItem* treeWidgetItem = new QTreeWidgetItem(parent);
    treeWidgetItem->setText(0, name);
    for(int i=0;i<bSpline->deBoorPoints.size();i++)
    {
        addPointToCurve(treeWidgetItem,QString::fromStdString(bSpline->deBoorPoints[i]->name));
    }
    parent->addTopLevelItem(treeWidgetItem);
}

void ObjectListsWidget::addInterBSplineTolist(InterBSpline *interBSpline, QTreeWidget *parent, QString name)
{
    QTreeWidgetItem* treeWidgetItem = new QTreeWidgetItem(parent);
    treeWidgetItem->setText(0, name);
    for(int i=0;i<interBSpline->deBoorPoints.size();i++)
    {
        addPointToCurve(treeWidgetItem,QString::fromStdString(interBSpline->deBoorPoints[i]->name));
    }
    parent->addTopLevelItem(treeWidgetItem);
}

void ObjectListsWidget::addBezierSurfaceTolist(BezierSurface* bezierSurface, QTreeWidget* parent, QString name)
{
    QTreeWidgetItem* treeWidgetItem = new QTreeWidgetItem(parent);
    treeWidgetItem->setText(0, name);
    for(int i=0;i<bezierSurface->controlPoints.size();i++)
    {
        addPointToCurve(treeWidgetItem,QString::fromStdString(bezierSurface->controlPoints[i]->name));
    }
    parent->addTopLevelItem(treeWidgetItem);
}

void ObjectListsWidget::updateLayoutHeight(int height)
{
    scrollArea->setFixedHeight(height);
}






