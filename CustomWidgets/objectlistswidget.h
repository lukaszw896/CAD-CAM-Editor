#ifndef OBJECTLISTSWIDGET_H
#define OBJECTLISTSWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QAbstractAnimation>
#include <QPushButton>
#include "drawable/point.h"
#include "drawable/torus.h"
#include "Data/drawableobjectsdata.h"

class ObjectListsWidget : public QWidget
{
    Q_OBJECT
public:
    ObjectListsWidget();

public slots:
    void updateListsContent();
    void torusHasBeenSelected();
    void torusHasBeenDoubleClicked();
    void pointHasBeenSelected();
    void pointHasBeenDoubleClicked();

    void deleteTorusButtonClicked();
    void deletePointButtonClicked();
    void deleteCurveButtonClicked();

    void pointOnSceneSelection(Point*);
    void pointOnSceneDoubleClick(Point*);

signals:



private:

    DrawableObjectsData& drawableObjectsData = DrawableObjectsData::getInstance();

    QVBoxLayout* mainLayout;
    QVBoxLayout* torusLayout;
    QVBoxLayout* pointLayout;
    QVBoxLayout* curveLayout;


    QGroupBox* torusGroupBox;
    QGroupBox* pointGroupBox;
    QGroupBox* curveGroupBox;

    QListWidget* torusList;
    QListWidget* pointList;
    QListWidget* curveList;

    QPushButton* deleteTorusButton;
    QPushButton* deletePointButton;
    QPushButton* deleteCurveButton;

    void setupGroupBoxes();
    void setupLayout();
    void setupButtons();
};

#endif // OBJECTLISTSWIDGET_H
