//
//  Sphere.cpp
//  firstSphere
//
//  Created by Julio Torres on 03/12/24.
//

#include "Sphere.hpp"
#include "Vector3D.h"

float Sphere::detectSphere(Vector3D viewportPosition, Vector3D rayDirection, Sphere sphere){
    
    Vector3D OC = viewportPosition.subtract(sphere.center);
    
    float a = rayDirection.dot(rayDirection);
    float b = rayDirection.scale(2.0f).dot(OC);
    float c = OC.dot(OC) - (pow(sphere.radius,2));
    float sphereDeterminant = b * b - 4*a*c;

    if (sphereDeterminant>0){
        float t = (-b - sqrt(sphereDeterminant)) / (2.0f * a);
        return t;
    }
    else return 0;
}
