//
//  SceneObject.hpp
//  firstSphere
//
//  Created by Julio Torres on 06/12/24.
//

#ifndef SceneObject_hpp
#define SceneObject_hpp

#include <stdio.h>

#endif /* SceneObject_hpp */

#include "Vector3D.h"
#include "Ray.hpp"

class SceneObject{
    
    virtual ~SceneObject() = default;

    // Método virtual para intersección
    virtual bool intersect(const Ray& ray, float& t, Vector3D& color) const = 0;
    
};
