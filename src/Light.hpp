//
//  Light.hpp
//  firstSphere
//
//  Created by Julio Torres on 06/12/24.
//

#pragma once

#include <stdio.h>
#include "Vector3D.h"

class Light{
public:
    
    Vector3D lightPosition;
    Vector3D lightIntensity;
    Vector3D diffuseReflectanceColor;
    float fractionOfLight;
    float phongExponent = 32;
    Vector3D I_a = lightIntensity.scale(fractionOfLight);
    
    Light(Vector3D lightPosition,
          Vector3D lightIntensity,
          float fractionOfLight,
          Vector3D diffuseReflectanceColor):
            lightPosition(lightPosition),
            lightIntensity(lightIntensity),
            fractionOfLight(fractionOfLight),
            diffuseReflectanceColor(diffuseReflectanceColor){}
    
};
