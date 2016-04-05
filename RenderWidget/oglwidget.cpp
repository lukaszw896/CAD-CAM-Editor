#include "oglwidget.h"
#include <iostream>
#include "uiaccess.h"
#include <QListWidgetItem>
#include "drawable/point.h"
typedef unsigned char BYTE;
OGlWidget::OGlWidget(QWidget *parent): QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    timerId = startTimer(17);

    this->setFocusPolicy(Qt::ClickFocus);

    camera = Camera();

   // Window& w = Window::getInstance();
   // Ui::Window* ui = w.getUi();
    /*drawableObjects.push_back(new Torus(&camera));
    //drawableObjects.push_back(new Torus(&camera));
    drawableObjects.push_back(new Point(&camera));*/
    drawableObjectsData.addTorus(new Torus(&camera));
        //drawableObjects.push_back(new Torus(&camera));
    drawableObjectsData.addPoint(new Point(&camera));
    drawableObjectsData.drawableObjects[1]->xPos = -0.7f;
    drawableObjectsData.drawableObjects[1]->updateTranslationMatX();
    drawableObjectsData.drawableObjects[1]->yPos = -0.7f;
    drawableObjectsData.drawableObjects[1]->updateTranslationMatY();
    drawableObjectsData.drawableObjects[1]->zPos = -13.7f;
    drawableObjectsData.drawableObjects[1]->updateTranslationMatZ();

    UiAccess& uiAccess = UiAccess::getInstance();

    ui = uiAccess.ui;

       QListWidgetItem item = QListWidgetItem();
       item.setText("test");
      // ui->drawableObjectsList->addItem(item);
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

        break;
    case Qt::Key_BracketRight:

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

    glPointSize(-30/camera.zPos - (5.f-camera.rProjection)/5);
    glLineWidth(-15/camera.zPos - (5.f-camera.rProjection)/5);
    //glLineWidth(1);

    for(int i=0; i<drawableObjectsData.drawableObjects.size();i++){
        drawableObjectsData.drawableObjects[i]->draw();
    }


}


