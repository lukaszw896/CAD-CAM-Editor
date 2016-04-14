#ifndef NAMECHANGEDIALOG_H
#define NAMECHANGEDIALOG_H
#include <QtGui>
#include <QtCore>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextBlock>
#include <QLineEdit>
#include "drawable/point.h"
#include "Data/drawableobjectsdata.h"

class NameChangeDialog : public QDialog
{
    Q_OBJECT
public:
    NameChangeDialog(QWidget* parent = 0);
    void setDrawable(Drawable*);

private slots:
    void okButtonClicked();
    void cancelButtonClicked();

signals:
    void nameHasBeenChanged();

private:
    DrawableObjectsData& data = DrawableObjectsData::getInstance();
    Drawable* objectChangingName;

    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QLabel *infoLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QLineEdit* lineEdit;

    void setuplayout();
};

#endif // NAMECHANGEDIALOG_H
