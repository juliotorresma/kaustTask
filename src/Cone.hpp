//
//  Cone.hpp
//  firstSphere
//
//  Created by Julio Torres on 04/12/24.
//

#ifndef Cone_hpp
#define Cone_hpp

#include <stdio.h>
#include "Vector3D.h"
#endif /* Cone_hpp */

class Cone{
public:
    Vector3D vortex; // The peek of the cone
    Vector3D centralAxis; // Axis where the cone is going to spin around, it has to be normalized so it simplifies the calculations
    
    float angleOfAxis; // Angle of spinning
    
    Cone(Vector3D vortex, Vector3D centralAxis, float angleOfAxis): vortex(vortex), centralAxis(centralAxis.normalize()), angleOfAxis(angleOfAxis){}
    
    
    
};
