#ifndef BSPLINE_H
#define BSPLINE_H
#include "drawable/drawable.h"
#include "point.h"
#include "Camera/camera.h"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include <vector>
#include <GL/gl.h>
#include <algorithm>
#include "drawable/beziercurve.h"

using namespace std;
using namespace glm;

class BSpline : public Drawable
{
public:
    BSpline();
    BSpline(Camera* camera);
    vector<Point*> deBoorPoints;
    void removePointByName(string name);
    bool drawPolygon;
    vector<float> knotVector;
    BezierCurve* bezierCurve;

private:
    static int id;
    Camera* camera;


    vec4 computeBSpline(const vector<float>& knotVector,float t, int n);
    void calculateBezierPoints(vector<Point*>*);
    float bsplineRecurive(float t, int n, int i,const vector<float>& knotVector);
    void draw();
    void printVec(vec3 v)
    {
        printf("X: %lf, Y: %lf, Z: %lf \n",v.x,v.y,v.z);
    }
    void drawPoint(vec3 point)
    {
        vec4 pointToDraw = vec4(point,1);
        pointToDraw = camera->transformationMatrix * pointToDraw;
        pointToDraw.x /= pointToDraw.w;
        pointToDraw.y /= pointToDraw.w;
        pointToDraw.x /= camera->xRatio;
        pointToDraw.y /= camera->yRatio;
        glPointSize(10);
        glColor3f(1,0,0);
        glBegin(GL_POINTS);
        glVertex2f(pointToDraw.x,pointToDraw.y);
        glEnd();
    }

};

#endif // BSPLINE_H
