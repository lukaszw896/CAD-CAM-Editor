#include "oglwidget.h"
#include <iostream>
typedef unsigned char BYTE;
OGlWidget::OGlWidget(QWidget *parent): QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    timerId = startTimer(17);

    this->setFocusPolicy(Qt::ClickFocus);
    xRatio = 1.f;
    yRatio = 1.f;

    xRot = 0;
    yRot = 0;
    zRot = 0;

    xPos = 0;
    yPos = 0;
    zPos = -10.f;

    rProjection = 4.0f;

    torus = Torus();
    torus.initTorus();
    initIdentityMat();
    initTranslationMat(xPos,yPos,zPos);
    initProjectionMat(rProjection);
    initXRotationMat(xRot);
    initYRotationMat(yRot);
    initZRotationMat(zRot);
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
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        initXRotationMat(xRot);
    }
}

void OGlWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        initYRotationMat(yRot);
    }
}

void OGlWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        initZRotationMat(zRot);
    }
}

void OGlWidget::initializeGL()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
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
        xRatio = (float)width/(float)height;
        yRatio = 1.0f;
    }
    else if(height>width){
        xRatio = 1.0f;
        yRatio = (float)height/(float)width;
    }
    else{xRatio = 1.0f;yRatio=1.0f;}
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
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }

    lastPos = event->pos();
}

void OGlWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
        case Qt::Key_Up:
            yPos -= 0.05f;
            break;
        case Qt::Key_Down:
            yPos += 0.05f;
            break;
    case Qt::Key_Left:
        xPos+=0.05f;
        break;
    case Qt::Key_Right:
        xPos-=0.05f;
        break;
    case Qt::Key_Plus:
        zPos+=0.1f;
        break;
    case Qt::Key_Minus:
        zPos-=0.1f;
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


    initTranslationMat(xPos,yPos,zPos);
}

void OGlWidget::timerEvent(QTimerEvent *event)
{
   updateGL();
}



void OGlWidget::computeTransformedPoints()
{
    //TODO resize
    for(int i=0;i<torus.torusPoints.size();i++){
        torus.trousTransPoints[i] = vecTransformMat*torus.torusPoints[i];
        //torus.trousTransPoints[i] = torus.trousTransPoints[i]/torus.trousTransPoints[i][3];
        torus.trousTransPoints[i].x = torus.trousTransPoints[i].x / torus.trousTransPoints[i].w;
        torus.trousTransPoints[i].y = torus.trousTransPoints[i].y / torus.trousTransPoints[i].w;
        torus.trousTransPoints[i].x /= xRatio;
        torus.trousTransPoints[i].y /= yRatio;
    }
}

void OGlWidget::computeTransformationMatrix()
{
    //*identityMat
    vecTransformMat = projectionMatrix*translationMatrix*zRotationMatrix* yRotationMatrix* xRotationMatrix;
}

void OGlWidget::draw()
{
    computeTransformationMatrix();
    computeTransformedPoints();

    qglColor(Qt::red);


    glLineWidth(-15/zPos - (5.f-rProjection)/5);
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_LINES);

    for(int i=0;i<torus.edges.size();i++){

        if(!(torus.edges[i].vertice1->w >=-0.06|| torus.edges[i].vertice2->w >=-0.06)){
            glVertex2f(torus.edges[i].vertice1->x,torus.edges[i].vertice1->y);
            glVertex2f(torus.edges[i].vertice2->x,torus.edges[i].vertice2->y);
        }


    }
     glEnd();
}


