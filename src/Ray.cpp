//
//  Ray.cpp
//  firstSphere
//
//  Created by Julio Torres on 03/12/24.
//

#include "Ray.hpp"
#include "Vector3D.h"

// Default construct
Ray::Ray() : origin(Vector3D()), direction(Vector3D(0,0,1)){}

// Construct with parameters
Ray::Ray(Vector3D origin, Vector3D direction): origin(origin), direction(direction){}

//Select a t for the vector Ray alog t
Vector3D Ray::pointAt(float t){
    return origin.add(direction.scale(t));
}

