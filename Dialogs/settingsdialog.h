#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H
#include <QDialog>
#include <QLabel>
#include <QSlider>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    SettingsDialog(QWidget *parent =0 );

signals:
    void turnOnOffStereoscopy(bool);
    void eyeDistanceValueChanged(int);

private slots:
    void checkBoxChecked(bool);
    void eyeDistanceSliderValueChanged(int);

private:

    QHBoxLayout *checkBoxLayout;
    QHBoxLayout *sliderLayout;
    QVBoxLayout *mainLayout;

    QLabel *titleLabel;
    QLabel *checkBoxLabel;
    QLabel *sliderLabel;
    QSlider *eyeDistanceSlider;
    QCheckBox *stereoscopyCheckBox;
};

#endif // SETTINGSDIALOG_H
