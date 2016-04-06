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
    //pointList->setSelectionMode(QAbstractItemView::MultiSelection);
    connect(pointList,SIGNAL(clicked(QModelIndex)),this,SLOT(pointHasBeenSelected()));
    connect(pointList,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(pointHasBeenDoubleClicked()));
    curveList = new QListWidget;

    torusLayout->addWidget(torusList);
    torusLayout->addWidget(deleteTorusButton);
    pointLayout->addWidget(pointList);
    pointLayout->addWidget(deletePointButton);
    curveLayout->addWidget(curveList);
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

    for(int i=0;i<drawableObjectsData.torusList.size();i++)
    {
        torusList->addItem( QString::fromStdString(drawableObjectsData.torusList[i]->name));
    }

    for(int i=0; i<drawableObjectsData.pointList.size();i++)
    {
        pointList->addItem(QString::fromStdString(drawableObjectsData.pointList[i]->name));
    }

}

void ObjectListsWidget::torusHasBeenSelected()
{

}

void ObjectListsWidget::torusHasBeenDoubleClicked()
{

}

void ObjectListsWidget::pointHasBeenSelected()
{

}

void ObjectListsWidget::pointHasBeenDoubleClicked()
{

}

void ObjectListsWidget::deleteTorusButtonClicked()
{
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

}

