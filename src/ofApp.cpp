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
#include <memory>

using std::make_shared;
using std::shared_ptr;
// Creating a red sphere with radius of 1, 5 units away
//auto sphere_ptr = make_shared<Sphere>(Vector3D(0, 0, -5), Vector3D(1, 0, 0), 1);

//Cone cone(Vector3D(-2, -2, -5), Vector3D(0, 1, 0), Vector3D(0, 1, 0), ofDegToRad(30));

//Ellipsoid ellip(Vector3D(2, 2, -5), Vector3D(2, 1, 1.5), Vector3D(0, 0, 1));

// lightPosition, lightIntensity, fractionOfLight
Light light(Vector3D(-2,4,-2), Vector3D(1,1,1), 1.5f, Vector3D(1,1,1));

// Define the viewport postion
Vector3D viewingPosition(0,0,0);

vector<std::unique_ptr<SceneObject>> sceneObjects;

Vector3D phongShading(float lightAngle, Vector3D& closestColor, Vector3D& Ldir, Light& light, Vector3D& viewPosition, Vector3D& closestHitPoint, Vector3D& closestNormal){
    
    Vector3D V = viewPosition.subtract(closestHitPoint).normalize();
    
    Vector3D H = (Ldir.add(V)).normalize();
    float specFactor = std::pow(std::max(0.0f, closestNormal.dot(H)), light.phongExponent);
    
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
    
    sceneObjects.push_back(make_unique<Sphere>(Vector3D(0, 0, -5), Vector3D(1, 0, 0), 1.0f));
    
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
    int width = ofGetWidth();
    int height = ofGetHeight();
    for(int x=0; x<width; x++){
        for(int y=0; y<height; y++){
           
            float aspectRatio = 640.0f / 480.0f;

            float u = (x - width / 2.0f) / (width / 2.0f) * aspectRatio; // Ajusta el ancho
            float v = (y - height / 2.0f) / (height / 2.0f);
            
            // Define the direction
            Vector3D canvasPosition(u,-v,-1);
            Vector3D rayDirection = Vector3D(u,-v,-1);
            //Vector3D rayDirection = canvasPosition.subtract(viewingPosition).normalize();
            Ray ray(viewingPosition, rayDirection);
            //Ray ray(Vector3D((x - width / 2.0f) / (width / 2.0f), (y - height / 2.0f) / (height / 2.0f),0), rayDirection);
            float closestT = std::numeric_limits<float>::infinity();
            
            Vector3D closestColor(0, 0, 0);
            Vector3D closestNormal(0, 0, 0);
            
            for (const auto& obj : sceneObjects){
                float t;
                Vector3D hitColor;
                Vector3D normalTHit;
                
                if (obj->intersect(ray, t, hitColor, normalTHit)) {
                    if (t<closestT){
                        closestT = t;
                        closestColor = hitColor;
                        closestNormal = normalTHit;
                    }
                }
            }
            
            Vector3D hitPoint = ray.origin.add(ray.direction.scale(closestT));
            Vector3D Ldir = light.lightPosition.subtract(hitPoint).normalize();
            
                    Ray shadowRay(hitPoint.add(Ldir.scale(1e-3f)), Ldir);
                    bool inShadow = false;
                    for (const auto& obj : sceneObjects) {
                        float t2 = 0;
                        Vector3D hitColor2, normalTHit2;
                        if (obj->intersect(shadowRay, t2, hitColor2, normalTHit2)) {
                            Vector3D shadowHitPoint = shadowRay.origin.add(shadowRay.direction.scale(t2));
                            float distanceToLight = light.lightPosition.subtract(shadowHitPoint).magnitude();
                            if (t2 < distanceToLight) {
                                inShadow = true;
                                break;
                            }
                        }
                    }

                    // Si el punto está en sombra, dibujar el píxel negro
                    if (inShadow) {
                        Vector3D finalColor2 = closestColor.scale(0.1f);
                        ofSetColor(finalColor2.x*255, finalColor2.y*255, finalColor2.z*255);
                        ofDrawRectangle(x, y, 1, 1);
                        
                    }
                    else{
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
                                                  viewingPosition, hitPoint, closestNormal);
                           
                            Vector3D finalColor =lambColor.add(phongSpecular.add(closestColor.scale(0.1f)));
                            ofSetColor(finalColor.x * 255, finalColor.y * 255, finalColor.z * 255);
                            ofDrawRectangle(x, y, 1, 1); // Dibujar píxel
                        }
                        else{
                            ofSetColor(0, 0, 0);
                            ofDrawRectangle(x, y, 1, 1); // Dibujar píxel
                        }
                    }
        }
    }
}
//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
