//
//  Sphere.hpp
//  firstSphere
//
//  Created by Julio Torres on 03/12/24.
//
#ifndef Sphere_hpp
#define Sphere_hpp
#include <stdio.h>
#include <iostream>
#include "Vector3D.h"
#include "Light.hpp"
#include "SceneObject.hpp"
#include "Ray.hpp"
#endif /* Sphere_hpp */

using namespace std;
class Sphere: public SceneObject{
public:
    
    Vector3D center;
    Vector3D sphereColor;
    
    float radius;
    
    
    Sphere(const Vector3D center,
           const Vector3D sphereColor,
           float radius):
    center(center), sphereColor(sphereColor), radius(radius){}
    
    
    
    Vector3D findNormal(Vector3D pointInT, Vector3D center) const;
    Vector3D shading(Ray ray, Light light, Vector3D normal, Vector3D hitPoint);
    
    virtual bool intersect(Ray ray, float& t, Vector3D& color){
        
        Vector3D OC = ray.origin.subtract(center);
        color = sphereColor;
        float a = ray.direction.dot(ray.direction);
        float b = ray.direction.scale(2.0f).dot(OC);
        float c = OC.dot(OC) - (pow(radius,2));
        
        float sphereDeterminant = b * b - 4*a*c;
    
        if (sphereDeterminant>0){
            
            // Solve t for the closest point
            float sqrtDiscriminant = sqrt(sphereDeterminant);
            float t0 = (-b - sqrtDiscriminant) / (2.0f * a);
            float t1 = (-b + sqrtDiscriminant) / (2.0f * a);
            float tHit;
            if (t0 > 0) { tHit = t0; }
            else if (t1 > 0) { tHit = t1; }
            else return false;
            
            //Vector3D hitPoint = ray.origin.add(ray.direction.scale(tHit));
            
            //Vector3D sphereNormal= findNormal(hitPoint, center);
            color = sphereColor;
            t = tHit;
            // Shading process
            
            return true;
            
        }
        
        return false;
    }
    
    
};

