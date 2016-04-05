#include "objectlistswidget.h"

ObjectListsWidget::ObjectListsWidget()
{
    setupLists();
    setupGroupBoxes();
    setupLayout();
}

void ObjectListsWidget::setupLists()
{

}

void ObjectListsWidget::setupGroupBoxes()
{
    torusGroupBox = new QGroupBox(tr("Tours List"));

    pointGroupBox = new QGroupBox(tr("Point List"));
}

void ObjectListsWidget::setupLayout()
{
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(torusGroupBox);
    mainLayout->addWidget(pointGroupBox);
    setLayout(mainLayout);
}
