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
    
    
    Ellipsoid(Vector3D center, Vector3D semiAxis): center(center), semiAxis(semiAxis){}
    
    float detectEllipsoid(Vector3D O, Vector3D D, Vector3D semiAxis);
    
};
