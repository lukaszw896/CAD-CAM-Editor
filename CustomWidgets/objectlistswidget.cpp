#include "objectlistswidget.h"

ObjectListsWidget::ObjectListsWidget()
{
    setupButtons();
    setupGroupBoxes();
    setupLayout();
    updateListsContent();

    pointList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(pointList,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showPointsContextMenu(QPoint)));

    bezierCurveTreeList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(bezierCurveTreeList,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showBezierCurvesContextMenu(QPoint)));
}

void ObjectListsWidget::setupButtons()
{
   deleteTorusButton = new QPushButton("Delete");
   connect(deleteTorusButton,SIGNAL(clicked(bool)),this,SLOT(deleteTorusButtonClicked()));
   deletePointButton = new QPushButton("Delete");
   connect(deletePointButton,SIGNAL(clicked(bool)),this,SLOT(deletePointButtonClicked()));
   deleteCurveButton = new QPushButton("Delete");
   connect(deleteCurveButton,SIGNAL(clicked(bool)),this,SLOT(deleteCurveButtonClicked()));

}

void ObjectListsWidget::setupGroupBoxes()
{
    torusGroupBox = new QGroupBox(tr("Tours List"));

    pointGroupBox = new QGroupBox(tr("Point List"));

    curveGroupBox = new QGroupBox(tr("Curve List"));
}

void ObjectListsWidget::setupLayout()
{
    torusLayout = new QVBoxLayout;
    pointLayout = new QVBoxLayout;
    curveLayout = new QVBoxLayout;

    torusGroupBox->setLayout(torusLayout);
    pointGroupBox->setLayout(pointLayout);
    curveGroupBox->setLayout(curveLayout);

    torusList = new QListWidget;
    connect(torusList,SIGNAL(clicked(QModelIndex)),this,SLOT(torusHasBeenSelected()));
    connect(torusList,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(torusHasBeenDoubleClicked()));
    pointList = new QListWidget;
    pointList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    connect(pointList,SIGNAL(clicked(QModelIndex)),this,SLOT(pointHasBeenSelected()));
    connect(pointList,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(pointHasBeenDoubleClicked()));
    bezierCurveTreeList = new QTreeWidget;
    connect(bezierCurveTreeList, SIGNAL(clicked(QModelIndex)),this, SLOT(bezierCurveHasBeenClicked()));

    torusLayout->addWidget(torusList);
    torusLayout->addWidget(deleteTorusButton);
    pointLayout->addWidget(pointList);
    pointLayout->addWidget(deletePointButton);
    curveLayout->addWidget(bezierCurveTreeList);
    curveLayout->addWidget(deleteCurveButton);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(torusGroupBox);
    mainLayout->addWidget(pointGroupBox);
    mainLayout->addWidget(curveGroupBox);
    setLayout(mainLayout);
}

///SLOTS

void ObjectListsWidget::updateListsContent()
{
    torusList->clear();
    pointList->clear();
    bezierCurveTreeList->clear();

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
        addBezierCurveToList(drawableObjectsData.bezierCurveList[i],bezierCurveTreeList,QString::fromStdString(drawableObjectsData.bezierCurveList[i]->name));
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
            ///
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

            ///

            myMenu.addMenu(addToCurveMenu);
            myMenu.addAction("Delete", this, SLOT(deletePointButtonClicked()));
        }
        if(itemList.count() == 1)
        {
            myMenu.addAction("Rename point", this, SLOT(addBezierCurveListItem()));
        }

        // Show context menu at handling position
        myMenu.exec(globalPos);
}

void ObjectListsWidget::showBezierCurvesContextMenu(const QPoint &pos)
{
    // Handle global position
        QPoint globalPos = bezierCurveTreeList->mapToGlobal(pos);

        // Create menu and insert some actions
        QMenu myMenu;

        myMenu.addAction("Insert", this, SLOT(addBezierCurveListItem()));
        myMenu.addAction("Erase",  this, SLOT(eraseBezierCurveListItem()));

        // Show context menu at handling position
        myMenu.exec(globalPos);
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

//BEZIER CURVE TREE WIDGET SLOTS
void ObjectListsWidget::addBezierCurveListItem()
{

}

void ObjectListsWidget::eraseBezierCurveListItem()
{

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
