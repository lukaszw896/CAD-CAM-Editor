#ifndef OGLWIDGET_H
#define OGLWIDGET_H

typedef unsigned char BYTE;

#include <QMouseEvent>
#include <QGLWidget>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include "cmath"
#include "drawable/torus.h"
#include "drawable/drawable.h"
#include "Camera/camera.h"
#include "window.h"

using namespace glm;

class OGlWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit OGlWidget(QWidget *parent = 0);
    ~OGlWidget();

   //

protected:

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void timerEvent(QTimerEvent *event);



private:
    int timerId;

    void draw();

    //last mouse position
    QPoint lastPos;

    std::vector<Drawable*> drawableObjects;

    Camera camera;

    Ui::Window* ui;

signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void checkBoxStateChanged(bool);
    void changeEyeDistance(int);
    void changeScale(int);
};

#endif // OGLWIDGET_H
