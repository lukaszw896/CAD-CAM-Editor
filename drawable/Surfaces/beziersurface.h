#ifndef BEZIERSURFACE_H
#define BEZIERSURFACE_H
#include "drawable/drawable.h"
#include "drawable/point.h"
#include "drawable/Surfaces/bezierpatch.h"
#include "Camera/camera.h"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include <vector>
#include <GL/gl.h>
#include <algorithm>

using namespace std;
using namespace glm;

class BezierSurface: public Drawable
{
public:
    bool isFlatSurface;
    bool drawBezierNet;
    BezierSurface();
    BezierSurface(Camera* camera);
    BezierSurface(Camera *camera,float totalWidth,float totalHeight,
                  int verNumOfPatches, int horNumOfPatches);
    BezierSurface(Camera *camera, float radius, float totalHeight,
                  int verNumOfPatches, int horNumOfPatches,bool tmp);
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

private:
    static int id;
    vector<BezierPatch*> patches;

};

#endif // BEZIERSURFACE_H
