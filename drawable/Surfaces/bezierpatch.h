#ifndef BEZIERPATCH_H
#define BEZIERPATCH_H
#include "drawable/drawable.h"
#include "drawable/point.h"
#include "Camera/camera.h"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include <vector>
#include <GL/gl.h>
#include <algorithm>

using namespace std;
using namespace glm;

class BezierPatch: public Drawable
{
public:
    BezierPatch();
    BezierPatch(Camera* camera);
    void draw();
private:
    Camera* camera;
    Point* controlPoints[4][4];
    vec4 tmp;
    vec4 pointToDraw;

    float width,height,u,v;

    float berBasis(int i, float u);
    vec4 computePoint(float u, float v);

};

#endif // BEZIERPATCH_H
