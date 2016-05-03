#include "beziersurface.h"

BezierSurface::BezierSurface()
{

}

BezierSurface::BezierSurface(Camera* camera)
{
    this->camera = camera;

    verNumOfPatches = 5;
    horNumOfPatches = 5;

    horNumOfConPoints = horNumOfPatches*3+1;
    verNumOfConPoints = verNumOfPatches*3+1;

    controlPoints.resize(verNumOfConPoints*horNumOfConPoints);
    patches.resize(verNumOfPatches*horNumOfPatches);

    initControlPoints();
    initPatches();


}

void BezierSurface::initControlPoints()
{
    float width = 0.2f;
    float height = 0.2f;
    float totalWidth = width*horNumOfPatches;
    float totalHeight = height*verNumOfPatches;

    float widthDT = totalWidth / (horNumOfConPoints-1);
    float heightDT = totalHeight / (verNumOfConPoints-1);
    int m=0,n=0;
    for(float i = -(totalWidth/(float)2);i< totalWidth/(float)2+widthDT/2;i+=widthDT,m++)
    {
        n=0;
        for(float j = -(totalHeight/(float)2);j< totalHeight/(float)2+heightDT/2;j+=heightDT,n++)
        {
            controlPoints[m*verNumOfConPoints + n] = new Point(camera);
            controlPoints[m*verNumOfConPoints + n]->xPos = i;
            controlPoints[m*verNumOfConPoints + n]->updateTranslationMatX();
            controlPoints[m*verNumOfConPoints + n]->yPos = j;
            controlPoints[m*verNumOfConPoints + n]->updateTranslationMatY();
        }
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

                    bezierPatch->controlPoints[k][l] = controlPoints[(verFix+k)*verNumOfConPoints + horFix+l];
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
