//
//  Light.hpp
//  firstSphere
//
//  Created by Julio Torres on 06/12/24.
//

#ifndef Light_hpp
#define Light_hpp

#include <stdio.h>
#include "Vector3D.h"

#endif /* Light_hpp */


class Light{
public:
    
    Vector3D lightPosition;
    Vector3D lightIntensity;
    Vector3D diffuseReflectanceColor;
    float fractionOfLight;
    Vector3D I_a = lightIntensity.scale(fractionOfLight);
    
    Light(Vector3D lightPosition,
          Vector3D lightIntensity,
          float fractionOfLight):
    
            lightPosition(lightPosition),
            lightIntensity(lightIntensity),
            fractionOfLight(fractionOfLight){}
    
};
