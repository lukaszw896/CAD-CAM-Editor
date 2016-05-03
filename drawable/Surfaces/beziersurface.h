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
    BezierSurface();
    BezierSurface(Camera* camera);
    Camera * camera;
    int verNumOfPatches;
    int horNumOfPatches;

    int horNumOfConPoints;
    int verNumOfConPoints;

    void initControlPoints();
    void initPatches();
    void draw();

private:
    vector<BezierPatch*> patches;
    vector<Point*> controlPoints;
};

#endif // BEZIERSURFACE_H
