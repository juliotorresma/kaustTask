//
//  Sphere.cpp
//  firstSphere
//
//  Created by Julio Torres on 03/12/24.
//

#include "Sphere.hpp"
#include "Vector3D.h"
#include "Light.hpp"

#include <iostream>

using namespace std;

Vector3D Sphere::shading(Ray ray, Light light, Vector3D normal, Vector3D hitPoint){
    
    // Calculate vector to light
    Vector3D Ldir = light.lightPosition.subtract(hitPoint).normalize();
    
    float lightAngle = normal.dot(Ldir);

    if (lightAngle>0){
        
        Vector3D finalColor = Vector3D(lightAngle*light.diffuseReflectanceColor.x * light.I_a.x,
                                       lightAngle*light.diffuseReflectanceColor.y * light.I_a.y,
                                       lightAngle*light.diffuseReflectanceColor.z * light.I_a.z);
        return finalColor;
    }
    return Vector3D(0,0,0);
}

Vector3D Sphere::findNormal(Vector3D pointInT, Vector3D center){
    
    Vector3D normal =  Vector3D((pointInT.x - center.x),
                                (pointInT.y - center.y),
                                (pointInT.z - center.z));
    return normal.normalize();
}

