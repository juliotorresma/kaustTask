#include "Vector3D.h"

// Constructor por defecto
Vector3D::Vector3D() {
    x = 0;
    y = 0;
    z = 0;
}

// Constructor con parámetros
Vector3D::Vector3D(float xVal, float yVal, float zVal) {
    x = xVal;
    y = yVal;
    z = zVal;
}

// Sumar dos vectores
Vector3D Vector3D::add(const Vector3D& v) {
    return Vector3D(x + v.x, y + v.y, z + v.z);
}

// Restar dos vectores
Vector3D Vector3D::subtract(const Vector3D& v) {
    return Vector3D(x - v.x, y - v.y, z - v.z);
}

// Producto punto
float Vector3D::dot(const Vector3D& v) {
    return x * v.x + y * v.y + z * v.z;
}

// Escalar un vector
Vector3D Vector3D::scale(float scalar) {
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

// Magnitud del vector
float Vector3D::magnitude() {
    return sqrt(x * x + y * y + z * z);
}

// Normalizar el vector
Vector3D Vector3D::normalize() {
    float mag = magnitude();
    return Vector3D(x / mag, y / mag, z / mag);
}
