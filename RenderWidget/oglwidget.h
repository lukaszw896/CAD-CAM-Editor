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

using namespace glm;

class OGlWidget : public QGLWidget, public Drawable
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
    void initProjectionMatLeftEye(float r, float e);
    void initProjectionMatRightEye(float r, float e);

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

    float xRatio;
    float yRatio;

    int xRot;
    int yRot;
    int zRot;

    float xPos;
    float yPos;
    float zPos;

    float scale;

    glm::mat4 identityMat;

    glm::mat4 xRotationMatrix;
    glm::mat4 yRotationMatrix;
    glm::mat4 zRotationMatrix;

    glm::mat4 translationMatrix;
    glm::mat4 scaleMatrix;
    glm::mat4 projectionMatrix;

    mat4 projectionMatrixLeftEye;
    mat4 projectionMatrixRightEye;

    glm::mat4 vecTransformMat;

    mat4 transformationMatrixLeftEye;
    mat4 transformationMatrixRightEye;

    //last mouse position
    QPoint lastPos;

    float rProjection;
    float eyeDist;

    bool isStereoscopic;

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
    void checkBoxStateChanged(bool);
    void changeEyeDistance(int);
    void changeScale(int);
};

#endif // OGLWIDGET_H
