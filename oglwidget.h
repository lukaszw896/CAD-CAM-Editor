#ifndef OGLWIDGET_H
#define OGLWIDGET_H

typedef unsigned char BYTE;

#include <QMouseEvent>
#include <QGLWidget>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include "cmath"
#include "torus.h"

class OGlWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit OGlWidget(QWidget *parent = 0);
    ~OGlWidget();

protected:

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void initIdentityMat();
    void initTranslationMat(float x, float y, float z);
    void initProjectionMat(float r);
    void initXRotationMat(int angle);
    void initYRotationMat(int angle);
    void initZRotationMat(int angle);
    void initScaleMat(float s);


    void computeTransformationMatrix();

    void computeTransformedPoints();

    void timerEvent(QTimerEvent *event);



private:
    int timerId;

    void draw();
    BYTE ComputeOutcode(float x,float y);

    void CohenSutherland(float x1,float y1, float x2, float y2);

    float xRatio;
    float yRatio;

    int xRot;
    int yRot;
    int zRot;

    float xPos;
    float yPos;
    float zPos;

    glm::mat4 identityMat;

    glm::mat4 xRotationMatrix;
    glm::mat4 yRotationMatrix;
    glm::mat4 zRotationMatrix;

    glm::mat4 translationMatrix;
    glm::mat4 scaleMatrix;
    glm::mat4 projectionMatrix;

    glm::mat4 vecTransformMat;

    //last mouse position
    QPoint lastPos;

    float rProjection;

    Torus torus;

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
};

#endif // OGLWIDGET_H