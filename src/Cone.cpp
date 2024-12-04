//
//  Cone.cpp
//  firstSphere
//
//  Created by Julio Torres on 04/12/24.
//

#include "Cone.hpp"
#include <cmath>
#include <iostream>
using namespace std;
float Cone::detectCone(Vector3D viewportPosition,Vector3D rayDirection, Cone cone){
    /*
     
     Cone equation: ((P−V)⋅C)^2−((P−V)⋅(P−V))⋅cos^2(θ)=0
     Cone solved equation (Operations in PDF notes):(L⋅C)^2+2⋅t⋅(L⋅C)⋅(D⋅C)+t^2⋅(D⋅C)^2−((L⋅L)+2⋅t⋅(L⋅D)+t^2⋅(D⋅D))⋅cos^2(θ)=0
        - Where L = viewportPosition-vortexPosition
     
     Thus we can assume:
         a = (D · C)^2 − (D · D) * cos^2(θ)
         b = 2 * ((L · C) * (D · C) − (L · D) * cos^2(θ))
         c = (L · C)^2 − (L · L) * cos^2(θ)
     */
    float cos2 = cos(cone.angleOfAxis) * cos(cone.angleOfAxis);
    Vector3D O = viewportPosition;
    Vector3D C = cone.centralAxis;
    Vector3D V = cone.vortex;
    Vector3D D = rayDirection;
    Vector3D L = O.subtract(V);

    float a = (D.dot(C) * D.dot(C)) - (D.dot(D) * cos2);
    float b = 2 * ((L.dot(C) * D.dot(C)) - (L.dot(D) * cos2));
    float c = (L.dot(C) * L.dot(C)) - (L.dot(L) * cos2);

    float coneDiscriminant = b*b - 4*a*c;
    
    if (coneDiscriminant>0){
        
        // Solve t for the closest point
        float sqrtDiscriminant = sqrt(coneDiscriminant);
        float t0 = (-b - sqrtDiscriminant) / (2 * a);
        float t1 = (-b + sqrtDiscriminant) / (2 * a);
        if (t0>0) {return t0;}
        else if (t1>0) return t1;
    }
    
    return 0;
}
