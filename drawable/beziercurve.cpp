#include "beziercurve.h"
#include <GL/gl.h>

BezierCurve::BezierCurve()
{

}

BezierCurve::BezierCurve(Camera *camera)
{
    this->camera = camera;
    drawPolygon = true;
    id++;
    name = "BezierCurve_";
    name += std::to_string(id);

    globalTransformationMatrix = camera->transformationMatrix;
}

int BezierCurve::id = 0;

void BezierCurve::draw()
{
    if(drawPolygon)
    {
        glBegin(GL_LINES);
        glColor4f(1,1.0, 1.0,1.0);
        if(pointVector.size()!=0){
            for(int i=0;i<pointVector.size()-1;i++)
            {
                glVertex2f(pointVector[i]->transPointCoordinates.x,pointVector[i]->transPointCoordinates.y);
                glVertex2f(pointVector[i+1]->transPointCoordinates.x,pointVector[i+1]->transPointCoordinates.y);
            }
        }
        glEnd();
    }
}
