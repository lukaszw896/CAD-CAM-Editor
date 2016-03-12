#include "oglwidget.h"
#include <iostream>
typedef unsigned char BYTE;
OGlWidget::OGlWidget(QWidget *parent): QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    timerId = startTimer(16);

    this->setFocusPolicy(Qt::ClickFocus);
    xRatio = 1.f;
    yRatio = 1.f;

    xRot = 0;
    yRot = 0;
    zRot = 0;

    xPos = 0;
    yPos = 0;
    zPos = -10.f;
    camera = vec3(0,0,0);
    scale = 1.0;

    rProjection = 4.0f;

    torus = Torus();
    torus.initTorus();

    initIdentityMat();
    initTranslationMat(xPos,yPos,zPos);
    initProjectionMat(rProjection);
    initScaleMat(scale);
    initXRotationMat(xRot);
    initYRotationMat(yRot);
    initZRotationMat(zRot);

    elipsoid = Elipsoid(0.6,0.65,0.6);

    drawAdaptive = true;
    adaptiveLastLoop = false;
    numOfTiles = 4;
   // elipsoid.m
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

void OGlWidget::setRadiusA(int aRad){
    elipsoid.updateRadius((100-aRad)/100,elipsoid.b,elipsoid.c);
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
    windowHeight = height;
    windowWidth = width;

    if(width>height){
        xRatio = (float)width/(float)height;
        yRatio = 1.0f;
    }
    else if(height>width){
        xRatio = 1.0f;
        yRatio = (float)height/(float)width;
    }
    else{xRatio = 1.0f;yRatio=1.0f;}

    drawAdaptive = true;
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
        scale+=0.05f;
        initScaleMat(scale);
       // zPos-=0.05f;
        break;
    case Qt::Key_Minus:
        scale-=0.05f;
        initScaleMat(scale);
      //   -zPos+=0.05f;
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
    if(drawAdaptive){

   updateGL();
    }
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
    vecTransformMat = projectionMatrix*translationMatrix*scaleMatrix* zRotationMatrix* yRotationMatrix* xRotationMatrix;
}

float OGlWidget::computePixFloatX(int xCord){
    float ret = (float)xCord/(float)windowWidth*2 - 1.0;
    return ret;
}

float OGlWidget::computePixFloatY(int yCord){
    float ret = (float)yCord/(float)windowHeight*2 - 1.0;
    return ret;

}

void OGlWidget::drawTile(int startX, int startY, int endX, int endY, vec4* color){
    float tmpX;
    float tmpY;
    tmpX = computePixFloatX(startX);
    tmpY = computePixFloatY(startY);
    float isColored = elipsoid.intersectCalc(tmpX,tmpY,&camera,color);
    glColor3f(color->x, color->y, color->z);
    if(isColored != NO_SOLUTION){
        for(int w=startX;w<endX;w++){
            for(int h=startY;h<endY;h++){
                tmpX = computePixFloatX(w);
                tmpY = computePixFloatY(h);
                 glVertex2f(tmpX,tmpY);
            }
        }
    }
}

void OGlWidget::draw()
{
    computeTransformationMatrix();
    elipsoid.calcDPMMat(vecTransformMat);

    glDisable(GL_LIGHTING);
    glBegin(GL_POINTS);
    vec4* color;

        int tileWidth = windowWidth/numOfTiles;
        int tileHeight = windowHeight/numOfTiles;
        for(int i=0;i<numOfTiles;i++){
            for(int j=0;j<numOfTiles;j++){
                drawTile(tileWidth*i,tileHeight*j,tileWidth*(i+1),tileWidth*(j+1),color);
            }
        }
        numOfTiles*=4;
        float tmpWidth = (float)windowWidth/(float)numOfTiles;
        float tmpHeight = (float)windowHeight/(float)numOfTiles;
        if(tmpHeight<1.0 || tmpWidth <1.0){
            numOfTiles=4;
            //drawAdaptive=false;


        }
       /* else if(tmpHeight==1.0 || tmpWidth ==1.0)
        {
            numOfTiles=4;
            drawAdaptive=false;
        }*/

   /* float tmpX;
    float tmpY;
    for(int w=0;w<windowWidth;w++){
        for(int h=0;h<windowHeight;h++){
            tmpX = computePixFloatX(w);
            tmpY = computePixFloatY(h);
            if(elipsoid.intersectCalc(tmpX,tmpY,&camera,color) != NO_SOLUTION)
            {
                 glColor3f(color->x, color->y, color->z);
                 glVertex2f(tmpX,tmpY);
            }
        }
    }*/
    glEnd();

  /*  computeTransformedPoints();

    qglColor(Qt::red);


    glLineWidth(-15/zPos - (5.f-rProjection)/5);
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_LINES);

    for(int i=0;i<torus.edges.size();i++){

      //  if(!(torus.edges[i].vertice1->w >=-0.06|| torus.edges[i].vertice2->w >=-0.06)){
            glVertex2f(torus.edges[i].vertice1->x,torus.edges[i].vertice1->y);
            glVertex2f(torus.edges[i].vertice2->x,torus.edges[i].vertice2->y);
       // }


    }
     glEnd();*/
}


