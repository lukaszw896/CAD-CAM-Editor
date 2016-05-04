#include "beziersurface.h"

BezierSurface::BezierSurface()
{

}

BezierSurface::BezierSurface(Camera* camera)
{
    this->camera = camera;
    isFlatSurface = false;
    verNumOfPatches = 5;
    horNumOfPatches = 5;

    if(isFlatSurface)horNumOfConPoints = horNumOfPatches*3+1;
    else horNumOfConPoints = horNumOfPatches*3;
    verNumOfConPoints = verNumOfPatches*3+1;

    controlPoints.resize(verNumOfConPoints*horNumOfConPoints);
    patches.resize(verNumOfPatches*horNumOfPatches);

    initControlPoints();
    initPatches();


}

void BezierSurface::initControlPoints()
{
    //flat surface
    float width = 0.3f;
    float height = 0.3f;
    float totalWidth = width*horNumOfPatches;
    float totalHeight = height*verNumOfPatches;

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
            controlPoints[n*horNumOfConPoints + m]->xPos = 0.3f*cos(6.28*t);
            controlPoints[n*horNumOfConPoints + m]->updateTranslationMatX();
            controlPoints[n*horNumOfConPoints + m]->yPos = -totalHeight/4 + j/2;
            controlPoints[n*horNumOfConPoints + m]->updateTranslationMatY();
            controlPoints[n*horNumOfConPoints + m]->zPos = 0.3f*sin(6.28*t);
            controlPoints[n*horNumOfConPoints + m]->updateTranslationMatZ();
           // printf("Control point init pos : %d , x: %lf, y: %lf \n",m*verNumOfConPoints + n,i,j);
            printf("%lf \n",t);
        }
    }
    }
    //// x=r\cos(t), \ \  y=r\sin(t)
    /// cylinder

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
    for(int i=0;i<patches.size();i++)
    {
            patches[i]->draw();
    }
}
