#include "objectlistswidget.h"

ObjectListsWidget::ObjectListsWidget()
{
    setupLists();
    setupGroupBoxes();
    setupLayout();
    updateListsContent();
}

void ObjectListsWidget::setupLists()
{

}

void ObjectListsWidget::setupGroupBoxes()
{
    torusGroupBox = new QGroupBox(tr("Tours List"));

    pointGroupBox = new QGroupBox(tr("Point List"));

    curveGroupBox = new QGroupBox(tr("Curve List"));
}

void ObjectListsWidget::setupLayout()
{
    torusLayout = new QHBoxLayout;
    pointLayout = new QHBoxLayout;
    curveLayout = new QHBoxLayout;

    torusGroupBox->setLayout(torusLayout);
    pointGroupBox->setLayout(pointLayout);
    curveGroupBox->setLayout(curveLayout);

    torusList = new QListWidget;
    pointList = new QListWidget;
    curveList = new QListWidget;

    torusLayout->addWidget(torusList);
    pointLayout->addWidget(pointList);
    curveLayout->addWidget(curveList);

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
