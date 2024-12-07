//
//  Ray.cpp
//  firstSphere
//
//  Created by Julio Torres on 03/12/24.
//

#include "Ray.hpp"


//Select a t for the vector Ray alog t
Vector3D Ray::pointAt(float t){
    return origin.add(direction.scale(t));
}

