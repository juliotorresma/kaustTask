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

float Ellipsoid::detectEllipsoid(Vector3D O, Vector3D D, Vector3D C ,Vector3D semiAxis){
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
    Vector3D oc = O.subtract(C);
    float a = (D.x * D.x) / (semiAxis.x * semiAxis.x) +
              (D.y * D.y) / (semiAxis.y * semiAxis.y) +
              (D.z * D.z) / (semiAxis.z * semiAxis.z);

    float b = 2 * ((oc.x * D.x) / (semiAxis.x * semiAxis.x) +
                   (oc.y * D.y) / (semiAxis.y * semiAxis.y) +
                   (oc.z * D.z) / (semiAxis.z * semiAxis.z));

    float c = (oc.x * oc.x) / (semiAxis.x * semiAxis.x) +
              (oc.y * oc.y) / (semiAxis.y * semiAxis.y) +
              (oc.z * oc.z) / (semiAxis.z * semiAxis.z) - 1;
    
    float discriminant = b*b - 4*a*c;

    
    if (discriminant>0){
        // Solve t for the closest point
        float sqrtDiscriminant = sqrt(discriminant);
        float t0 = (-b - sqrtDiscriminant) / (2 * a);
        float t1 = (-b + sqrtDiscriminant) / (2 * a);
        if (t0>0) {return t0;}
        else if (t1>0) return t1;
    }
    
    
    return 0;
    
}

