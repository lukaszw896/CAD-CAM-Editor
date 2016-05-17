#ifndef BSPLINESURFACE_H
#define BSPLINESURFACE_H
#include "drawable/drawable.h"
#include "drawable/point.h"
#include "Camera/camera.h"
#include "glm/vec4.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include <vector>
#include <GL/gl.h>
#include <algorithm>

using namespace std;
using namespace glm;

class BSplineSurface: public Drawable
{
public:

    bool isFlatSurface;
    bool drawBSplineNet;
    BSplineSurface();
    BSplineSurface(Camera* camera);
    BSplineSurface(Camera *camera,float totalWidth,float totalHeight,
                  int verNumOfPatches, int horNumOfPatches,bool isC0);
    BSplineSurface(Camera *camera, float radius, float totalHeight,
                  int verNumOfPatches, int horNumOfPatches,bool tmp, bool isC0);
    Camera * camera;
    int verNumOfPatches;
    int horNumOfPatches;

    int horNumOfConPoints;
    int verNumOfConPoints;

    float totalWidth;
    float totalHeight;
    float radius;

    void initControlPoints();
    void initPatches();
    void draw();
    vector<Point*> controlPoints;
    vec4 pointToDraw;
    float bsplineRecurive(float t, int n, int i,
                          const vector<float>& knotVector);
    vector<float> knotVector;
    static int id;
    float u = 0.25f, v=0.25f;

    vec3 computePoint(float u, float v);
};

#endif // BSPLINESURFACE_H
