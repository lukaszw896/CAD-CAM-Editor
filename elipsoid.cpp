#include "elipsoid.h"

Elipsoid::Elipsoid(){

}

Elipsoid::Elipsoid(float a, float b, float c)
{
    this->a = a;
    this->b = b;
    this->c = c;
    initDiagMat();
}

void Elipsoid::updateRadius(float a, float b, float c)
{
    this->a = a;
    this->b = b;
    this->c = c;
    updateDiagMat();
}

void Elipsoid::initDiagMat()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
           diagMat[i][j] = 0;
        }
    }
    diagMat[3][3] = -1;
    updateDiagMat();
}

void Elipsoid::updateDiagMat()
{
    diagMat[0][0] = a;
    diagMat[1][1] = b;
    diagMat[2][2] = c;
}

void Elipsoid::calcDPMMat(glm::mat4 transMat)
{
    DPMMat = transpose(inverse(transMat)) * diagMat * inverse(transMat);
}

float Elipsoid::intersectCalc(float x, float y, float cameraZ,vec4* color) {

    float a = DPMMat[2][2];
    float b = (x * DPMMat[0][2] + y * DPMMat[1][2] + DPMMat[3][2]) +
              (x * DPMMat[2][0] + y * DPMMat[2][1] + DPMMat[2][3]);
    float c = (x*x * DPMMat[0][0]) + (x*y*DPMMat[0][1]) + (y*DPMMat[0][3]) +
              (y*x*DPMMat[1][0]) + (y*y * DPMMat[1][1]) + (y*DPMMat[1][3]) +
              (x*DPMMat[3][0]) + (y*DPMMat[3][1]) + DPMMat[3][3];

    if(a == 0 || isnan(a))
        return NO_SOLUTION;
    float deltaSquare = (b*b) - (4*a*c);
    float delta;
    if(deltaSquare < 0)
    {
        return NO_SOLUTION;
    }
    else delta = sqrt(deltaSquare);

    float z1 = (-b + delta) / 2*a;
    float z2 = (-b - delta) / 2*a;

    float z;
    if(abs(z1-cameraZ)<abs(z2-cameraZ))
        z=z1;
    else
        z=z2;

    vec3 point = vec3(x,y,z);

   vec3 v = normalize(derivative(point));
   vec3 n = normalize(-point);

   float dot = (v.x * n.x) + (v.y * n.y) + (v.z * n.z);
       if (dot < 0) dot = 0;
       float lightIntensity = pow(dot, 0.5);

       *color = vec4(1.000*lightIntensity, 1.000*lightIntensity, 0.000*lightIntensity,1);
}

glm::vec3 Elipsoid::derivative(glm::vec3 p)
{
    float dx;
        dx = 2*p.x * DPMMat[0][0]
             + p.z * (DPMMat[0][2] + DPMMat[2][0])
             + p.y * (DPMMat[0][1] + DPMMat[1][0])
             + DPMMat[0][3] + DPMMat[3][0];

        float dy;
        dy = 2*p.y * DPMMat[1][1]
             + p.z * (DPMMat[1][2] + DPMMat[2][1])
             + p.x * (DPMMat[0][1] + DPMMat[1][0])
             + DPMMat[1][3] + DPMMat[3][1];

        float dz;
        dz = 2*p.z * DPMMat[2][2]
             + p.x * (DPMMat[0][2] + DPMMat[2][0])
             + p.y * (DPMMat[1][2] + DPMMat[2][1])
             + DPMMat[2][3] + DPMMat[3][2];

      return glm::vec3(dx,dy,dz);
}
