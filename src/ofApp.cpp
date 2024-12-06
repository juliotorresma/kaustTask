#include "ofApp.h"
#include <cmath>
// Creating a red sphere with radius of 1, 5 units away
Sphere sphere(Vector3D(0, 0, 5), Vector3D(1, 0, 0), 1);

Cone cone(Vector3D(-2, -2, -5), Vector3D(0, 1, 0), Vector3D(0, 1, 0), ofDegToRad(30));

Ellipsoid ellip(Vector3D(2, 2, -5), Vector3D(2, 1, 1.5), Vector3D(0, 0, 1));

// Define the viewport postion
Vector3D viewingPosition(0,0,0);

//--------------------------------------------------------------
void ofApp::setup(){
    
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
            
            // Creating a Ray
            Ray ray(viewingPosition, rayDirection);
            /*
            // Try to detect sphere
            Vector3D sphereColor = sphere.detectSphere(viewingPosition, sphere, ray);
            
            if (sphereColor.x != 0 || sphereColor.y != 0 || sphereColor.z != 0) {
                ofSetColor(sphereColor.x * 255, sphereColor.y * 255, sphereColor.z * 255);
                ofDrawRectangle(x, y, 1, 1); // Dibujar píxel
            }
            
            // Try to detect cone
        
            Vector3D coneColor = cone.detectCone(viewingPosition, cone, ray);
            
            if (coneColor.x != 0 || coneColor.y != 0 || coneColor.z != 0) {
                ofSetColor(coneColor.x * 255, coneColor.y * 255, coneColor.z * 255);
                ofDrawRectangle(x, y, 1, 1); // Dibujar píxel
            }
            */
            // Try to detect ellipsoid
            Vector3D ellipColor = ellip.detectEllipsoid(viewingPosition, ellip, ray);
            
            ofSetColor(ellipColor.x * 255, ellipColor.y * 255, ellipColor.z * 255);
            ofDrawRectangle(x, y, 1, 1); // Dibujar píxel
            
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
