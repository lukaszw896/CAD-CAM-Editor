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
    bool isDeBoorControled;
    bool isFlatSurface;
    bool drawBezierNet;
    BezierSurface();
    void initC0(Camera *camera, float totalHeight, int verNumOfPatches,
                  int horNumOfPatches, bool isFlatSurface);
    void initC2(Camera *camera, float totalHeight, int verNumOfPatches,
                int horNumOfPatches, bool isFlatSurface);
    BezierSurface(Camera *camera,float totalWidth,float totalHeight,
                  int verNumOfPatches, int horNumOfPatches);
    BezierSurface(Camera *camera, float radius, float totalHeight,
                  int verNumOfPatches, int horNumOfPatches,bool tmp);



    Camera * camera;
    int verNumOfPatches;
    int horNumOfPatches;

    int horNumOfConPoints;
    int verNumOfConPoints;

    int horNumOfDeBoorePoints;
    int verNumOfDeBoorePoints;

    float totalWidth;
    float totalHeight;
    float radius;

    void initDeBoorePoints();
    void initControlPoints();
    void deBooreToBezier();
    void initPatches();
    void draw();
    vector<Point*> controlPoints;
    vector<Point*> deBoorePoints;
    vector<Point*> rowTMPBezierPoints;
    vector<BezierPatch*> patches;
private:

    static int id;


};

#endif // BEZIERSURFACE_H
