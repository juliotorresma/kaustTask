//
//  Sphere.hpp
//  firstSphere
//
//  Created by Julio Torres on 03/12/24.
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include <stdio.h>
#include "Vector3D.h"
#include "Ray.hpp"

#endif /* Sphere_hpp */

class Sphere{
public:
    Vector3D center;
    Vector3D color;
    
    float radius;
    
    
    Sphere(const Vector3D& center,
           const Vector3D& color,
           float radius):
    center(center), color(color), radius(radius){}
    
    Vector3D detectSphere(Vector3D viewportPosition,
                          Sphere sphere,
                          Ray ray);
    Vector3D findNormal(Vector3D pointInT, float a, float b, float c);
};

