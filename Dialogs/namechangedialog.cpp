#include "namechangedialog.h"

NameChangeDialog::NameChangeDialog(QWidget *parent): QDialog(parent)
{
    setuplayout();

    connect(okButton,SIGNAL(clicked(bool)),this,SLOT(okButtonClicked()));
    connect(cancelButton,SIGNAL(clicked(bool)),this,SLOT(cancelButtonClicked()));
}

void NameChangeDialog::setDrawable(Drawable * drawable)
{
    objectChangingName = drawable;
    lineEdit->setText(QString::fromStdString(objectChangingName->name));
}

void NameChangeDialog::okButtonClicked()
{
    std::string newName = lineEdit->text().toStdString();

    bool changeName = true;
    if(newName == "")
    {
        changeName = false;
    }
    else
    {
        for(int i=2;i<data.allDrawableObjects.size();i++)
        {
            if(data.allDrawableObjects[i]->name == newName)
            {
                changeName = false;
            }
        }
    }
    if(changeName)
    {
        objectChangingName->name = newName;
        emit nameHasBeenChanged();
    }
    close();
}

void NameChangeDialog::cancelButtonClicked()
{
    close();
}

void NameChangeDialog::setuplayout()
{
    infoLabel = new QLabel("Enter new name");
    lineEdit = new QLineEdit();
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(infoLabel);
    mainLayout->addWidget(lineEdit);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}
