#include "beziersurface.h"

BezierSurface::BezierSurface()
{

}

int BezierSurface::id = 0;

 void BezierSurface::initC0(Camera *camera, float totalHeight, int verNumOfPatches, int horNumOfPatches, bool isFlatSurface)
{
    isDeBoorControled = false;
    this->camera = camera;
    drawBezierNet = false;
    this->isFlatSurface = isFlatSurface;
    this->totalHeight = totalHeight;
    this->verNumOfPatches = verNumOfPatches;
    this->horNumOfPatches = horNumOfPatches;
    if(isFlatSurface)horNumOfConPoints = horNumOfPatches*3+1;
    else horNumOfConPoints = horNumOfPatches*3;
    verNumOfConPoints = verNumOfPatches*3+1;
    controlPoints.resize(verNumOfConPoints*horNumOfConPoints);
    patches.resize(verNumOfPatches*horNumOfPatches);
    initControlPoints();
    initPatches();
    initThreads();
}

 void BezierSurface::initC2(Camera *camera, float totalHeight, int verNumOfPatches, int horNumOfPatches, bool isFlatSurface)
 {
     isDeBoorControled = true;
     this->camera = camera;
     drawBezierNet = false;
     this->isFlatSurface = isFlatSurface;
     this->totalHeight = totalHeight;
     this->verNumOfPatches = verNumOfPatches;
     this->horNumOfPatches = horNumOfPatches;
     if(isFlatSurface){
         horNumOfDeBoorePoints = horNumOfPatches + 3;
         horNumOfConPoints = horNumOfPatches*3+1;
     }
     else{
         horNumOfDeBoorePoints = horNumOfPatches+3;
         horNumOfConPoints = horNumOfPatches*3+1;
     }
     verNumOfDeBoorePoints = verNumOfPatches + 3;
     verNumOfConPoints = verNumOfPatches*3+1;
     controlPoints.resize(verNumOfConPoints*horNumOfConPoints);
     for(int i=0;i<verNumOfConPoints*horNumOfConPoints;i++)
     {
        controlPoints[i] = new Point(camera);
     }
     deBoorePoints.resize(verNumOfDeBoorePoints*horNumOfDeBoorePoints);
     patches.resize(verNumOfPatches*horNumOfPatches);
     initDeBoorePoints();
     deBooreToBezier();
     initPatches();
     initThreads();
 }

BezierSurface::BezierSurface(Camera *camera, float totalWidth, float totalHeight, int verNumOfPatches, int horNumOfPatches,bool isC0)
{
    id++;
    string continuity;
    if(isC0)continuity="C0";
    else continuity="C2";
    name = continuity + "BezierFlatSurface_";
    name += std::to_string(id);
    this->totalWidth = totalWidth;
    if(isC0)initC0(camera,totalHeight,verNumOfPatches,horNumOfPatches,true);
    else initC2(camera,totalHeight,verNumOfPatches,horNumOfPatches,true);
}



BezierSurface::BezierSurface(Camera *camera, float radius, float totalHeight, int verNumOfPatches, int horNumOfPatches,bool tmp, bool isC0)
{
    id++;
    string continuity;
    if(isC0)continuity="C0";
    else continuity="C2";
    name = continuity + "BezierCylinderSurface_";
    name += std::to_string(id);
    this->totalWidth = 1.0f;
    this->radius = radius;
    if(isC0)initC0(camera,totalHeight,verNumOfPatches,horNumOfPatches,false);
    else initC2(camera,totalHeight,verNumOfPatches,horNumOfPatches,false);
}

void BezierSurface::initThreads()
{
    for(int i=0;i<patches.size();i++)
    {
        threadTable[i%8]++;
    }
}


void BezierSurface::initDeBoorePoints()
{
    //flat surface

    float widthDT = totalWidth / (horNumOfDeBoorePoints - 1);
    float heightDT = totalHeight / (verNumOfDeBoorePoints-1);
    int m=0,n=0;
    if(isFlatSurface){
    for(float i = -(totalWidth/(float)2);i< totalWidth/(float)2+widthDT/2;i+=widthDT,m++)
    {
        n=0;
        for(float j = -(totalHeight/(float)2);j< totalHeight/(float)2+heightDT/2;j+=heightDT,n++)
        {
            deBoorePoints[n*horNumOfDeBoorePoints + m] = new Point(camera);
            deBoorePoints[n*horNumOfDeBoorePoints + m]->xPos = i;
            deBoorePoints[n*horNumOfDeBoorePoints + m]->updateTranslationMatX();
            deBoorePoints[n*horNumOfDeBoorePoints + m]->yPos = j;
            deBoorePoints[n*horNumOfDeBoorePoints + m]->updateTranslationMatY();
        }
    }
    }else{
    //// x=r\cos(t), \ \  y=r\sin(t)
    float t = 0;
    widthDT = totalWidth / (horNumOfDeBoorePoints-3);
    for(float i = 0;i< totalWidth;i+=widthDT,m++)
    {
        n=0;
        for(float j = 0;j< totalHeight+heightDT/2;j+=heightDT,n++)
        {
            t= i/totalWidth;
            deBoorePoints[n*horNumOfDeBoorePoints + m] = new Point(camera);
            deBoorePoints[n*horNumOfDeBoorePoints + m]->xPos = radius*cos(6.28*t);
            deBoorePoints[n*horNumOfDeBoorePoints + m]->updateTranslationMatX();
            deBoorePoints[n*horNumOfDeBoorePoints + m]->yPos = -totalHeight/4 + j/2;
            deBoorePoints[n*horNumOfDeBoorePoints + m]->updateTranslationMatY();
            deBoorePoints[n*horNumOfDeBoorePoints + m]->zPos = radius*sin(6.28*t);
            deBoorePoints[n*horNumOfDeBoorePoints + m]->updateTranslationMatZ();
        }
    }

    for(int i=0;i<3;i++){
        n=0;
        for(float j = 0;j< totalHeight+heightDT/2;j+=heightDT,n++)
        {
            deBoorePoints[n*horNumOfDeBoorePoints + m+i] = deBoorePoints[n*horNumOfDeBoorePoints+i];
        }
    }
    }
}

void BezierSurface::initControlPoints()
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
    n=0;
}

void BezierSurface::deBooreToBezier()
{
    vec3 pos0,pos1,pos2,pos3;
    int segmentCount = horNumOfDeBoorePoints - 3;
    rowTMPBezierPoints.clear();
    for(int i= 0;i<verNumOfDeBoorePoints;i++)
    {
        for(int j=0;j<segmentCount-1;j++)
        {
            pos0 = deBoorePoints[i*horNumOfDeBoorePoints+j+0]->localTransPointCoordinates;
            pos1 = deBoorePoints[i*horNumOfDeBoorePoints+j+1]->localTransPointCoordinates;
            pos2 = deBoorePoints[i*horNumOfDeBoorePoints+j+2]->localTransPointCoordinates;

            rowTMPBezierPoints.push_back(new Point(vec3((pos0 + pos1*4.0f + pos2)/6.0f)));
            rowTMPBezierPoints.push_back(new Point(vec3((pos1*4.0f + pos2*2.0f)/6.0f)));
            rowTMPBezierPoints.push_back(new Point(vec3((pos1*2.0f + pos2*4.0f)/6.0f)));
        }
        pos0 = deBoorePoints[i*horNumOfDeBoorePoints+segmentCount-1+0]->localTransPointCoordinates;
        pos1 = deBoorePoints[i*horNumOfDeBoorePoints+segmentCount-1+1]->localTransPointCoordinates;
        pos2 = deBoorePoints[i*horNumOfDeBoorePoints+segmentCount-1+2]->localTransPointCoordinates;
        pos3 = deBoorePoints[i*horNumOfDeBoorePoints+segmentCount-1+3]->localTransPointCoordinates;

        rowTMPBezierPoints.push_back(new Point(vec3((pos0 + pos1*4.0f + pos2)/6.0f)));
        rowTMPBezierPoints.push_back(new Point(vec3((pos1*4.0f + pos2*2.0f)/6.0f)));
        rowTMPBezierPoints.push_back(new Point(vec3((pos1*2.0f + pos2*4.0f)/6.0f)));
        rowTMPBezierPoints.push_back(new Point(vec3((pos1 + pos2*4.0f + pos3)/6.0f)));
    }

    segmentCount = verNumOfDeBoorePoints -3;
    int numOfRowBezPoints = 1+3*(horNumOfDeBoorePoints - 3);
    for(int i=0;i<numOfRowBezPoints;i++)
    {
        for(int j=0;j<segmentCount-1;j++)
        {
            pos0 = rowTMPBezierPoints[j*numOfRowBezPoints+i+0]->localTransPointCoordinates;
            pos1 = rowTMPBezierPoints[j*numOfRowBezPoints+i+1*numOfRowBezPoints]->localTransPointCoordinates;
            pos2 = rowTMPBezierPoints[j*numOfRowBezPoints+i+2*numOfRowBezPoints]->localTransPointCoordinates;

            controlPoints[(j*3+0)*numOfRowBezPoints + i]->localTransPointCoordinates = vec3((pos0 + pos1*4.0f + pos2)/6.0f);
            controlPoints[(j*3+1)*numOfRowBezPoints + i]->localTransPointCoordinates = vec3((pos1*4.0f + pos2*2.0f)/6.0f);
            controlPoints[(j*3+2)*numOfRowBezPoints + i]->localTransPointCoordinates = vec3((pos1*2.0f + pos2*4.0f)/6.0f);
        }
        pos0 = rowTMPBezierPoints[(segmentCount-1)*numOfRowBezPoints+i+0]->localTransPointCoordinates;
        pos1 = rowTMPBezierPoints[(segmentCount-1)*numOfRowBezPoints+i+1*numOfRowBezPoints]->localTransPointCoordinates;
        pos2 = rowTMPBezierPoints[(segmentCount-1)*numOfRowBezPoints+i+2*numOfRowBezPoints]->localTransPointCoordinates;
        pos3 = rowTMPBezierPoints[(segmentCount-1)*numOfRowBezPoints+i+3*numOfRowBezPoints]->localTransPointCoordinates;

        controlPoints[((segmentCount-1)*3+0)*numOfRowBezPoints + i]->localTransPointCoordinates = vec3((pos0 + pos1*4.0f + pos2)/6.0f);
        controlPoints[((segmentCount-1)*3+1)*numOfRowBezPoints + i]->localTransPointCoordinates = vec3((pos1*4.0f + pos2*2.0f)/6.0f);
        controlPoints[((segmentCount-1)*3+2)*numOfRowBezPoints + i]->localTransPointCoordinates = vec3((pos1*2.0f + pos2*4.0f)/6.0f);
        controlPoints[((segmentCount-1)*3+3)*numOfRowBezPoints + i]->localTransPointCoordinates = vec3((pos1 + pos2*4.0f + pos3)/6.0f);
    }
}

void BezierSurface::initPatches()
{
    for(int i=0;i<horNumOfPatches;i++)
    {
        for(int j=0;j<verNumOfPatches;j++)
        {
            BezierPatch* bezierPatch = new BezierPatch(camera);
            for(int k=0;k<4;k++)
            {
                for(int l=0;l<4;l++)
                {
                    int horFix =0;
                    int verFix =0;
                    if(i >0)horFix = i*3;
                    if(j >0)verFix = j*3;
                    int ctrlPNum = (verFix+k)*horNumOfConPoints + horFix+l;
                ///   printf("Control point index : %d \n",ctrlPNum);
                    bezierPatch->controlPoints[k][l] = controlPoints[ctrlPNum];
                    if(i==horNumOfPatches-1 && l==3 && !isFlatSurface)
                    {
                        ctrlPNum = (verFix+k)*horNumOfConPoints;
                    ///   printf("Control point index : %d \n",ctrlPNum);
                        bezierPatch->controlPoints[k][l] = controlPoints[ctrlPNum];
                    }
                }
            }
            patches[i*verNumOfPatches+j] = bezierPatch;
        }
    }

}

void BezierSurface::draw()
{
    if(isDeBoorControled) deBooreToBezier();
    if(drawBezierNet)
    {
        glColor3f(0.2,1,0.3);
        glBegin(GL_LINES);
        if(!camera->isStereoscopic){
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
        if(isDeBoorControled)
        {
            glColor3f(0.2,1,0.3);
            glBegin(GL_LINES);
            if(!camera->isStereoscopic){
                for(int i=0;i<horNumOfDeBoorePoints-1;i++){
                    for(int j=0;j<verNumOfDeBoorePoints-1;j++)
                    {
                        glVertex2f(deBoorePoints[j*horNumOfDeBoorePoints + i]->transPointCoordinates.x,
                                deBoorePoints[j*horNumOfDeBoorePoints + i]->transPointCoordinates.y);
                        glVertex2f(deBoorePoints[j*horNumOfDeBoorePoints + i +1]->transPointCoordinates.x,
                                deBoorePoints[j*horNumOfDeBoorePoints + i +1]->transPointCoordinates.y);

                        glVertex2f(deBoorePoints[j*horNumOfDeBoorePoints + i]->transPointCoordinates.x,
                                deBoorePoints[j*horNumOfDeBoorePoints + i]->transPointCoordinates.y);
                        glVertex2f(deBoorePoints[(j+1)*horNumOfDeBoorePoints + i]->transPointCoordinates.x,
                                deBoorePoints[(j+1)*horNumOfDeBoorePoints + i]->transPointCoordinates.y);
                    }
                }
                for(int i=0;i<horNumOfDeBoorePoints-1;i++){
                    {
                        glVertex2f(deBoorePoints[(verNumOfDeBoorePoints-1)*horNumOfDeBoorePoints + i]->transPointCoordinates.x,
                                deBoorePoints[(verNumOfDeBoorePoints-1)*horNumOfDeBoorePoints + i]->transPointCoordinates.y);
                        glVertex2f(deBoorePoints[(verNumOfDeBoorePoints-1)*horNumOfDeBoorePoints + i +1]->transPointCoordinates.x,
                                deBoorePoints[(verNumOfDeBoorePoints-1)*horNumOfDeBoorePoints + i +1]->transPointCoordinates.y);
                    }
                }
                for(int j=0;j<verNumOfDeBoorePoints-1;j++)
                {
                    glVertex2f(deBoorePoints[j*horNumOfDeBoorePoints + horNumOfDeBoorePoints-1]->transPointCoordinates.x,
                            deBoorePoints[j*horNumOfDeBoorePoints + horNumOfDeBoorePoints-1]->transPointCoordinates.y);
                    glVertex2f(deBoorePoints[(j+1)*horNumOfDeBoorePoints + horNumOfDeBoorePoints-1]->transPointCoordinates.x,
                            deBoorePoints[(j+1)*horNumOfDeBoorePoints + horNumOfDeBoorePoints-1]->transPointCoordinates.y);
                }
            }
            else{
                for(int i=0;i<horNumOfDeBoorePoints-1;i++){
                    for(int j=0;j<verNumOfDeBoorePoints-1;j++)
                    {
                        glColor3f(0.4,0.0, 0.0);
                        glVertex2f(controlPoints[j*horNumOfDeBoorePoints + i]->leftEyeTransPointCoordinate.x,
                                controlPoints[j*horNumOfDeBoorePoints + i]->leftEyeTransPointCoordinate.y);
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
    }


    vector<thread> workers;
    int patchCounter = 0;
    for(int i=0;i<8;i++)
    {
        workers.push_back(thread([this,i,patchCounter](){
            for(int j=0;j<threadTable[i];j++)
            {
               patches[patchCounter+j]->calculatePoints();
            }
        }));
        patchCounter += threadTable[i];
    }
    std::for_each(workers.begin(), workers.end(), [](std::thread &t)
        {
            t.join();
        });



   /*for(int i=0;i<patches.size();i++)
    {
            patches[i]->calculatePoints();
    }*/

    for(int i=0;i<patches.size();i++)
    {
            patches[i]->draw();
    }
}
