//
//  Sphere.cpp
//  firstSphere
//
//  Created by Julio Torres on 03/12/24.
//
#include "Sphere.hpp"

using namespace std;

Vector3D Sphere::findNormal(Vector3D pointInT, Vector3D center) const
{
    
    Vector3D normal =  Vector3D((pointInT.x - center.x),
                                (pointInT.y - center.y),
                                (pointInT.z - center.z));
    return normal.normalize();
}

