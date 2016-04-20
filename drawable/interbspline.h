#ifndef INTERBSPLINE_H
#define INTERBSPLINE_H
#include "drawable/drawable.h"
#include "point.h"
#include "Camera/camera.h"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include <vector>
#include <GL/gl.h>
#include <algorithm>

using namespace std;
using namespace glm;

class InterBSpline : public Drawable
{
public:
    InterBSpline();
    InterBSpline(Camera* camera);
    vector<Point*> deBoorPoints;
    void removePointByName(string name);
    bool drawPolygon;
    vector<float> knotVector;

private:
    static int id;
    Camera* camera;

    vec4 computeBSpline(const vector<float>& knotVector,float t, int n);
    vector<vec4> calculateBezierPoints();
    float bsplineRecurive(float t, int n, int i,const vector<float>& knotVector);
    void draw();
};

#endif // INTERBSPLINE_H
