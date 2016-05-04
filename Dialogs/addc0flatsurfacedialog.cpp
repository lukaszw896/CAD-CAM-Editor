#include "addc0flatsurfacedialog.h"

AddC0FlatSurfaceDialog::AddC0FlatSurfaceDialog(QWidget* parent): QDialog(parent)
{
    setupLayout();
}

void AddC0FlatSurfaceDialog::setupLayout()
{
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
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);

}

void AddC0FlatSurfaceDialog::addFlatBezierSurface()
{
    float totalWidth = widthInput->text().toFloat();
    float totalHeight = heightInput->text().toFloat();
    int verNumOfPatches = verPatchesInput->text().toInt();
    int horNumOfPatches = horPatchesInput->text().toInt();

    BezierSurface* bezierSurface = new BezierSurface(data.camera,totalWidth,totalHeight,
                                                     verNumOfPatches,horNumOfPatches);
    data.addBezierSurface(bezierSurface);
    emit bezFlatSurfAdded();
    close();
}

void AddC0FlatSurfaceDialog::cancelButtonClicked()
{
    close();
}
