#pragma once
#include <cmath>

// Clase Vector3D
class Vector3D {
public:
    float x, y, z;

    // Constructores
    Vector3D();
    Vector3D(float xVal, float yVal, float zVal);

    // Métodos básicos
    Vector3D add(Vector3D v);
    Vector3D subtract(Vector3D v);
    float dot(Vector3D v);
    Vector3D scale(float scalar);
    float magnitude();
    Vector3D normalize();
};
