//
//  Ray.hpp
//  firstSphere
//
//  Created by Julio Torres on 03/12/24.
//

#pragma once
#include <stdio.h>
#include <cmath>
#include "Vector3D.h"

class Ray{
public:
    Vector3D origin;
    Vector3D direction;
    Ray();
    // Constructor functions
    Ray(Vector3D origin, Vector3D direction): origin(origin), direction(direction){}
    
    // Select a t for the vector Ray alog t
    Vector3D pointAt(float t);
};

