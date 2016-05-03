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
#include "Data/drawableobjectsdata.h"
#include "drawable/Surfaces/bezierpatch.h"
#include "drawable/Surfaces/beziersurface.h"

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
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void timerEvent(QTimerEvent *event);



private:
    QSet<int> keysPressed;
    bool isSpacePressed;
    Drawable* objectToMove;

    int timerId;

    void draw();

    //last mouse position
    QPoint lastPos;
    QPoint firstPos;

    int screenWidth;
    int screenHeight;
    QPoint screenSize;

    Camera camera;
    DrawableObjectsData& drawableObjectsData = DrawableObjectsData::getInstance();
    BezierPatch* bezierPatch;
    BezierSurface* bezierSurface;

    Ui::Window* ui;

signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void pointOnScreenClick(Point*);
    void pointOnScreenDoubleClick(Point*);
    void cursorPositionChanged();

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
