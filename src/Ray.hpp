//
//  Ray.hpp
//  firstSphere
//
//  Created by Julio Torres on 03/12/24.
//

#ifndef Ray_hpp
#define Ray_hpp
#include "Vector3D.h"

#include <stdio.h>

#endif /* Ray_hpp */
#include <cmath>

class Ray {
public:
    Vector3D origin;
    Vector3D direction;
    
    Ray();
    // Constructor functions
    Ray(Vector3D origin, Vector3D direction);
    
    // Select a t for the vector Ray alog t
    Vector3D pointAt(float t);
};
