#ifndef OBJECTLISTSWIDGET_H
#define OBJECTLISTSWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include "Data/drawableobjectsdata.h"

class ObjectListsWidget : public QWidget
{
    Q_OBJECT
public:
    ObjectListsWidget();

public slots:
    void updateListsContent();

private:

    DrawableObjectsData& drawableObjectsData = DrawableObjectsData::getInstance();

    QVBoxLayout* mainLayout;
    QHBoxLayout* torusLayout;
    QHBoxLayout* pointLayout;
    QHBoxLayout* curveLayout;


    QGroupBox* torusGroupBox;
    QGroupBox* pointGroupBox;
    QGroupBox* curveGroupBox;

    QListWidget* torusList;
    QListWidget* pointList;
    QListWidget* curveList;

    void setupLists();
    void setupGroupBoxes();
    void setupLayout();
};

#endif // OBJECTLISTSWIDGET_H
