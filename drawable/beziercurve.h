#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H
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

class BezierCurve: public Drawable
{
public:
    BezierCurve();
    BezierCurve(Camera* camera);
    vector<Point*> pointVector;
    void removePointByName(string name);
    bool drawPolygon;
    vector<glm::vec4> curvePointsCoordinates;
    void draw();

private:

    static int id;


    Camera* camera;




    vector<glm::vec4> curveTransPointsCooridnates;
    vector<int> sectionPointNum;

    glm::vec4 leftEyeCurveTransPointCoordinate;
    glm::vec4 rightEyeCurveTransPointCoordinate;

    glm::vec4 pointToDraw;

   // glm::mat4 localTransformationMatrix;
    ///In this case I need only camera transformation matrix because any transformation is made of points building curve
    glm::mat4 globalTransformationMatrix;

    int numberOfPoints;

    int twoPointsDist(Point* p1, Point* p2);

    int polygonLength(Point* p1, Point* p2 )
    {
        return twoPointsDist(p1,p2);
    }

    int polygonLength(Point* p1, Point* p2, Point* p3 )
    {
        return (twoPointsDist(p1,p2) + twoPointsDist(p2,p3) + twoPointsDist(p3,p1));
    }

    int polygonLength(Point* p1, Point* p2, Point* p3, Point* p4 )
    {
        return (twoPointsDist(p1,p2) + twoPointsDist(p2,p3) + twoPointsDist(p3,p4) + twoPointsDist(p4,p1));
    }

    void oneDimBezier0C(Point* p1, Point* p2, int pointNum);

    void twoDimBezier0C(Point* p1, Point* p2, Point* p3, int pointNum);

    void threeDimBezier0C(Point* p1, Point* p2, Point* p3, Point* p4, int pointNum);

    void drawSingleOGLPoint(vec4* point);

    void transform();
};

#endif // BEZIERCURVE_H
