//
//  Sphere.cpp
//  firstSphere
//
//  Created by Julio Torres on 03/12/24.
//

#include "Sphere.hpp"
#include "Vector3D.h"

Vector3D Sphere::detectSphere(Vector3D viewportPosition, Sphere sphere, Ray ray){
    
    Vector3D OC = viewportPosition.subtract(sphere.center);
    
    float a = ray.direction.dot(ray.direction);
    float b = ray.direction.scale(2.0f).dot(OC);
    float c = OC.dot(OC) - (pow(sphere.radius,2));
    float sphereDeterminant = b * b - 4*a*c;
    
    if (sphereDeterminant>0){
            
            // Solve t for the closest point
            float sqrtDiscriminant = sqrt(sphereDeterminant);
            float t0 = (-b - sqrtDiscriminant) / (2 * a);
            float t1 = (-b + sqrtDiscriminant) / (2 * a);
            float tHit;
            if (t0>0) {tHit = t0;}
            else if (t1>0) {tHit = t1;}

            Vector3D hitPoint = ray.origin.add(ray.direction.scale(tHit));
                
            return sphere.color;
            
        }
    
    return Vector3D(0,0,0);
}
