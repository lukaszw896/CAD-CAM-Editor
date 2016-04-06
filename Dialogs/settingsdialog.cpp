#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent ) :QDialog(parent)
{
    titleLabel = new QLabel("Stereoscopy settings");
    checkBoxLabel = new QLabel("Turn ON/OFF stereoscopy");
    sliderLabel = new QLabel("Eye distance");

    stereoscopyCheckBox = new QCheckBox();
    eyeDistanceSlider = new QSlider();
    eyeDistanceSlider->setMaximum(100);
    eyeDistanceSlider->setMinimum(1);

    checkBoxLayout = new QVBoxLayout();
    checkBoxLayout->addWidget(checkBoxLabel);
    checkBoxLayout->addWidget(stereoscopyCheckBox);

    sliderLayout = new QVBoxLayout();
    sliderLayout->addWidget(sliderLabel);
    sliderLayout->addWidget(eyeDistanceSlider);

    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(checkBoxLayout);
    mainLayout->addLayout(sliderLayout);

    setLayout(mainLayout);

    connect(stereoscopyCheckBox,SIGNAL(toggled(bool)),this,SLOT(checkBoxChecked(bool)));
    connect(eyeDistanceSlider,SIGNAL(valueChanged(int)),this, SLOT(eyeDistanceSliderValueChanged(int)));

}

void SettingsDialog::checkBoxChecked(bool value)
{
    emit turnOnOffStereoscopy(value);
}

void SettingsDialog::eyeDistanceSliderValueChanged(int value)
{
    emit eyeDistanceValueChanged(value);
}
