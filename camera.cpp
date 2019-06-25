#include "camera.h"
#include <math.h>
#include "constants.h"

Camera::Camera()
{
   x = 0.0f;
   y = 0.0f;
   z = 0.0f;

   s = -2*PI/4;
   t = 0.0f;
   r = 0.0f;
}

void Camera::findPointOnSphere(float s, float t, float r){
    this->s = s;
    this->t = t;
    this->r = r;
    this->x = r * cos(s) * sin(t);
    this->y = r * cos(t);
    this->z = r * sin(s) * sin(t);
}

void Camera::przesunDoModelu(float xx, float yy, float zz){
    this->x += xx;
    this->y += yy;
    this->z -= zz;
}

