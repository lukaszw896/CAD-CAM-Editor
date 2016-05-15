#include "bsplinesurface.h"

BSplineSurface::BSplineSurface()
{

}

int BSplineSurface::id = 0;

BSplineSurface::BSplineSurface(Camera* camera)
{

    this->camera = camera;
    isFlatSurface = false;
    verNumOfPatches = 3;
    horNumOfPatches = 3;
    totalWidth = 1.0f;
    totalHeight = 1.0f;

    if(isFlatSurface)horNumOfConPoints = horNumOfPatches*3+1;
    else horNumOfConPoints = horNumOfPatches*3;
    verNumOfConPoints = verNumOfPatches*3+1;

    controlPoints.resize(verNumOfConPoints*horNumOfConPoints);

    initControlPoints();
}

BSplineSurface::BSplineSurface(Camera *camera, float totalWidth, float totalHeight, int verNumOfPatches, int horNumOfPatches)
{
    id++;
    name = "BSplineFlatSurface_";
    name += std::to_string(id);
    drawBSplineNet = false;

    this->camera = camera;
    isFlatSurface = true;
    this->verNumOfPatches = verNumOfPatches;
    this->horNumOfPatches = horNumOfPatches;
    this->totalWidth = totalWidth;
    this->totalHeight = totalHeight;

    horNumOfConPoints = horNumOfPatches*3+1;
    verNumOfConPoints = verNumOfPatches*3+1;

    controlPoints.resize(verNumOfConPoints*horNumOfConPoints);

    initControlPoints();
}

BSplineSurface::BSplineSurface(Camera *camera, float radius, float totalHeight, int verNumOfPatches, int horNumOfPatches,bool tmp)
{
    id++;
    name = "BezierCylinderSurface_";
    name += std::to_string(id);
    drawBSplineNet = false;

    this->camera = camera;
    isFlatSurface = false;
    this->verNumOfPatches = verNumOfPatches;
    this->horNumOfPatches = horNumOfPatches;
    this->totalWidth = 1.0f;
    this->totalHeight = totalHeight;
    this->radius = radius;

    horNumOfConPoints = horNumOfPatches*3;
    verNumOfConPoints = verNumOfPatches*3+1;

    controlPoints.resize(verNumOfConPoints*horNumOfConPoints);

    initControlPoints();
}

void BSplineSurface::initControlPoints()
{
    //flat surface

    float widthDT = totalWidth / (horNumOfConPoints-1);
    float heightDT = totalHeight / (verNumOfConPoints-1);
    int m=0,n=0;
    if(isFlatSurface){
    for(float i = -(totalWidth/(float)2);i< totalWidth/(float)2+widthDT/2;i+=widthDT,m++)
    {
        n=0;
        for(float j = -(totalHeight/(float)2);j< totalHeight/(float)2+heightDT/2;j+=heightDT,n++)
        {
            controlPoints[n*horNumOfConPoints + m] = new Point(camera);
            controlPoints[n*horNumOfConPoints + m]->xPos = i;
            controlPoints[n*horNumOfConPoints + m]->updateTranslationMatX();
            controlPoints[n*horNumOfConPoints + m]->yPos = j;
            controlPoints[n*horNumOfConPoints + m]->updateTranslationMatY();
           // printf("Control point init pos : %d , x: %lf, y: %lf \n",m*verNumOfConPoints + n,i,j);
        }
    }
    }else{
    //// x=r\cos(t), \ \  y=r\sin(t)
    float t = 0;
    for(float i = 0;i< totalWidth+widthDT/2;i+=widthDT,m++)
    {
        n=0;
        for(float j = 0;j< totalHeight+heightDT/2;j+=heightDT,n++)
        {
            t= i/totalWidth;
            controlPoints[n*horNumOfConPoints + m] = new Point(camera);
            controlPoints[n*horNumOfConPoints + m]->xPos = radius*cos(6.28*t);
            controlPoints[n*horNumOfConPoints + m]->updateTranslationMatX();
            controlPoints[n*horNumOfConPoints + m]->yPos = -totalHeight/4 + j/2;
            controlPoints[n*horNumOfConPoints + m]->updateTranslationMatY();
            controlPoints[n*horNumOfConPoints + m]->zPos = radius*sin(6.28*t);
            controlPoints[n*horNumOfConPoints + m]->updateTranslationMatZ();
           // printf("Control point init pos : %d , x: %lf, y: %lf \n",m*verNumOfConPoints + n,i,j);
            printf("%lf \n",t);
        }
    }
    }
    //// x=r\cos(t), \ \  y=r\sin(t)
    /// cylinder
}

void BSplineSurface::draw()
{
    for(int i=0;i<horNumOfConPoints;i++){
        for(int j=0;j<verNumOfConPoints;j++)
        {
            controlPoints[j*horNumOfConPoints + i]->draw();
        }
    }
    if(drawBSplineNet)
    {


        if(!camera->isStereoscopic){
            for(int i=0;i<horNumOfConPoints;i++){
                for(int j=0;j<verNumOfConPoints;j++)
                {
                    controlPoints[j*horNumOfConPoints + i]->draw();
                }
            }
            glBegin(GL_LINES);
            glColor3f(0.5,1,1);
            for(int i=0;i<horNumOfConPoints-1;i++){
                for(int j=0;j<verNumOfConPoints-1;j++)
                {
                    glVertex2f(controlPoints[j*horNumOfConPoints + i]->transPointCoordinates.x,
                            controlPoints[j*horNumOfConPoints + i]->transPointCoordinates.y);
                    glVertex2f(controlPoints[j*horNumOfConPoints + i +1]->transPointCoordinates.x,
                            controlPoints[j*horNumOfConPoints + i +1]->transPointCoordinates.y);

                    glVertex2f(controlPoints[j*horNumOfConPoints + i]->transPointCoordinates.x,
                            controlPoints[j*horNumOfConPoints + i]->transPointCoordinates.y);
                    glVertex2f(controlPoints[(j+1)*horNumOfConPoints + i]->transPointCoordinates.x,
                            controlPoints[(j+1)*horNumOfConPoints + i]->transPointCoordinates.y);
                }
            }
            for(int i=0;i<horNumOfConPoints-1;i++){
                {
                    glVertex2f(controlPoints[(verNumOfConPoints-1)*horNumOfConPoints + i]->transPointCoordinates.x,
                            controlPoints[(verNumOfConPoints-1)*horNumOfConPoints + i]->transPointCoordinates.y);
                    glVertex2f(controlPoints[(verNumOfConPoints-1)*horNumOfConPoints + i +1]->transPointCoordinates.x,
                            controlPoints[(verNumOfConPoints-1)*horNumOfConPoints + i +1]->transPointCoordinates.y);
                }
            }
            for(int j=0;j<verNumOfConPoints-1;j++)
            {
                glVertex2f(controlPoints[j*horNumOfConPoints + horNumOfConPoints-1]->transPointCoordinates.x,
                        controlPoints[j*horNumOfConPoints + horNumOfConPoints-1]->transPointCoordinates.y);
                glVertex2f(controlPoints[(j+1)*horNumOfConPoints + horNumOfConPoints-1]->transPointCoordinates.x,
                        controlPoints[(j+1)*horNumOfConPoints + horNumOfConPoints-1]->transPointCoordinates.y);
            }
        }
        else{
            for(int i=0;i<horNumOfConPoints-1;i++){
                for(int j=0;j<verNumOfConPoints-1;j++)
                {
                    glColor3f(0.4,0.0, 0.0);
                    glVertex2f(controlPoints[j*horNumOfConPoints + i]->leftEyeTransPointCoordinate.x,
                            controlPoints[j*horNumOfConPoints + i]->leftEyeTransPointCoordinate.y);
                    glVertex2f(controlPoints[j*horNumOfConPoints + i +1]->leftEyeTransPointCoordinate.x,
                            controlPoints[j*horNumOfConPoints + i +1]->leftEyeTransPointCoordinate.y);

                    glVertex2f(controlPoints[j*horNumOfConPoints + i]->leftEyeTransPointCoordinate.x,
                            controlPoints[j*horNumOfConPoints + i]->leftEyeTransPointCoordinate.y);
                    glVertex2f(controlPoints[(j+1)*horNumOfConPoints + i]->leftEyeTransPointCoordinate.x,
                            controlPoints[(j+1)*horNumOfConPoints + i]->leftEyeTransPointCoordinate.y);
                    glColor3f(0, 0.5, 0.5);
                    glVertex2f(controlPoints[j*horNumOfConPoints + i]->rightEyeTransPointCoordinate.x,
                            controlPoints[j*horNumOfConPoints + i]->rightEyeTransPointCoordinate.y);
                    glVertex2f(controlPoints[j*horNumOfConPoints + i +1]->rightEyeTransPointCoordinate.x,
                            controlPoints[j*horNumOfConPoints + i +1]->rightEyeTransPointCoordinate.y);

                    glVertex2f(controlPoints[j*horNumOfConPoints + i]->rightEyeTransPointCoordinate.x,
                            controlPoints[j*horNumOfConPoints + i]->rightEyeTransPointCoordinate.y);
                    glVertex2f(controlPoints[(j+1)*horNumOfConPoints + i]->rightEyeTransPointCoordinate.x,
                            controlPoints[(j+1)*horNumOfConPoints + i]->rightEyeTransPointCoordinate.y);
                }
            }
            for(int i=0;i<horNumOfConPoints-1;i++){
                {
                    glColor3f(0.4,0.0, 0.0);
                    glVertex2f(controlPoints[(verNumOfConPoints-1)*horNumOfConPoints + i]->leftEyeTransPointCoordinate.x,
                            controlPoints[(verNumOfConPoints-1)*horNumOfConPoints + i]->leftEyeTransPointCoordinate.y);
                    glVertex2f(controlPoints[(verNumOfConPoints-1)*horNumOfConPoints + i +1]->leftEyeTransPointCoordinate.x,
                            controlPoints[(verNumOfConPoints-1)*horNumOfConPoints + i +1]->leftEyeTransPointCoordinate.y);
                    glColor3f(0, 0.5, 0.5);
                    glVertex2f(controlPoints[(verNumOfConPoints-1)*horNumOfConPoints + i]->rightEyeTransPointCoordinate.x,
                            controlPoints[(verNumOfConPoints-1)*horNumOfConPoints + i]->rightEyeTransPointCoordinate.y);
                    glVertex2f(controlPoints[(verNumOfConPoints-1)*horNumOfConPoints + i +1]->rightEyeTransPointCoordinate.x,
                            controlPoints[(verNumOfConPoints-1)*horNumOfConPoints + i +1]->rightEyeTransPointCoordinate.y);
                }
            }
            for(int j=0;j<verNumOfConPoints-1;j++)
            {
                glColor3f(0.4,0.0, 0.0);
                glVertex2f(controlPoints[j*horNumOfConPoints + horNumOfConPoints-1]->leftEyeTransPointCoordinate.x,
                        controlPoints[j*horNumOfConPoints + horNumOfConPoints-1]->leftEyeTransPointCoordinate.y);
                glVertex2f(controlPoints[(j+1)*horNumOfConPoints + horNumOfConPoints-1]->leftEyeTransPointCoordinate.x,
                        controlPoints[(j+1)*horNumOfConPoints + horNumOfConPoints-1]->leftEyeTransPointCoordinate.y);
                glColor3f(0, 0.5, 0.5);
                glVertex2f(controlPoints[j*horNumOfConPoints + horNumOfConPoints-1]->rightEyeTransPointCoordinate.x,
                        controlPoints[j*horNumOfConPoints + horNumOfConPoints-1]->rightEyeTransPointCoordinate.y);
                glVertex2f(controlPoints[(j+1)*horNumOfConPoints + horNumOfConPoints-1]->rightEyeTransPointCoordinate.x,
                        controlPoints[(j+1)*horNumOfConPoints + horNumOfConPoints-1]->rightEyeTransPointCoordinate.y);
            }

        }
        glEnd();

    }
    //////

   /* for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            controlPoints[i][j]->draw();
        }
    }*/

    glPointSize(-50/camera->zPos - (5.f-camera->rProjection)/5);
    float dt=0.007;

    int degree = 3;

    int knotNumber = verNumOfConPoints +4;
    float startValue = 0.f;
    float knotDT = 1.0f / (knotNumber-7);
    knotVector.resize(knotNumber);
    knotVector[0] = 0;
    knotVector[1] = 0;
    knotVector[2] = 0;
    knotVector[knotNumber-3] = 1;
    knotVector[knotNumber-2] = 1;
    knotVector[knotNumber-1] = 1;
    for(int i=3;i<knotNumber-3;i++)
    {

        knotVector[i] = startValue;
        startValue += knotDT;

    }

    glPointSize(1);
    glBegin(GL_POINTS);
    glColor3f(1,1,1);
    //draw columns
    for(float i=0;i<1.01f;i+=u)
    {

        for(float j=0;j<1.f;j+=dt)
        {
            pointToDraw = vec4(computePoint(i,j),1);
            if(!camera->isStereoscopic){
                pointToDraw = camera->transformationMatrix* pointToDraw;
                pointToDraw.x = pointToDraw.x / pointToDraw.w;
                pointToDraw.y = pointToDraw.y / pointToDraw.w;
                pointToDraw.x /= camera->xRatio;
                pointToDraw.y /= camera->yRatio;
                glVertex2f(pointToDraw.x,pointToDraw.y);
            }
            else{
                vec4 point2 = vec4(pointToDraw);
                glColor3f(0.4,0.0, 0.0);
                pointToDraw = camera->transformationMatrixLeftEye * pointToDraw;
                pointToDraw.x /= pointToDraw.w;
                pointToDraw.y /= pointToDraw.w;
                pointToDraw.x /= camera->xRatio;
                pointToDraw.y /= camera->yRatio;

                if(!(pointToDraw.w >=-0.06)) // clip
                    glVertex2f(pointToDraw.x, pointToDraw.y);

                glColor3f(0, 0.5, 0.5);
                point2 = camera->transformationMatrixRightEye * point2;
                point2.x /= point2.w;
                point2.y /= point2.w;
                point2.x /= camera->xRatio;
                point2.y /= camera->yRatio;

                if(!(point2.w >=-0.06)) // clip
                    glVertex2f(point2.x, point2.y);
            }
        }
    }
    glEnd();
}

float BSplineSurface::bsplineRecurive(float t, int n, int i,
                      const vector<float>& knotVector){
    if (n == 0){
        if(t >= knotVector[i] && t < knotVector[i+1])
            return 1;
        else
            return 0;
    }
    float leftRecursion = (t - knotVector[i]);
    float leftDenominator = (knotVector[i+n] - knotVector[i]);
    if(leftRecursion == 0 || leftDenominator == 0)
        leftRecursion = 1;
    else
        leftRecursion /= leftDenominator;

    float rightRecursion = knotVector[i+1+n] - t;
    float rightDenominator = (knotVector[i+1+n] - knotVector[i+1]);
    if(rightRecursion == 0 || rightDenominator == 0)
        rightRecursion = 1;
    else
        rightRecursion /= rightDenominator;

    leftRecursion *= bsplineRecurive(t, n-1, i, knotVector);
    rightRecursion *= bsplineRecurive(t, n-1, i+1, knotVector);

    return leftRecursion + rightRecursion;
}

vec3 BSplineSurface::computePoint(float u, float v)
{
    vec3 tmp = vec3(0,0,0);
    for(int i=0;i<verNumOfConPoints;i++)
    {
        for(int j=0;j<horNumOfConPoints;j++)
        {
            tmp+= controlPoints[horNumOfConPoints*i+j]->localTransPointCoordinates * bsplineRecurive(u,3,i,knotVector)*bsplineRecurive(v,3,i,knotVector);
        }
    }
    return tmp;
}
