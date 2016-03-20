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

    scale = 1.0f;

    rProjection = 4.f;
    eyeDist = 0.10f;
    isStereoscopic = false;


    torus = Torus();
    torus.initTorus();
    initIdentityMat();
    initTranslationMat();
    updateTranslationMatZ(zPos);
    initScaleMat(scale);
    initProjectionMat(rProjection);
    initProjectionMatLeftEye(rProjection,eyeDist);
    initProjectionMatRightEye(rProjection,eyeDist);
    initXRotationMat();
    initYRotationMat();
    initZRotationMat();
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
        updateXRotationMat(xRot);
    }
}

void OGlWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateYRotationMat(yRot);
    }
}

void OGlWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateZRotationMat(zRot);
    }
}

void OGlWidget::checkBoxStateChanged(bool state){
    if(state == true){
        isStereoscopic = true;
    }
    else
    {
        isStereoscopic = false;
    }
}

void OGlWidget::changeEyeDistance(int distance){
    eyeDist = (float)distance/100;
    initProjectionMatLeftEye(rProjection,eyeDist);
    initProjectionMatRightEye(rProjection,eyeDist);
}

void OGlWidget::changeScale(int scale){
    this->scale = (float)scale/25;
    initScaleMat(this->scale);
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
            updateTranslationMatY(yPos);
            break;
        case Qt::Key_Down:
            yPos += 0.05f;
             updateTranslationMatY(yPos);
            break;
    case Qt::Key_Left:
        xPos+=0.05f;
        updateTranslationMatX(xPos);
        break;
    case Qt::Key_Right:
        xPos-=0.05f;
        updateTranslationMatX(xPos);
        break;
    case Qt::Key_Plus:
        zPos+=0.1f;
        updateTranslationMatZ(zPos);
        break;
    case Qt::Key_Minus:
        zPos-=0.1f;
        updateTranslationMatZ(zPos);
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



void OGlWidget::computeTransformedPoints()
{
    //TODO resize
    for(int i=0;i<torus.torusPoints.size();i++){
        if(!isStereoscopic){
            torus.trousTransPoints[i] = vecTransformMat*torus.torusPoints[i];
        //torus.trousTransPoints[i] = torus.trousTransPoints[i]/torus.trousTransPoints[i][3];
            torus.trousTransPoints[i].x = torus.trousTransPoints[i].x / torus.trousTransPoints[i].w;
            torus.trousTransPoints[i].y = torus.trousTransPoints[i].y / torus.trousTransPoints[i].w;
            torus.trousTransPoints[i].x /= xRatio;
            torus.trousTransPoints[i].y /= yRatio;
        }
        else
        {

                torus.toursPointsLeftEye[i] = transformationMatrixLeftEye*torus.torusPoints[i];
                torus.toursPointsLeftEye[i].x = torus.toursPointsLeftEye[i].x / torus.toursPointsLeftEye[i].w;
                torus.toursPointsLeftEye[i].y = torus.toursPointsLeftEye[i].y / torus.toursPointsLeftEye[i].w;
                torus.toursPointsLeftEye[i].x /= xRatio;
                torus.toursPointsLeftEye[i].y /= yRatio;


                torus.torusPointsRightEye[i] = transformationMatrixRightEye*torus.torusPoints[i];
                torus.torusPointsRightEye[i].x = torus.torusPointsRightEye[i].x / torus.torusPointsRightEye[i].w;
                torus.torusPointsRightEye[i].y = torus.torusPointsRightEye[i].y / torus.torusPointsRightEye[i].w;
                torus.torusPointsRightEye[i].x /= xRatio;
                torus.torusPointsRightEye[i].y /= yRatio;
        }

    }
}

void OGlWidget::computeTransformationMatrix()
{
    //*identityMat
    if(!isStereoscopic){
         vecTransformMat = projectionMatrix*translationMatrix*scaleMatrix * zRotationMatrix* yRotationMatrix* xRotationMatrix;
    }
    else
    {
        transformationMatrixLeftEye = projectionMatrixLeftEye*translationMatrix*scaleMatrix *zRotationMatrix* yRotationMatrix* xRotationMatrix;
        transformationMatrixRightEye = projectionMatrixRightEye*translationMatrix*scaleMatrix *zRotationMatrix* yRotationMatrix* xRotationMatrix;
    }
}

void OGlWidget::draw()
{
    computeTransformationMatrix();
    computeTransformedPoints();

    glEnable(GL_BLEND);
   // glBlendFunc(GL_SRC_COLOR, GL_ONE);
    glBlendEquation(GL_MAX);


    glLineWidth(-15/zPos - (5.f-rProjection)/5);
    //glLineWidth(1);

   // glColor3f(1.0,0, 0.0);

    glBegin(GL_LINES);

    if(!isStereoscopic){
        glColor4f(1,1.0, 1.0,1.0);
        for(int i=0;i<torus.edges.size();i++){

            if(!(torus.edges[i].vertice1->w >=-0.06|| torus.edges[i].vertice2->w >=-0.06)){
                glVertex2f(torus.edges[i].vertice1->x,torus.edges[i].vertice1->y);
                glVertex2f(torus.edges[i].vertice2->x,torus.edges[i].vertice2->y);
            }
        }

    }else
    {
        glColor3f(0.4,0.0, 0.0);
        for(int i=0;i<torus.edgesLeftEye.size();i++){

            if(!(torus.edgesLeftEye[i].vertice1->w >=-0.06|| torus.edgesLeftEye[i].vertice2->w >=-0.06)){
                glVertex2f(torus.edgesLeftEye[i].vertice1->x,torus.edgesLeftEye[i].vertice1->y);
                glVertex2f(torus.edgesLeftEye[i].vertice2->x,torus.edgesLeftEye[i].vertice2->y);
            }
        }

    //glColor3f(0, 0, 1);
     glColor3f(0, 0.5, 0.5);
        for(int i=0;i<torus.edgesRightEye.size();i++){

            if(!(torus.edgesRightEye[i].vertice1->w >=-0.06|| torus.edgesRightEye[i].vertice2->w >=-0.06)){
             glVertex2f(torus.edgesRightEye[i].vertice1->x,torus.edgesRightEye[i].vertice1->y);
             glVertex2f(torus.edgesRightEye[i].vertice2->x,torus.edgesRightEye[i].vertice2->y);
             }
        }
    }
     glEnd();
}


