//
//  Ellipsoid.cpp
//  firstSphere
//
//  Created by Julio Torres on 05/12/24.
//

#include "Ellipsoid.hpp"
#include "Vector3D.h"
#include <cmath>
#include <iostream>
using namespace std;

Vector3D Ellipsoid::findNormal(Vector3D pointInT, Ellipsoid ellip ,float a, float b, float c){
    
    Vector3D normal =  Vector3D((pointInT.x - ellip.center.x) / (a * a),
                                (pointInT.y - ellip.center.y) / (b * b),
                                (pointInT.z - ellip.center.z) / (c * c));
    return normal;
}

Vector3D Ellipsoid::detectEllipsoid(Vector3D O, Ellipsoid ellip, Ray ray){
    /*
     x^2/a^2 + y^2/b^2 + z^2/c^2 = 1
     
     Ray equation applied:
     
     (Ox + tDx)^2/a^2 + (Oy + tDy)^2/b^2 + (Oz + tDz)^2/z^2 = 1
     Ox^2/a^2 + 2OxtDx/a^2 + t^2Dx^2/a^2 + Oy2/b^2 + 2OytDy/b^2 + t^2Dy^2/b^2 + Oz^2/c^2 + 2OztDz/c^2 + t^2Dz^2/c^2 = 1
     Cuadratic equation: At^2 + Bt + C = 0
     Group terms:
     
     A: Dx^2/a^2 + Dy2/b^2 + Dz^2/c^2
     B: 2(OxDx/a^2 + OyDy/b^2 + OzDz/c^2)
     C: Ox^2/a^2 + Oy2/b^2 + Oz^2/c^2 - 1
     */
    Vector3D oc = O.subtract(ellip.center);
    
    float a =   pow(ray.direction.x,2)/pow(semiAxis.x,2) +
                pow(ray.direction.y,2)/pow(semiAxis.y,2) +
                pow(ray.direction.z,2)/pow(semiAxis.z,2);
    
    float b = 2*((oc.x * ray.direction.x)/pow(semiAxis.x,2) +
                 (oc.y * ray.direction.y)/pow(semiAxis.y,2) +
                 (oc.z * ray.direction.z)/pow(semiAxis.z,2));
    
    float c =   (pow(oc.x,2)/pow(semiAxis.x,2)) +
                (pow(oc.y,2)/pow(semiAxis.y,2)) +
                (pow(oc.z,2)/pow(semiAxis.z,2))-1;
    
    float discriminant = b*b - 4*a*c;
    
    
    if (discriminant>0){
        // Solve t for the closest point
        float sqrtDiscriminant = sqrt(discriminant);
        float t0 = (-b - sqrtDiscriminant) / (2 * a);
        float t1 = (-b + sqrtDiscriminant) / (2 * a);
        float tHit;
        if (t0>0) {tHit = t0;}
        else if (t1>0) {tHit = t1;}
        Vector3D hitPoint = ray.origin.add(ray.direction.scale(tHit));
        
        Vector3D ellipsoidNormal= ellip.findNormal(hitPoint, ellip, a, b, c);
        
        return ellip.color;
    }
    return Vector3D(0,0,0);
}

