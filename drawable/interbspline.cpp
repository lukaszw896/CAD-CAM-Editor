#include "interbspline.h"
#include "Math/bandiag.h"

InterBSpline::InterBSpline()
{

}

InterBSpline::InterBSpline(Camera *camera)
{
    this->camera = camera;
    drawPolygon = false;
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

//computing parameteres based on length of arcs of curve
void InterBSpline::computeChordParameters(){
    int n = deBoorPoints.size();
    parameters.resize(n);

    interpolatingPolygonLength = 0;
    for(int i = 1; i < n ; i++){
        float dist = euclideanDistance(deBoorPoints[i]->localTransPointCoordinates,deBoorPoints[i-1]->localTransPointCoordinates);
        interpolatingPolygonLength += dist;
    }
    parameters[0] = 0;
    float sumOfDistances = 0;
    for(int i = 1; i < n -1; i++){
        sumOfDistances += euclideanDistance(deBoorPoints[i]->localTransPointCoordinates,deBoorPoints[i-1]->localTransPointCoordinates);
        parameters[i] = sumOfDistances / interpolatingPolygonLength;
    }
    parameters[n-1] = 1.0f;
}

void InterBSpline::computeKnotVector(){
    int n = deBoorPoints.size();
    int knotVectorCount = n + 3 + 1;

    knotVector.resize(knotVectorCount);
    for(int i = 0; i <= 3; i++){
        knotVector[i] = 0;
    }
    int j;

    for(j = 1; j < n-3; j++){
        float sum = 0;
        for(int i = j; i < j + 3; i++){
            sum += parameters[i];
        }
        knotVector[j+ 3] = sum / 3;
    }

    for(int i = j+3; i < knotVectorCount; i++){
        knotVector[i] = 1.0f;
    }
}

vec4 InterBSpline::computeBSpline(
                    const vector<float>& knotVector,
                    float t, int n){
    float x,y,z;
    x = y = z = 0;
    for(int i = 0; i < controlPoints.size(); i++){
        float bsplineBasisValue = bsplineRecurive(t, n, i, knotVector);

        x += controlPoints[i].x * bsplineBasisValue;
        y += controlPoints[i].y * bsplineBasisValue;
        z += controlPoints[i].z * bsplineBasisValue;
    }
    return vec4(x,y,z,1);
}

float InterBSpline::euclideanDistance(vec4& point1, vec4& point2)
{
    return sqrt(pow(point1.x-point2.x,2)+pow(point1.y-point2.y,2)+pow(point1.z-point2.z,2));
}

float InterBSpline::bsplineRecurive(float t, int n, int i, const vector<float>& knotVector){
    if (n == 0){
        if(t >= knotVector[i] && t < knotVector[i+1]) return 1;
        else return 0;
    }
    float leftRecursion = (t - knotVector[i]);
    float leftDenominator = (knotVector[i+n] - knotVector[i]);
    if(leftRecursion == 0 || leftDenominator == 0)
        leftRecursion = 0;
    else
        leftRecursion /= leftDenominator;

    float rightRecursion = knotVector[i+1+n] - t;
    float rightDenominator = (knotVector[i+1+n] - knotVector[i+1]);
    if(rightRecursion == 0 || rightDenominator == 0)
        rightRecursion = 0;
    else
        rightRecursion /= rightDenominator;

    leftRecursion *= bsplineRecurive(t, n-1, i, knotVector);
    rightRecursion *= bsplineRecurive(t, n-1, i+1, knotVector);

    return leftRecursion + rightRecursion;
}

void InterBSpline::computeControlPoints()
{
    int n = deBoorPoints.size();

       const int SUB_DIAG_COUNT = 2;
       const int SUPER_DIAG_COUNT = 2;
       const int DIAG_COUNT = 5;

       float** bandMatrix = (float**)malloc(sizeof(float*) * (n+1));
       float** lowerMatrix = (float**)malloc(sizeof(float*) * (n+1));
       for(int i = 1; i < n+1;i++){
           bandMatrix[i] = (float*)malloc(sizeof(float) * (DIAG_COUNT+1));
           lowerMatrix[i] = (float*)malloc(sizeof(float) * (SUB_DIAG_COUNT+1));
       }
       unsigned long* index = (unsigned long*)malloc(sizeof(unsigned long) * (n+1));


       // ---------------------------------------
       bandMatrix[1][1] = 0;
       bandMatrix[2][1] = 0;
       for(int i = 3; i < n+1; i++){
           bandMatrix[i][1] = bsplineRecurive(parameters[i-1], 3, i-3,knotVector);
       }

       bandMatrix[1][2] = 0;
       for(int i = 2; i < n+1; i++){
           bandMatrix[i][2] = bsplineRecurive(parameters[i-1], 3, i - 2,knotVector);
       }

       for(int i = 1; i < n+1; i++){
           bandMatrix[i][3] = bsplineRecurive(parameters[i-1], 3, i-1,knotVector);
       }

       for(int i = 1; i < n; i++){
           bandMatrix[i][4] = bsplineRecurive(parameters[i-1], 3, i,knotVector);
       }
       for(int i = 1; i < n-1; i++){
           bandMatrix[i][5] = bsplineRecurive(parameters[i-1], 3, i+1,knotVector);
       }
       bandMatrix[n][3] = 1;
       bandMatrix[n][4] = 0;
       bandMatrix[n][5] = 0;
       bandMatrix[n-1][5] = 0;

       float evenOdd = 0;
       bandec(bandMatrix, n, SUB_DIAG_COUNT, SUPER_DIAG_COUNT, lowerMatrix,
              index, &evenOdd);

       controlPoints.clear();
       controlPoints.resize(n);
       for(int s = 0; s < 3; s++){
           float* d = (float*)malloc(sizeof(float) * (n+1));

           for(int i = 1; i < n+1; i++){
               d[i] = deBoorPoints[i-1]->localTransPointCoordinates[s];
           }

           banbks(bandMatrix, n , SUB_DIAG_COUNT, SUPER_DIAG_COUNT, lowerMatrix, index, d);

           for(int i = 1; i < n+1; i++){
               controlPoints[i-1][s] = d[i];
           }
           delete d;
       }
       for(int i = 1; i < n+1; i++){
           delete bandMatrix[i];
           delete lowerMatrix[i];
       }
       delete index;
       delete bandMatrix;
       delete lowerMatrix;
}

void InterBSpline::draw()
{
    int n = deBoorPoints.size();
    if(drawPolygon || n==2){
        glPointSize(1);
        glBegin(GL_LINES);
        glColor4f(1,1.0, 1.0,1.0);
        if(!(deBoorPoints.size()<2)){
            if(!camera->isStereoscopic){
            for(int i=0;i<deBoorPoints.size()-1;i++){
                glVertex2f(deBoorPoints[i]->transPointCoordinates.x,deBoorPoints[i]->transPointCoordinates.y);
                glVertex2f(deBoorPoints[i+1]->transPointCoordinates.x,deBoorPoints[i+1]->transPointCoordinates.y);
            }
            }
            else{
                for(int i=0;i<deBoorPoints.size()-1;i++){
                    glColor3f(0.4,0.0, 0.0);
                    glVertex2f(deBoorPoints[i]->leftEyeTransPointCoordinate.x,deBoorPoints[i]->leftEyeTransPointCoordinate.y);
                    glVertex2f(deBoorPoints[i+1]->leftEyeTransPointCoordinate.x,deBoorPoints[i+1]->leftEyeTransPointCoordinate.y);

                     glColor3f(0, 0.5, 0.5);
                    glVertex2f(deBoorPoints[i]->rightEyeTransPointCoordinate.x,deBoorPoints[i]->rightEyeTransPointCoordinate.y);
                    glVertex2f(deBoorPoints[i+1]->rightEyeTransPointCoordinate.x,deBoorPoints[i+1]->rightEyeTransPointCoordinate.y);
                }
            }
        }
        glEnd();
    }

    if(n<3) return;

    if(n>2){
        if(n==3)
        {
            Point* p = deBoorPoints[0];
            deBoorPoints.insert(deBoorPoints.begin(),p);
        }

        computeChordParameters();
        computeKnotVector();

        computeControlPoints();

        int degree = deBoorPoints.size() -1;
        if(degree>3)degree = 3;
        else if(degree<0) return;

        float pixNum =0;
        if(camera->screenWidth > camera->screenHeight){
            pixNum = camera->screenHeight;
        }
        else{
            pixNum = camera->screenWidth;
        }
        //TMP
        float dt = 1.0f/pixNum / interpolatingPolygonLength;

        float t = knotVector[2];
        //dt /= 5*t_max;

        glPointSize(1.0f);
        glColor4f(1,1.0, 1.0,1.0);
        glBegin(GL_POINTS);
        while(t < knotVector[knotVector.size()-2]){
            vec4 point = computeBSpline(knotVector, t, degree);
            t += dt;

            if(!camera->isStereoscopic){
                point = camera->transformationMatrix * point;
                point.x /= point.w;
                point.y /= point.w;
                point.x /= camera->xRatio;
                point.y /= camera->yRatio;

                if(!(point.w >=-0.06)) // clip
                    glVertex2f(point.x, point.y);
            }
            else{
                vec4 point2 = vec4(point);
                glColor3f(0.4,0.0, 0.0);
                point = camera->transformationMatrixLeftEye * point;
                point.x /= point.w;
                point.y /= point.w;
                point.x /= camera->xRatio;
                point.y /= camera->yRatio;

                if(!(point.w >=-0.06)) // clip
                    glVertex2f(point.x, point.y);

                glColor3f(0, 0.5, 0.5);
                point2 = camera->transformationMatrixRightEye * point2;
                point2.x /= point2.w;
                point2.y /= point2.w;
                point2.x /= camera->xRatio;
                point2.y /= camera->yRatio;

                if(!(point.w >=-0.06)) // clip
                    glVertex2f(point2.x, point2.y);
            }
        }

    }
    if(n==3)
        deBoorPoints.erase(deBoorPoints.begin());



    glEnd();
}

