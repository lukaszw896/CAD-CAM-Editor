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

private:
    static int id;
    Camera* camera;

    void draw();

};

#endif // BSPLINE_H
