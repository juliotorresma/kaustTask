#include "ofApp.h"
#include "Ray.hpp"
#include "Vector3D.h"
#include "Ellipsoid.hpp"
#include "Sphere.hpp"
#include "SceneObject.hpp"
#include "Light.hpp"
#include <vector>
#include <memory>

using std::make_shared;
using std::shared_ptr;
// Creating a red sphere with radius of 1, 5 units away
//auto sphere_ptr = make_shared<Sphere>(Vector3D(0, 0, -5), Vector3D(1, 0, 0), 1);

//Cone cone(Vector3D(-2, -2, -5), Vector3D(0, 1, 0), Vector3D(0, 1, 0), ofDegToRad(30));

//Ellipsoid ellip(Vector3D(2, 2, -5), Vector3D(2, 1, 1.5), Vector3D(0, 0, 1));

// lightPosition, lightIntensity, fractionOfLight
Light light(Vector3D(0,5,5), Vector3D(1,1,1), 1.3f);

// Define the viewport postion
Vector3D viewingPosition(0,0,0);

vector<std::unique_ptr<SceneObject>> sceneObjects;


//--------------------------------------------------------------
void ofApp::setup(){

    sceneObjects.push_back(make_unique<Sphere>(Vector3D(0, 0, -5), Vector3D(1, 0, 0), 1.0f));
    
    sceneObjects.push_back(make_unique<Ellipsoid>(
        Vector3D(0, 3, -5),          // Centro de la elipse
        Vector3D(2.0f, 1.0f, 1.5f), // Semi-ejes: X=2.0, Y=1.0, Z=1.5
        Vector3D(0, 0, 1)           // Color: Azul
    ));
    
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
            Vector3D rayDirection = canvasPosition.subtract(viewingPosition).normalize();;
            Ray ray(viewingPosition, rayDirection);
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
                    
            float lightAngle = std::max(0.0f,closestNormal.dot(Ldir));
            if (lightAngle>0){
                Vector3D finalColor = Vector3D(lightAngle*closestColor.x *light.lightIntensity.x * light.I_a.x,
                                               lightAngle*closestColor.y *light.lightIntensity.y * light.I_a.y,
                                               lightAngle*closestColor.z *light.lightIntensity.z * light.I_a.z);
                
                ofSetColor(finalColor.x * 255, finalColor.y * 255, finalColor.z * 255);
                ofDrawRectangle(x, y, 1, 1); // Dibujar píxel
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
