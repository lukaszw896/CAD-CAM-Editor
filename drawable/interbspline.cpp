#include "interbspline.h"

InterBSpline::InterBSpline()
{

}

InterBSpline::InterBSpline(Camera *camera)
{
    this->camera = camera;
    drawPolygon = true;
    id++;
    name = "InterBSpline_";
    name += to_string(id);
}

void InterBSpline::removePointByName(string name)
{
    for(int i=0; i<deBoorPoints.size();i++){
        if(deBoorPoints[i]->name == name)
        {
            std::vector<Point*>::iterator position = std::find(deBoorPoints.begin(), deBoorPoints.end(), deBoorPoints[i]);
                if (position != deBoorPoints.end()) // == myVector.end() means the element was not found
                    deBoorPoints.erase(position);
            break;
        }
    }
}

int InterBSpline::id = 0;

void InterBSpline::draw()
{
    if(drawPolygon)
    {
        glPointSize(1);
        glBegin(GL_LINES);
        glColor4f(1,1.0, 1.0,1.0);
        if(deBoorPoints.size()!=0){
            for(int i=0;i<deBoorPoints.size()-1;i++)
            {
                glVertex2f(deBoorPoints[i]->transPointCoordinates.x,deBoorPoints[i]->transPointCoordinates.y);
                glVertex2f(deBoorPoints[i+1]->transPointCoordinates.x,deBoorPoints[i+1]->transPointCoordinates.y);
            }
        }
        glEnd();
    }



        int degree = deBoorPoints.size() -1;
        if(degree>3)degree = 3;
        else if(degree<0) return;

        int knotNumber = deBoorPoints.size()+4;
        float startValue = 0.f;
        float knotDT = 1.0f / knotNumber;
        knotVector.resize(knotNumber);
        for(int i=0;i<knotNumber;i++)
        {
            startValue += knotDT;
            knotVector[i] = startValue;

        }

        //TMP
        float dt = 0.0001/(float)deBoorPoints.size();

        float t = knotVector[1];
        //dt /= 5*t_max;

        glPointSize(1.0f);
        glBegin(GL_POINTS);
        while(t < knotVector[knotNumber-3]){
            vec4 point = computeBSpline(knotVector, t, degree);
            t += dt;

            point = camera->transformationMatrix * point;
            point.x /= point.w;
            point.y /= point.w;
            point.x /= camera->xRatio;
            point.y /= camera->yRatio;

            if(!(point.w >=-0.06)) // clip
            glVertex2f(point.x, point.y);
        }



        glEnd();

}

vector<vec4> InterBSpline::calculateBezierPoints(){

    int segmentCount = deBoorPoints.size() - 3;
    vector<vec4> bezierPoints;
    for(int i = 0; i < segmentCount; i++){
        const vec4& pos0 = deBoorPoints[i+0]->localTransPointCoordinates;
        const vec4& pos1 = deBoorPoints[i+1]->localTransPointCoordinates;
        const vec4& pos2 = deBoorPoints[i+2]->localTransPointCoordinates;
        const vec4& pos3 = deBoorPoints[i+3]->localTransPointCoordinates;

        bezierPoints.push_back(vec4((pos0 + pos1*4.0f + pos2)/6.0f));
        bezierPoints.push_back(vec4((pos1*4.0f + pos2*2.0f)/6.0f));
        bezierPoints.push_back(vec4((pos1*2.0f + pos2*4.0f)/6.0f));
        bezierPoints.push_back(vec4((pos1 + pos2*4.0f + pos3)/6.0f));
    }
    return bezierPoints;
}


vec4 InterBSpline::computeBSpline(
                    const vector<float>& knotVector,
                    float t, int n){
    float x,y,z;
    x = y = z = 0;
    for(unsigned int i = 0; i < deBoorPoints.size(); i++){
        float bsplineBasisValue = bsplineRecurive(t, n, i, knotVector);

        const vec4& pos = deBoorPoints[i]->localTransPointCoordinates;
        x += pos.x * bsplineBasisValue;
        y += pos.y * bsplineBasisValue;
        z += pos.z * bsplineBasisValue;
    }
    return vec4(x,y,z,1);
}

float InterBSpline::bsplineRecurive(float t, int n, int i,
                      const vector<float>& knotVector){
    if (n == 0){
        if(t >= knotVector[i] && t < knotVector[i+1])
            return 1;
        else
            return 0;
    }
    float leftRecursion = (t - knotVector[i]);
    float leftDenominator = (knotVector[i+n] - knotVector[i]);
    if(leftRecursion == 0 || leftDenominator == 0)
        leftRecursion = 1;
    else
        leftRecursion /= leftDenominator;

    float rightRecursion = knotVector[i+1+n] - t;
    float rightDenominator = (knotVector[i+1+n] - knotVector[i+1]);
    if(rightRecursion == 0 || rightDenominator == 0)
        rightRecursion = 1;
    else
        rightRecursion /= rightDenominator;

    leftRecursion *= bsplineRecurive(t, n-1, i, knotVector);
    rightRecursion *= bsplineRecurive(t, n-1, i+1, knotVector);

    return leftRecursion + rightRecursion;
}
