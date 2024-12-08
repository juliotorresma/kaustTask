//
//  Ellipsoid.cpp
//  firstSphere
//
//  Created by Julio Torres on 05/12/24.
//

#include "Ellipsoid.hpp"
#include <iostream>
using namespace std;

Vector3D Ellipsoid::findNormal(Vector3D pointInT, Ellipsoid ellip ,float a, float b, float c){
    
    Vector3D normal =  Vector3D((pointInT.x - ellip.center.x)/(ellip.semiAxis.x),
                                (pointInT.y - ellip.center.y)/(ellip.semiAxis.y),
                                (pointInT.z - ellip.center.z)/(ellip.semiAxis.z));
    return normal.normalize();
}
