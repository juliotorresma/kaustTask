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
#include "SceneObject.hpp"
#endif /* Cone_hpp */

class Cone: public SceneObject{
public:
    Vector3D vortex; // The peek of the cone
    Vector3D centralAxis; // Axis where the cone is going to spin around, it has to be normalized so it simplifies the calculations
    Vector3D coneColor;
    float height;
    float angleOfAxis; // Angle of spinning
    
    Cone(const Vector3D vortex,
         Vector3D centralAxis,
         const Vector3D coneColor,
         float angleOfAxis,
         float height): vortex(vortex), centralAxis(centralAxis.normalize()), coneColor(coneColor), angleOfAxis(angleOfAxis), height(height){}
    
    virtual bool intersect(Ray ray, float& t, Vector3D& color, Vector3D& normalTHit){
        /*
         
         Cone equation: ((P−V)⋅C)^2−((P−V)⋅(P−V))⋅cos^2(θ)=0
         Cone solved equation (Operations in PDF notes):(L⋅C)^2+2⋅t⋅(L⋅C)⋅(D⋅C)+t^2⋅(D⋅C)^2−((L⋅L)+2⋅t⋅(L⋅D)+t^2⋅(D⋅D))⋅cos^2(θ)=0
            - Where L = viewportPosition-vortexPosition
         
         Thus we can assume:
             a = (D · C)^2 − (D · D) * cos^2(θ)
             b = 2 * ((L · C) * (D · C) − (L · D) * cos^2(θ))
             c = (L · C)^2 − (L · L) * cos^2(θ)
         */
        float cos2 = cos(angleOfAxis) * cos(angleOfAxis);
        Vector3D O = ray.origin;
        Vector3D C = centralAxis;
        Vector3D V = vortex;
        Vector3D D = ray.direction;
        Vector3D L = O.subtract(V);

        float a = (D.dot(C) * D.dot(C)) - (D.dot(D) * cos2);
        float b = 2 * ((L.dot(C) * D.dot(C)) - (L.dot(D) * cos2));
        float c = (L.dot(C) * L.dot(C)) - (L.dot(L) * cos2);

        float coneDiscriminant = b*b - 4*a*c;
        float tHit;
        if (coneDiscriminant > 0) {
             // Solve t for the closest point
             float sqrtDiscriminant = sqrt(coneDiscriminant);
             float t0 = (-b - sqrtDiscriminant) / (2 * a);
             float t1 = (-b + sqrtDiscriminant) / (2 * a);
             
             if (t1 > 0) {
                 tHit = t1;
             }else if (t0 > 0) {
                 tHit = t0;
             }else return false;
             // Calculate the point of intersection
             Vector3D hitPoint = ray.origin.add(ray.direction.scale(tHit));
             Vector3D vectorToIntersection = hitPoint.subtract(vortex);

             // Project the vector onto the cone's central axis
             float heightAtIntersection = vectorToIntersection.dot(centralAxis);

             // Check if the intersection is within the cone's height range
             if (heightAtIntersection >= 0 && heightAtIntersection <= height) {
                 t = tHit;
                 color = coneColor;
                 normalTHit = findNormal(hitPoint, vortex);
                 if (normalTHit.dot(ray.direction) > 0) {
                     // Si la normal apunta en la misma dirección que el rayo, inviértela
                     normalTHit = normalTHit.scale(-1);
                     //normalTHit.z = -normalTHit.z;
                 }
                 return true;
             }
            
         }
        // Intersección con la base del cono
            Vector3D baseCenter = vortex.add(C.scale(height));
            float denom = D.dot(C); // Producto punto con la normal del plano de la base
            
                float tBase = (baseCenter.subtract(O)).dot(C) / denom;
                if (tBase > 0) { // Verificar si está más cerca que la superficie
                    Vector3D hitPoint = ray.origin.add(ray.direction.scale(tBase));
                    
                    if (hitPoint.subtract(baseCenter).magnitude() <= height * tan(angleOfAxis)) { // Dentro del radio
                        t = tBase;
                        color = coneColor;
                        //normalTHit = C.scale(-1); // La normal en la base apunta hacia abajo
                        return true;
                    }
            }
        return false;
    }

    Vector3D findNormal(Vector3D point, Vector3D apex) {
        
        Vector3D v = point.subtract(apex);

            // Proyección de v sobre el eje del cono (centralAxis ya está normalizado)
            float projectionLength = v.dot(centralAxis);
            Vector3D projection = centralAxis.scale(projectionLength);

            // Verificar si el punto está en la base
            if (projectionLength > height) {
                return centralAxis; // Normal de la base (apunta hacia arriba)
            }

            // Vector radial: Componente de v perpendicular al eje del cono
            Vector3D radial = v.subtract(projection);

            // La normal combina el radial y el ajuste por la pendiente
            float slope = tan(angleOfAxis); // Pendiente de la superficie
            Vector3D normal = radial.subtract(centralAxis.scale(slope * radial.magnitude()));
            
            // Normalizar el vector antes de devolverlo
            return normal.normalize();
    }
};
