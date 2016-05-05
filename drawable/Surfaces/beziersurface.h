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
    vector<BezierPatch*> patches;
private:
   /* float getMaxLength()
    {
        float max = 0;
        float tmpRow =0;
        for(int i=0;i<horNumOfConPoints;i++)
        {
            for(int j=0;j<verNumOfConPoints-1;j++)
            {
                tmpRow += euclideanDistance2(controlPoints[j*horNumOfConPoints+i]->localTransPointCoordinates,controlPoints[(j+1)*horNumOfConPoints+i]->localTransPointCoordinates);
            }
            if(tmpRow>max)max=tmpRow;
            tmpRow=0;
        }
    }
    float euclideanDistance2(vec3& point1, vec3& point2)
    {
        return sqrt(pow(point1.x-point2.x,2)+pow(point1.y-point2.y,2)+pow(point1.z-point2.z,2));
    }*/

    static int id;


};

#endif // BEZIERSURFACE_H
