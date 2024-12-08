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
#include "Ray.hpp"
#endif /* Cone_hpp */

class Cone{
public:
    Vector3D vortex; // The peek of the cone
    Vector3D centralAxis; // Axis where the cone is going to spin around, it has to be normalized so it simplifies the calculations
    Vector3D color;
    
    float angleOfAxis; // Angle of spinning
    
    Cone(const Vector3D& vortex,
         Vector3D centralAxis,
         const Vector3D& color,
         float angleOfAxis): vortex(vortex), centralAxis(centralAxis.normalize()), color(color), angleOfAxis(angleOfAxis){}
    
    Vector3D detectCone(Vector3D viewportPosition,
                     Cone cone,
                     Ray ray);
    
    Vector3D findNormal(Vector3D point, Vector3D apex, float angle, float height);
};
