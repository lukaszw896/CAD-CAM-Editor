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
    connect(torusList,SIGNAL(clicked(QModelIndex)),this,SLOT(torusHasBeenSelected()));
    connect(torusList,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(torusHasBeenDoubleClicked()));
    pointList = new QListWidget;
    pointList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    connect(pointList,SIGNAL(clicked(QModelIndex)),this,SLOT(pointHasBeenSelected()));
    connect(pointList,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(pointHasBeenDoubleClicked()));
    bezierCurveTreeList = new QTreeWidget;
    connect(bezierCurveTreeList, SIGNAL(clicked(QModelIndex)),this, SLOT(bezierCurveHasBeenClicked()));  
    bSplineCurveTreeList = new QTreeWidget;
    connect(bSplineCurveTreeList,SIGNAL(clicked(QModelIndex)),this,SLOT(bSplineHasBeenClicked()));
    interBSplineCurveTreeList = new QTreeWidget;
    connect(interBSplineCurveTreeList,SIGNAL(clicked(QModelIndex)),this,SLOT(interBSplineHasBeenClicked()));
    bezierSurfaceTreeList = new QTreeWidget;
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



    mainLayout->addLayout(torusLayout);
    mainLayout->addLayout(pointLayout);
    mainLayout->addLayout(curveLayout);
    mainLayout->addLayout(bSplineLayout);
    mainLayout->addLayout(interBSplineLayout);
    mainLayout->addLayout(bezierSurfaceLayout);
    /*scrollArea->setLayout(widgetContainerLayout);
    scrollArea->setWidgetResizable(true);
    QSizePolicy policy = scrollArea->sizePolicy();

    policy.setVerticalStretch(1);
    policy.setHorizontalStretch(1);

    scrollArea->minimumSize().setHeight(500);
    mainLayout->minimumSize().setHeight(500);

    mainLayout->addWidget(scrollArea);*/

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
        addBezierCurveToList(drawableObjectsData.bezierCurveList[i],bezierCurveTreeList,
                             QString::fromStdString(drawableObjectsData.bezierCurveList[i]->name));
    }

    for(int i=0; i<drawableObjectsData.bSplineList.size(); i++)
    {
        addBSplineTolist(drawableObjectsData.bSplineList[i],bSplineCurveTreeList,
                         QString::fromStdString(drawableObjectsData.bSplineList[i]->name));
    }

    for(int i=0; i<drawableObjectsData.interBSplineList.size(); i++)
    {
        addInterBSplineTolist(drawableObjectsData.interBSplineList[i],interBSplineCurveTreeList,
                              QString::fromStdString(drawableObjectsData.interBSplineList[i]->name));
    }

    for(int i=0; i<drawableObjectsData.bezierSurfaceList.size();i++)
    {
        addBezierSurfaceTolist(drawableObjectsData.bezierSurfaceList[i],bezierSurfaceTreeList,
                               QString::fromStdString(drawableObjectsData.bezierSurfaceList[i]->name));
    }

}

void ObjectListsWidget::torusHasBeenSelected()
{
    drawableObjectsData.deselectToruses();
    QList<QListWidgetItem *> itemList = torusList->selectedItems();
    for (int i=0; i<itemList.size(); i++) {
        drawableObjectsData.selectTorusByName(itemList[i]->text().toStdString());
    }
}

void ObjectListsWidget::torusHasBeenDoubleClicked()
{
    drawableObjectsData.deselectToruses();
    QList<QListWidgetItem *> itemList = torusList->selectedItems();
    for (int i=0; i<itemList.size(); i++) {
        drawableObjectsData.selectTorusByName(itemList[i]->text().toStdString());
        drawableObjectsData.moveCursorToTorusByName(itemList[i]->text().toStdString());
    }
}

void ObjectListsWidget::pointHasBeenSelected()
{
    drawableObjectsData.deselectPoints();
    QList<QListWidgetItem *> itemList = pointList->selectedItems();
    for (int i=0; i<itemList.size(); i++) {
        drawableObjectsData.selectPointByName(itemList[i]->text().toStdString());
    }
}

void ObjectListsWidget::pointHasBeenDoubleClicked()
{
    drawableObjectsData.deselectPoints();
    QList<QListWidgetItem *> itemList = pointList->selectedItems();
    for (int i=0; i<itemList.size(); i++) {
        drawableObjectsData.selectPointByName(itemList[i]->text().toStdString());
        drawableObjectsData.moveCursorToPointByName(itemList[i]->text().toStdString());
    }
}

void ObjectListsWidget::bezierCurveHasBeenClicked()
{
    drawableObjectsData.deselectBezierCurves();
    QList<QTreeWidgetItem*> itemList = bezierCurveTreeList->selectedItems();
    for(int i=0; i < itemList.size(); i++)
    {
        drawableObjectsData.selectBezierCurveByName(itemList[i]->text(0).toStdString());
    }
}

void ObjectListsWidget::bSplineHasBeenClicked()
{
    drawableObjectsData.deselectBSplines();
    QList<QTreeWidgetItem*> itemList = bSplineCurveTreeList->selectedItems();
    for(int i=0; i < itemList.size(); i++)
    {
        drawableObjectsData.selectBSplineByName(itemList[i]->text(0).toStdString());
    }
}

void ObjectListsWidget::interBSplineHasBeenClicked()
{
    drawableObjectsData.deselectInterBSplines();
    QList<QTreeWidgetItem*> itemList = interBSplineCurveTreeList->selectedItems();
    for(int i=0; i < itemList.size(); i++)
    {
        drawableObjectsData.selectInterBSplineByName(itemList[i]->text(0).toStdString());
    }
}

void ObjectListsWidget::bezierSurfaceHasBeenClicked()
{
    drawableObjectsData.deselectBezierSurface();
    QList<QTreeWidgetItem*> itemList = bezierSurfaceTreeList->selectedItems();
    for(int i=0; i < itemList.size(); i++)
    {
        drawableObjectsData.selectBezierSurfaceByName(itemList[i]->text(0).toStdString());
    }
}

void ObjectListsWidget::deleteTorusButtonClicked()
{
    //items in lists are deseleted while deleting element (?)
    drawableObjectsData.deselectToruses();
    drawableObjectsData.deselectPoints();
    drawableObjectsData.deselectBezierCurves();


    QList<QListWidgetItem *> itemList = torusList->selectedItems();
    for (int i=0; i<itemList.size(); i++) {
            drawableObjectsData.removeTorusByName(itemList[i]->text().toStdString());
            torusList->removeItemWidget(itemList[i]);
           // torusList->takeItem(torusList->indexFromItem(itemList[i]));
    }
    updateListsContent();
}
void ObjectListsWidget::deletePointButtonClicked()
{
    //items in lists are deseleted while deleting element (?)
    drawableObjectsData.deselectToruses();
    drawableObjectsData.deselectPoints();

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
    drawableObjectsData.deselectToruses();
    drawableObjectsData.deselectPoints();

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
    for(int i=0;i<pointList->size().rheight();i++)
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
    Point* point = drawableObjectsData.getPointByName(listItem.at(0)->text().toStdString());
    string curveName = act->text().toStdString();
    if(curveName != "Create New Bezier")
    {
        BezierCurve* bezierCurve = drawableObjectsData.getBezierCurveByName(curveName);
        for(int i=0;i<listItem.count();i++)
        {
            point = drawableObjectsData.getPointByName(listItem.at(i)->text().toStdString());
            drawableObjectsData.addPointToBezierCurve(bezierCurve,point);
        }
    }
    else
    {
        BezierCurve* bezierCurve = new BezierCurve(drawableObjectsData.camera);
        drawableObjectsData.addBezierCurve(bezierCurve);
        for(int i=0;i<listItem.count();i++)
        {
            point = drawableObjectsData.getPointByName(listItem.at(i)->text().toStdString());
            drawableObjectsData.addPointToBezierCurve(bezierCurve,point);
        }
    }
     drawableObjectsData.deselectToruses();
     drawableObjectsData.deselectPoints();
     drawableObjectsData.deselectBezierCurves();
     updateListsContent();
}

void ObjectListsWidget::addToBSpline(QAction * act)
{
    QList<QListWidgetItem*> listItem = pointList->selectedItems();
    Point* point = drawableObjectsData.getPointByName(listItem.at(0)->text().toStdString());
    string bSplineName = act->text().toStdString();
    if(bSplineName != "Create new BSpline")
    {
        BSpline * bSpline = drawableObjectsData.getBSplineByName(bSplineName);
        for(int i=0;i<listItem.count();i++)
        {
            point = drawableObjectsData.getPointByName(listItem.at(i)->text().toStdString());
            drawableObjectsData.addPointToBSpline(bSpline,point);
        }
    }
    else
    {
        BSpline* bSpline= new BSpline(drawableObjectsData.camera);
        drawableObjectsData.addBSpline(bSpline);
        for(int i=0;i<listItem.count();i++)
        {
            point = drawableObjectsData.getPointByName(listItem.at(i)->text().toStdString());
            drawableObjectsData.addPointToBSpline(bSpline,point);
        }
    }
     drawableObjectsData.deselectToruses();
     drawableObjectsData.deselectPoints();
     drawableObjectsData.deselectBezierCurves();
     drawableObjectsData.deselectBSplines();
     updateListsContent();
}

void ObjectListsWidget::addToInterBSpline(QAction * act)
{
    QList<QListWidgetItem*> listItem = pointList->selectedItems();
    Point* point = drawableObjectsData.getPointByName(listItem.at(0)->text().toStdString());
    string interBSplineName = act->text().toStdString();
    if(interBSplineName != "Create new InterBSpline")
    {
        InterBSpline * interBSpline = drawableObjectsData.getInterBSplineByName(interBSplineName);
        for(int i=0;i<listItem.count();i++)
        {
            point = drawableObjectsData.getPointByName(listItem.at(i)->text().toStdString());
            drawableObjectsData.addPointToInterBSpline(interBSpline,point);
        }
    }
    else
    {
        InterBSpline* interBSpline= new InterBSpline(drawableObjectsData.camera);
        drawableObjectsData.addInterBSpline(interBSpline);
        for(int i=0;i<listItem.count();i++)
        {
            point = drawableObjectsData.getPointByName(listItem.at(i)->text().toStdString());
            drawableObjectsData.addPointToInterBSpline(interBSpline,point);
        }
    }
     drawableObjectsData.deselectToruses();
     drawableObjectsData.deselectPoints();
     drawableObjectsData.deselectBezierCurves();
     drawableObjectsData.deselectBSplines();
     drawableObjectsData.deselectInterBSplines();
     updateListsContent();
}

void ObjectListsWidget::renamePoint()
{
    QList<QListWidgetItem*> itemList = pointList->selectedItems();
    Point* point = drawableObjectsData.getPointByName(itemList.at(0)->text().toStdString());
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

    drawableObjectsData.removeBezierCurveByName(name);
    updateListsContent();
}

void ObjectListsWidget::removePointFromBezierCurve()
{
    QList<QTreeWidgetItem*> itemList = bezierCurveTreeList->selectedItems();
    string name = itemList.at(0)->text(0).toStdString();
    string parentName = itemList.at(0)->parent()->text(0).toStdString();


    BezierCurve* bezierCurve = drawableObjectsData.getBezierCurveByName(parentName);
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
    BezierCurve* bezierCurve = drawableObjectsData.getBezierCurveByName(name);
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

    drawableObjectsData.removeBSplineByName(name);
    updateListsContent();
}

void ObjectListsWidget::removePointFromBSpline()
{
    QList<QTreeWidgetItem*> itemList = bSplineCurveTreeList->selectedItems();
    string name = itemList.at(0)->text(0).toStdString();
    string parentName = itemList.at(0)->parent()->text(0).toStdString();


    BSpline* bSpline = drawableObjectsData.getBSplineByName(parentName);
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
    BSpline* bSpline = drawableObjectsData.getBSplineByName(name);
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

    drawableObjectsData.removeInterBSplineByName(name);
    updateListsContent();
}

void ObjectListsWidget::removePointFromInterBSpline()
{
    QList<QTreeWidgetItem*> itemList = interBSplineCurveTreeList->selectedItems();
    string name = itemList.at(0)->text(0).toStdString();
    string parentName = itemList.at(0)->parent()->text(0).toStdString();


    InterBSpline* interBSpline = drawableObjectsData.getInterBSplineByName(parentName);
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
    InterBSpline* interBSpline = drawableObjectsData.getInterBSplineByName(name);
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
    BezierSurface* bezierSurface = drawableObjectsData.getBezierSurfaceByName(name);
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





