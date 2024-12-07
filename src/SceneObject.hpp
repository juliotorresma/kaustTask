//
//  SceneObject.hpp
//  firstSphere
//
//  Created by Julio Torres on 06/12/24.
//

#pragma once
#include <stdio.h>
#include "Vector3D.h"
#include "Ray.hpp"
#include <vector>


using std::make_shared;
using std::shared_ptr;

class SceneObject{
public:
    
    virtual ~SceneObject() = default;
    
    std::vector<shared_ptr<SceneObject>> objects;
    
    void add(shared_ptr<SceneObject> object) {
            objects.push_back(object);
        }
    
    // Método virtual para intersección
    virtual bool intersect(Ray ray, float& t, Vector3D& color);
    
    void add(std::vector<SceneObject> sceneObjects);
    
};
