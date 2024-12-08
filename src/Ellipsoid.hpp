//
//  Ellipsoid.hpp
//  firstSphere
//
//  Created by Julio Torres on 05/12/24.
//

#ifndef Ellipsoid_hpp
#define Ellipsoid_hpp

#include <stdio.h>

#endif /* Ellipsoid_hpp */
#include "Vector3D.h"
#include "Ray.hpp"
#include "SceneObject.hpp"

class Ellipsoid: public SceneObject{
  
public:
    
    Vector3D center;
    Vector3D semiAxis;
    Vector3D ellipColor;
    Vector3D normal;
    Vector3D quadraticTerms;
    
    Ellipsoid(Vector3D center ,Vector3D semiAxis, Vector3D ellipColor): center(center), semiAxis(semiAxis), ellipColor(ellipColor){}
    
    virtual bool intersect(Ray ray, float& t, Vector3D& color) {
        
        Vector3D oc = ray.origin.subtract(center);
        
        float a =   pow(ray.direction.x,2)/pow(semiAxis.x,2) +
                    pow(ray.direction.y,2)/pow(semiAxis.y,2) +
                    pow(ray.direction.z,2)/pow(semiAxis.z,2);
        
        float b = 2*((oc.x * ray.direction.x)/pow(semiAxis.x,2) +
                     (oc.y * ray.direction.y)/pow(semiAxis.y,2) +
                     (oc.z * ray.direction.z)/pow(semiAxis.z,2));
        
        float c =   (pow(oc.x,2)/pow(semiAxis.x,2)) +
                    (pow(oc.y,2)/pow(semiAxis.y,2)) +
                    (pow(oc.z,2)/pow(semiAxis.z,2))-1;
        
        float sphereDeterminant = b * b - 4 * a * c;
        
        if (sphereDeterminant > 0) {
            float sqrtDiscriminant = sqrt(sphereDeterminant);
            float t0 = (-b - sqrtDiscriminant) / (2.0f * a);
            float t1 = (-b + sqrtDiscriminant) / (2.0f * a);
            if (t0 > 0) t = t0;
            else if (t1 > 0) t = t1;
            else return false;
            
            color = ellipColor;
            return true;
        }
        
        return false;
    }
    
    Vector3D findNormal(Vector3D pointInT, Ellipsoid ellip, float a, float b, float c);
    
    void changeColor(Ellipsoid ellip);
    
};
