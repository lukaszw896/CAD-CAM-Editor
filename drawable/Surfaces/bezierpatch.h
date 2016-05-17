#ifndef BEZIERPATCH_H
#define BEZIERPATCH_H
#include "drawable/drawable.h"
#include "drawable/point.h"
#include "Camera/camera.h"
#include "glm/vec2.hpp"
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
    Point* controlPoints[4][4];
    float dt;
    void calculatePoints();
    void draw();
    float u,v;
private:
    Camera* camera;

    vec3 tmp;
    vec4 pointToDraw;
    vec4 pointToDraw2;
    vector<vec4> pixelVector;
    vector<vec4> leftEyePixelVector;
    vector<vec4> rightEyePixelVector;

    int pointCounter;
    float width,height;
    float berBasis(int i, float u);
    vec3 computePoint(float u, float v);
    /*float getMaxLength()
    {
        float max = 0;
        float tmpCol =0;
        float tmpRow =0;
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<3;j++)
            {
                tmpCol += euclideanDistance2(controlPoints[i][j]->localTransPointCoordinates,controlPoints[i][j+1]->localTransPointCoordinates);
                tmpRow += euclideanDistance2(controlPoints[j][i]->localTransPointCoordinates,controlPoints[j+1][i]->localTransPointCoordinates);
            }
            if(tmpCol>max)max=tmpCol;
            if(tmpRow>max)max=tmpRow;
            tmpCol=0;
            tmpRow=0;
        }
    }*/
   /* float euclideanDistance2(vec3& point1, vec3& point2)
    {
        return sqrt(pow(point1.x-point2.x,2)+pow(point1.y-point2.y,2)+pow(point1.z-point2.z,2));
    }*/

};

#endif // BEZIERPATCH_H
