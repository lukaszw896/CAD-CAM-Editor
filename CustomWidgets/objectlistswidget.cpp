#include "objectlistswidget.h"

ObjectListsWidget::ObjectListsWidget()
{
    setupButtons();
    setupGroupBoxes();
    setupLayout();
    updateListsContent();
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
    pointList->setSelectionMode(QAbstractItemView::MultiSelection);
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
