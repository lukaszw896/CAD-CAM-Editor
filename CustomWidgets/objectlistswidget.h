#ifndef OBJECTLISTSWIDGET_H
#define OBJECTLISTSWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>

class ObjectListsWidget : public QWidget
{
    Q_OBJECT
public:
    ObjectListsWidget();

private:

    QVBoxLayout* mainLayout;

    QGroupBox* torusGroupBox;
    QGroupBox* pointGroupBox;

    void setupLists();
    void setupGroupBoxes();
    void setupLayout();
};

#endif // OBJECTLISTSWIDGET_H
