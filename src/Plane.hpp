//
//  Plane.hpp
//  firstSphere
//
//  Created by Julio Torres on 08/12/24.
//

#ifndef Plane_hpp
#define Plane_hpp
#include "Vector3D.h"
#include "SceneObject.hpp"
#include <stdio.h>

#endif /* Plane_hpp */

class Plane: public SceneObject{
public:
    
    Vector3D planeColor;
    Vector3D normalVector;
    Vector3D knownPointAtSpace;
    
    Plane(Vector3D planeColor,
          Vector3D normalVector,
          Vector3D knownPointAtSpace):
    planeColor(planeColor),normalVector(normalVector),knownPointAtSpace(knownPointAtSpace){}
    
    virtual bool intersect(Ray ray, float& t, Vector3D& color, Vector3D& closestNormal){
        
        /*
         Primero tenemos que normalizar el vector normal
         Luego revisar si el rayo no es paralelo al rayo, eso se hace sacando el producto punto entre la normal y el rayo, si ese denominador
         es un numero extremadamente pequeño entonces si es paralelo.
         */
        
        Vector3D normalizedNormal = normalVector.normalize();
        float dotToFindParallel = ray.direction.dot(normalizedNormal);
        
        if(dotToFindParallel<1e-6){
            return false;
        }
        
        
        float tHit = normalizedNormal.dot(knownPointAtSpace.subtract(ray.origin))/dotToFindParallel;
        
        if (tHit < 0) return false;
        else {
            color = planeColor;
            t = tHit;
            closestNormal = normalizedNormal;
            return true;
            
        }
            
    }
    
};


