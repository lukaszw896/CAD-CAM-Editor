#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H
#include "drawable/drawable.h"
#include "point.h"
#include "Camera/camera.h"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include <vector>

using namespace std;

class BezierCurve: public Drawable
{
public:
    BezierCurve();
    BezierCurve(Camera* camera);
    vector<Point*> pointVector;
private:

    static int id;
    bool drawPolygon;

    Camera* camera;



    vector<glm::vec4> curvePointsCoordinates;
    vector<glm::vec4> curveTransPointsCooridnates;

    glm::vec4 leftEyeCurveTransPointCoordinate;
    glm::vec4 rightEyeCurveTransPointCoordinate;

   // glm::mat4 localTransformationMatrix;
    ///In this case I need only camera transformation matrix because any transformation is made of points building curve
    glm::mat4 globalTransformationMatrix;

    void computeLocalTransformationMatrix();
    void computeGlobalTransformationMatrix();
    void transform();
    void draw();
};

#endif // BEZIERCURVE_H
