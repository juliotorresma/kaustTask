#include "ofApp.h"
#include "Ray.hpp"
#include "Vector3D.h"
#include "Sphere.hpp"
#include "SceneObject.hpp"
#include <vector>
#include <memory>

using std::make_shared;
using std::shared_ptr;
// Creating a red sphere with radius of 1, 5 units away
//auto sphere_ptr = make_shared<Sphere>(Vector3D(0, 0, -5), Vector3D(1, 0, 0), 1);

//Cone cone(Vector3D(-2, -2, -5), Vector3D(0, 1, 0), Vector3D(0, 1, 0), ofDegToRad(30));

//Ellipsoid ellip(Vector3D(2, 2, -5), Vector3D(2, 1, 1.5), Vector3D(0, 0, 1));

// lightPosition, lightIntensity, fractionOfLight
//Light light(Vector3D(0,5,5), Vector3D(1,1,1), 1.3f);

// Define the viewport postion
Vector3D viewingPosition(0,0,0);

vector<std::unique_ptr<SceneObject>> sceneObjects;


//--------------------------------------------------------------
void ofApp::setup(){

    sceneObjects.push_back(make_unique<Sphere>(Vector3D(0, 0, -5), Vector3D(1, 0, 0), 1.0f));
    
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
            // Normalize coordinates of pixels so they can fit in world space
            float u = (x - width / 2.0f) / (width / 2.0f);
            float v = (y - height / 1.5f) / (height / 1.5f);
            
            // Define the direction
            Vector3D canvasPosition(u,-v,-1);
            Vector3D rayDirection = canvasPosition.subtract(viewingPosition);
            Ray ray(viewingPosition, rayDirection);
            float closestT = std::numeric_limits<float>::infinity();
            Vector3D closestColor(0, 0, 0);
            for (const auto& obj : sceneObjects){
                float t;
                Vector3D hitColor;
                
                if (obj->intersect(ray, t, hitColor)) {
                    if (t<closestT){
                        closestT = t;
                        closestColor = hitColor;
                    }
                }
            }
            
            Vector3D hitPoint = ray.origin.add(ray.direction.scale(closestT));
            ofSetColor(closestColor.x * 255, closestColor.y * 255, closestColor.z * 255);
            ofDrawRectangle(x, y, 1, 1); // Dibujar píxel
            
            
            // Creating a Ray
        

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
