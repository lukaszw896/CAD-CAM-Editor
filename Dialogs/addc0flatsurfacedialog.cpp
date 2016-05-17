#include "addc0flatsurfacedialog.h"

AddC0FlatSurfaceDialog::AddC0FlatSurfaceDialog(QWidget* parent): QDialog(parent)
{
    isAddingFlat = true;
    setupLayout();
}



void AddC0FlatSurfaceDialog::setupLayout()
{
    initGroupBox();

    infoLabel = new QLabel("Size in floats");
    heightLabel = new QLabel("Height");
    widthLabel = new QLabel("Width");
    xLabel = new QLabel("x");
    patchesLabel = new QLabel("patches");

    heightInput = new QLineEdit();
    widthInput = new QLineEdit();
    horPatchesInput = new QLineEdit();
    verPatchesInput = new QLineEdit();

    heightInput->setText("0.5");
    widthInput->setText("0.5");
    verPatchesInput->setText("2");
    horPatchesInput->setText("2");

    cancelButton = new QPushButton("Cancel");
    connect(cancelButton,SIGNAL(clicked(bool)),this,SLOT(cancelButtonClicked()));
    okButton = new QPushButton("OK");
    connect(okButton,SIGNAL(clicked(bool)),this,SLOT(addFlatBezierSurface()));

    mainLayout = new QVBoxLayout();
    heightLayout = new QHBoxLayout();
    widthLayout = new QHBoxLayout();
    patchesLayout = new QHBoxLayout();
    buttonsLayout = new QHBoxLayout();

    heightLayout->addWidget(heightLabel);
    heightLayout->addWidget(heightInput);

    widthLayout->addWidget(widthLabel);
    widthLayout->addWidget(widthInput);

    patchesLayout->addWidget(horPatchesInput);
    patchesLayout->addWidget(xLabel);
    patchesLayout->addWidget(verPatchesInput);
    patchesLayout->addWidget(patchesLabel);

    buttonsLayout->addWidget(cancelButton);
    buttonsLayout->addWidget(okButton);

    mainLayout->addWidget(infoLabel);
    mainLayout->addLayout(heightLayout);
    mainLayout->addLayout(widthLayout);
    mainLayout->addLayout(patchesLayout);
    mainLayout->addWidget(groupBox);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);

}

void AddC0FlatSurfaceDialog::initGroupBox()
{
    checkBoxLayout = new QHBoxLayout;
    c0CheckBox = new QCheckBox(tr("C0"));
    c0CheckBox->setChecked(true);
    c0PrevState = true;
    connect(c0CheckBox,SIGNAL(clicked(bool)),this,SLOT(checkBoxChecked()));
    c2CheckBox = new QCheckBox(tr("C2"));
    connect(c2CheckBox,SIGNAL(clicked(bool)),this,SLOT(checkBoxChecked()));
    checkBoxLayout->addWidget(c0CheckBox);
    checkBoxLayout->addWidget(c2CheckBox);
    groupBox = new QGroupBox(tr("Continuity"));
    groupBox->setAlignment(Qt::AlignLeft);
    groupBox->setLayout(checkBoxLayout);
}

void AddC0FlatSurfaceDialog::cancelButtonClicked()
{
    close();
}

void AddC0FlatSurfaceDialog::addFlatBezierSurface()
{
    float totalWidth = widthInput->text().toFloat();
    float totalHeight = heightInput->text().toFloat();
    int verNumOfPatches = verPatchesInput->text().toInt();
    int horNumOfPatches = horPatchesInput->text().toInt();
    BezierSurface* bezierSurface;
    if(isAddingFlat){
        bezierSurface = new BezierSurface(data.camera,totalWidth,totalHeight,
                                          verNumOfPatches,horNumOfPatches,c0CheckBox->isChecked());
    }
    else{
        bezierSurface = new BezierSurface(data.camera,totalWidth,totalHeight,
                                          verNumOfPatches,horNumOfPatches,true,c0CheckBox->isChecked());
    }
    data.addBezierSurface(bezierSurface);
    emit bezFlatSurfAdded();
    close();
}

void AddC0FlatSurfaceDialog::checkBoxChecked()
{
    if(c0PrevState == c0CheckBox->isChecked())
    {
        c0PrevState = false;
        c0CheckBox->setChecked(false);
    }else
    {
        c0PrevState = true;
        c2CheckBox->setChecked(false);
    }
}

void AddC0FlatSurfaceDialog::show()
{
    if(isAddingFlat) widthLabel->setText("Width");
    else widthLabel->setText("Radius");

    QDialog::show();
}
