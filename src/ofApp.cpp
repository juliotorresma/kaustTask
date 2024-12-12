#include "ofApp.h"
#include "Ray.hpp"
#include "Vector3D.h"
#include "Ellipsoid.hpp"
#include "Sphere.hpp"
#include "Cone.hpp"
#include "SceneObject.hpp"
#include "Light.hpp"
#include "Plane.hpp"
#include <vector>
#include <chrono>
#include <memory>

using std::make_shared;
using std::shared_ptr;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;


Light light(Vector3D(-2,4,-2), Vector3D(1,1,1), 1.5f, Vector3D(1,1,1));

// Define the viewport postion
Vector3D viewingPosition(0,0,1.5f);
bool parallelProjection = false;


vector<std::unique_ptr<SceneObject>> sceneObjects;

Vector3D phongShading(float lightAngle, Vector3D& closestColor, Vector3D& Ldir, Light& light, Vector3D& viewPosition, Vector3D& closestHitPoint, Vector3D& closestNormal){
    
    // Vector V is the one that begins at hitpoint and direction to the viewpoint
    Vector3D V = viewPosition.subtract(closestHitPoint).normalize();
    
    // Vector H is the sum of V and light direction, we will use it later to calculate the angle between the normal.
    Vector3D H = (Ldir.add(V)).normalize();
    
    // Checking the specular factor, if it is big the specular is going to be small
    float specFactor = std::pow(std::max(0.0f, closestNormal.dot(H)), light.phongExponent);
    
    // final formula to calculate the phong shading
    Vector3D specular = Vector3D (light.diffuseReflectanceColor.x * light.lightIntensity.x * specFactor,
                                  light.diffuseReflectanceColor.y * light.lightIntensity.y * specFactor,
                                  light.diffuseReflectanceColor.z * light.lightIntensity.z * specFactor);
    
    return specular;
}

Vector3D lambertianShading(float lightAngle, Vector3D& closestColor, Vector3D& lightIntensity, Vector3D& I_a){
    
    Vector3D lambSColor = Vector3D(lightAngle*closestColor.x *lightIntensity.x * I_a.x,
                                   lightAngle*closestColor.y *lightIntensity.y * I_a.y,
                                   lightAngle*closestColor.z *lightIntensity.z * I_a.z);
    return lambSColor;
}

//--------------------------------------------------------------
void ofApp::setup(){
    
    sceneObjects.push_back(make_unique<Sphere>(Vector3D(0, 0, -5), // central position
                                               Vector3D(1, 0, 0), // color
                                               1.0f)); //radius
    
    sceneObjects.push_back(make_unique<Ellipsoid>(
        Vector3D(-3, 2, -6),          // Centro de la elipse
        Vector3D(2.0f, 1.0f, 1.5f), // Semi-ejes: X=2.0, Y=1.0, Z=1.5
        Vector3D(0, 0, 1)           // Color: Azul
    ));
    
    sceneObjects.push_back(make_unique<Cone>(
        Vector3D(3, 1, -4), // Posicion de peek
        Vector3D(0, -1, 0), // Vector de dirección del peek
        Vector3D(0, 1, 0), // Color
        ofDegToRad(30), // Apertura
        2.0f)); // Altura

    sceneObjects.push_back(make_unique<Plane>
                           (Vector3D(0,1,0), // normalVector
                            Vector3D(0,-1.6f,0), // knownPointAtSpace
                            Vector3D(0.5f,0.5f,0.5f))); // planeColor
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    auto t1 = high_resolution_clock::now();
    
    int width = ofGetWidth();
    int height = ofGetHeight();
    // Nested for to iterate through every pixel
    for(int x=0; x<width; x++){
        for(int y=0; y<height; y++){
           
            float aspectRatio = 640.0f / 480.0f;
            float scale = 3.0f;
            // Getting the center coordinate of every pixel
            float u = (x - width / 2.0f) / (width / 2.0f) * aspectRatio * scale; // Ajusta el ancho
            float v = (y - height / 2.0f) / (height / 2.0f) * scale;
            
            // Define the direction
            Vector3D canvasPosition(u,-v,-1);
            Vector3D rayDirection = Vector3D(u,-v,-1);
            //Vector3D rayDirection = canvasPosition.subtract(viewingPosition).normalize();
            Ray ray(viewingPosition, rayDirection);
            
            if (parallelProjection) {
                ray.origin = Vector3D(u,-v,0);
                ray.direction = Vector3D(0,0,-1);
            }else{ // Perspective
                ray.origin = viewingPosition;
                ray.direction = canvasPosition.subtract(viewingPosition).normalize();
            }
            float closestT = std::numeric_limits<float>::infinity(); //
            
            Vector3D closestColor(0, 0, 0); // Variable to store closest figure color detected
            Vector3D closestNormal(0, 0, 0);// Variable to store closest figure normal detected
            // Iterate though every SceneObject to check witch one is the closest
            for (const auto& obj : sceneObjects){
                
                float t;
                Vector3D hitColor;
                Vector3D normalTHit;
                // Calling virtual boolean function of a SceneObject
                if (obj->intersect(ray, t, hitColor, normalTHit)) {
                    if (t<closestT){
                        closestT = t;
                        closestColor = hitColor;
                        closestNormal = normalTHit; // Updating closest hitpoint info
                    }
                }
            }
            
            // Ray equation solved
            Vector3D hitPoint = ray.origin.add(ray.direction.scale(closestT));
            // Vector poiting to the light
            Vector3D Ldir = light.lightPosition.subtract(hitPoint).normalize();
            
                    Ray shadowRay(hitPoint.add(Ldir.scale(1e-3f)), Ldir);
                    bool inShadow = false;
                    for (const auto& obj : sceneObjects) {
                        float t2 = 0;
                        Vector3D hitColor2, normalTHit2;
                        if (obj->intersect(shadowRay, t2, hitColor2, normalTHit2)) {
                            Vector3D shadowHitPoint = shadowRay.origin.add(shadowRay.direction.scale(t2));
                            // Calculate the closest shawray collision with another object
                            float distanceToLight = light.lightPosition.subtract(shadowHitPoint).magnitude();
                            if (t2 < distanceToLight) {
                                inShadow = true;
                                break;
                            }
                        }
                    }

                    // If the object is blocking light rays, draw a shadow with ambient light
                    if (inShadow) {
                        Vector3D finalColor2 = closestColor.scale(0.1f);
                        ofSetColor(finalColor2.x*255, finalColor2.y*255, finalColor2.z*255);
                        ofDrawRectangle(x, y, 1, 1);
                        
                    }
                    else{
                        // Calulate angle between light direction and figure normal
                        float lightAngle = std::max(0.0f,closestNormal.dot(Ldir));
                        
                        if (lightAngle>0){
                            
                            // Lambertian Shading
                            Vector3D lambColor = lambertianShading(lightAngle,
                                                                   closestColor,
                                                                   light.lightIntensity,
                                                                   light.I_a);
                            //Phong shading
                            Vector3D phongSpecular = phongShading(lightAngle, closestColor,
                                                  Ldir, light,
                                                  ray.origin, hitPoint, closestNormal);
                           //Final color
                            Vector3D finalColor =lambColor.add(phongSpecular.add(closestColor.scale(0.1f)));
                            ofSetColor(finalColor.x * 255, finalColor.y * 255, finalColor.z * 255);
                            ofDrawRectangle(x, y, 1, 1); // Dibujar píxel
                        }
                        else{
                            // if the ray doesnt collide with anything, draw darkness
                            ofSetColor(0, 0, 0);
                            ofDrawRectangle(x, y, 1, 1); // Dibujar píxel
                        }
                    }
        }
    }
    auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;
    
    printf("CPU: 8-core ARM-based design (4 performance cores + 4 efficiency cores) took %f ms\n", ms_double.count());
}
//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
        //left
       if (key == 57356){
           
           parallelProjection = false;
           cout<<"Perspective Activated"<<endl;
           
           
       }//right
       if (key == 57358){
           
           parallelProjection = true;
           cout<<"Parallel Activated"<<endl;
           
       }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
