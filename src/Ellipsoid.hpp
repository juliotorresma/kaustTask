//
//  Ellipsoid.hpp
//  firstSphere
//
//  Created by Julio Torres on 05/12/24.
//

#ifndef Ellipsoid_hpp
#define Ellipsoid_hpp

#include <stdio.h>

#endif /* Ellipsoid_hpp */
#include "Vector3D.h"
#include "Ray.hpp"
class Ellipsoid{
  
public:
    
    Vector3D center;
    Vector3D semiAxis;
    Vector3D color;
    Vector3D normal;
    Vector3D quadraticTerms;
    
    Ellipsoid(Vector3D center ,Vector3D semiAxis, Vector3D color): center(center), semiAxis(semiAxis), color(color){}
    
    Vector3D detectEllipsoid(Vector3D O, Ellipsoid ellip, Ray rayo);
    
    Vector3D findNormal(Vector3D pointInT, Ellipsoid ellip, float a, float b, float c);
    
};
