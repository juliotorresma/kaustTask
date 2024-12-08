//
//  Ellipsoid.cpp
//  firstSphere
//
//  Created by Julio Torres on 05/12/24.
//

#include "Ellipsoid.hpp"
#include <iostream>
using namespace std;

Vector3D Ellipsoid::findNormal(Vector3D pointInT, Vector3D semiaxis, Vector3D center){
    
    Vector3D normal =  Vector3D((pointInT.x - center.x)/(semiAxis.x),
                                (pointInT.y - center.y)/(semiAxis.y),
                                (pointInT.z - center.z)/(semiAxis.z));
    return normal.normalize();
}
