#include "bspline.h"

BSpline::BSpline()
{

}

BSpline::BSpline(Camera *camera)
{
    this->camera = camera;
    drawPolygon = true;
    id++;
    name = "BSpline_";
    name += to_string(id);
}

void BSpline::removePointByName(string name)
{
    for(int i=0; i<deBoorPoints.size();i++){
        if(deBoorPoints[i]->name == name)
        {
            std::vector<Point*>::iterator position = std::find(deBoorPoints.begin(), deBoorPoints.end(), deBoorPoints[i]);
                if (position != deBoorPoints.end()) // == myVector.end() means the element was not found
                    deBoorPoints.erase(position);
            break;
        }
    }
}

int BSpline::id = 0;

void BSpline::draw()
{
    if(drawPolygon)
    {
        glPointSize(1);
        glBegin(GL_LINES);
        glColor4f(1,1.0, 1.0,1.0);
        if(deBoorPoints.size()!=0){
            for(int i=0;i<deBoorPoints.size()-1;i++)
            {
                glVertex2f(deBoorPoints[i]->transPointCoordinates.x,deBoorPoints[i]->transPointCoordinates.y);
                glVertex2f(deBoorPoints[i+1]->transPointCoordinates.x,deBoorPoints[i+1]->transPointCoordinates.y);
            }
        }
        glEnd();
    }
}
