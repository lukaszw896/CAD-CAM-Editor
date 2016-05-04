#ifndef INTERBSPLINE_H
#define INTERBSPLINE_H
#include "drawable/drawable.h"
#include "point.h"
#include "Camera/camera.h"
#include "glm/vec4.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include <vector>
#include <GL/gl.h>
#include <algorithm>
#include <iostream>

///BSPLINE BASIS COEFFICIENTS
///Source: http://www.cs.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/B-spline/bspline-curve-coef.html
///GLOBAL INTERPOLATION
///Source: http://www.cs.mtu.edu/~shene/COURSES/cs3621/NOTES/INT-APP/CURVE-INT-global.html
///CHORD PARAMETRIZATION
///Source: http://www.cs.mtu.edu/~shene/COURSES/cs3621/NOTES/INT-APP/PARA-chord-length.html
///KNOT VECTOR GENERATION
/// http://www.cs.mtu.edu/~shene/COURSES/cs3621/NOTES/INT-APP/PARA-knot-generation.html
using namespace std;
using namespace glm;

class InterBSpline : public Drawable
{
public:
    InterBSpline();
    InterBSpline(Camera* camera);
    vector<Point*> deBoorPoints;
    vector<vec3> controlPoints;
    void removePointByName(string name);
    bool drawPolygon;
    vector<float> knotVector;

    vector<float> parameters;
private:
    float interpolatingPolygonLength;
    static int id;
    Camera* camera;

    vec4 computeBSpline(const vector<float>& knotVector,float t, int n);
    vec4 computeDrawingBSpline(const vector<float>& knotVector,float t, int n);

    float bsplineRecurive(float t, int n, int i,const vector<float>& knotVector);

    void computeChordParameters();
    void computeKnotVector();
    float euclideanDistance(vec3& point1, vec3& point2);
    void computeControlPoints();
    void draw();
    void printMat(float** a, int n, int m);
};

#endif // INTERBSPLINE_H
