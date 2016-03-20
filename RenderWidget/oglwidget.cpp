#include "oglwidget.h"
#include <iostream>
typedef unsigned char BYTE;
OGlWidget::OGlWidget(QWidget *parent): QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    timerId = startTimer(17);

    this->setFocusPolicy(Qt::ClickFocus);

    camera = Camera();

    torus = Torus(&camera);
    torus.initTorus();

    torus2 = Torus(&camera);
    torus2.initTorus();
    torus2.xPos = -0.7f;
    torus2.updateTranslationMatX();
    torus2.yPos = -0.7f;
    torus2.updateTranslationMatY();
    torus2.zPos = -13.7f;
    torus2.updateTranslationMatZ();
}

OGlWidget::~OGlWidget()
{
    killTimer(timerId);
}

QSize OGlWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize OGlWidget::sizeHint() const
{
    return QSize(400, 400);
}


static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void OGlWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != camera.xRot) {
        camera.xRot = angle;
        emit xRotationChanged(angle);
        camera.updateXRotationMat();
    }
}

void OGlWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != camera.yRot) {
        camera.yRot = angle;
        emit yRotationChanged(angle);
        camera.updateYRotationMat();
    }
}

void OGlWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != camera.zRot) {
        camera.zRot = angle;
        emit zRotationChanged(angle);
        camera.updateZRotationMat();
    }
}

void OGlWidget::checkBoxStateChanged(bool state){
    if(state == true){
        camera.isStereoscopic = true;
    }
    else
    {
        camera.isStereoscopic = false;
    }
}

void OGlWidget::changeEyeDistance(int distance){
    camera.eyeDist = (float)distance/100;
    camera.initProjectionMatLeftEye(camera.rProjection,camera.eyeDist);
    camera.initProjectionMatRightEye(camera.rProjection,camera.eyeDist);
}

void OGlWidget::changeScale(int scale){
    camera.scale = (float)scale/25;
    camera.updateScaleMatrix(camera.scale);
}

void OGlWidget::initializeGL()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    glEnable ( GL_COLOR_MATERIAL );
}

void OGlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
}

void OGlWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    if(width>height){
        camera.xRatio = (float)width/(float)height;
        camera.yRatio = 1.0f;
    }
    else if(height>width){
        camera.xRatio = 1.0f;
        camera.yRatio = (float)height/(float)width;
    }
    else{camera.xRatio = 1.0f;camera.yRatio=1.0f;}
}

void OGlWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void OGlWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(camera.xRot + 1 * dy);
        setYRotation(camera.yRot + 1 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(camera.xRot + 1 * dy);
        setZRotation(camera.zRot + 1 * dx);
    }

    lastPos = event->pos();
}

void OGlWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
        case Qt::Key_Up:
            camera.yPos -= 0.05f;
            camera.updateTranslationMatY();
            break;
        case Qt::Key_Down:
            camera.yPos += 0.05f;
             camera.updateTranslationMatY();
            break;
    case Qt::Key_Left:
        camera.xPos+=0.05f;
        camera.updateTranslationMatX();
        break;
    case Qt::Key_Right:
        camera.xPos-=0.05f;
        camera.updateTranslationMatX();
        break;
    case Qt::Key_Plus:
        camera.zPos+=0.2f;
        camera.updateTranslationMatZ();
        break;
    case Qt::Key_Minus:
        camera.zPos-=0.2f;
        camera.updateTranslationMatZ();
        break;
    case Qt::Key_BracketLeft:
    if(torus.ringsCount>10){
            torus.ringsCount -=10;
            torus.sectionsCount -=10;
            torus.initTorus();
        }
        break;
    case Qt::Key_BracketRight:
        if(torus.ringsCount<200){
                torus.ringsCount +=10;
                torus.sectionsCount +=10;
                torus.initTorus();
            }
            break;
    }
}

void OGlWidget::timerEvent(QTimerEvent *event)
{
   updateGL();
}


void OGlWidget::draw()
{
    camera.computeTransformationMatrix();
   // computeTransformedPoints();

    glEnable(GL_BLEND);
   // glBlendFunc(GL_SRC_COLOR, GL_ONE);
    glBlendEquation(GL_MAX);


    //glLineWidth(-15/camera.zPos - (5.f-camera.rProjection)/5);
    glLineWidth(1);
    torus.draw();
    torus2.draw();

}


