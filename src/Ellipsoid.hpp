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

class Ellipsoid{
  
public:
    
    Vector3D center;
    Vector3D semiAxis;
    Vector3D color;
    
    
    Ellipsoid(Vector3D center ,Vector3D semiAxis, Vector3D color): center(center), semiAxis(semiAxis), color(color){}
    
    float detectEllipsoid(Vector3D O, Vector3D D, Vector3D C, Vector3D semiAxis);
    
};
