#ifndef ADDC0FLATSURFACEDIALOG_H
#define ADDC0FLATSURFACEDIALOG_H
#include <QtGui>
#include <QtCore>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextBlock>
#include <QLineEdit>
#include "Data/drawableobjectsdata.h"

class AddC0FlatSurfaceDialog : public QDialog
{
    Q_OBJECT
public:
    AddC0FlatSurfaceDialog(QWidget* parent = 0);

signals:
    void bezFlatSurfAdded();

private:
    DrawableObjectsData& data = DrawableObjectsData::getInstance();
    QVBoxLayout *mainLayout;
    QHBoxLayout *heightLayout;
    QHBoxLayout *widthLayout;
    QHBoxLayout *patchesLayout;
    QHBoxLayout *buttonsLayout;

    QLabel *infoLabel;
    QLabel *heightLabel;
    QLabel *widthLabel;
    QLabel *xLabel;
    QLabel *patchesLabel;

    QLineEdit *heightInput;
    QLineEdit *widthInput;
    QLineEdit *horPatchesInput;
    QLineEdit *verPatchesInput;

    QPushButton *cancelButton;
    QPushButton *okButton;

    void setupLayout();


private slots:
    void cancelButtonClicked();
    void addFlatBezierSurface();
};

#endif // ADDC0FLATSURFACEDIALOG_H
