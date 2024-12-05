#include "ofApp.h"
#include <cmath>
// Creating a red sphere with radius of 1, 5 units away
Sphere sphere(Vector3D(0, 0, 5), Vector3D(1, 0, 0), 1);

Cone cone(Vector3D(-2, -2, -5), Vector3D(0, 1, 0), Vector3D(0, 1, 0), ofDegToRad(30));

Ellipsoid ellip(Vector3D(3, 3, -5), Vector3D(3, 1, 1), Vector3D(0, 0, 1));

// Define the viewport postion
Vector3D viewPortPosition(0,0,0);

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
            float v = (y - height / 2.0f) / (height / 2.0f);
            
            // Define the direction
            Vector3D pixelInCenter(u,-v,-1);
            Vector3D rayDirection = pixelInCenter.subtract(viewPortPosition);
            
            // Creating a Ray
            Ray ray(viewPortPosition, rayDirection);
            // Try to detect sphere
            float sphereT = sphere.detectSphere(viewPortPosition, rayDirection, sphere);
            if (sphereT != 0) {
                Vector3D hitPoint = ray.origin.add(ray.direction.scale(sphereT));
                
                Vector3D color = sphere.color;
                ofSetColor(color.x * 255, color.y * 255, color.z * 255);
                ofDrawRectangle(x, y, 1, 1); // Dibujar píxel
            }
            // Try to detect cone
            float coneT = cone.detectCone(viewPortPosition, rayDirection, cone);
            
            if (coneT != 0) {
                Vector3D hitPoint = ray.origin.add(ray.direction.scale(coneT));
                Vector3D vectorToIntersection = hitPoint.subtract(cone.vortex);
                
                if (vectorToIntersection.dot(cone.centralAxis) <= 0) {
                    Vector3D color = cone.color;
                    ofSetColor(color.x * 255, color.y * 255, color.z * 255);
                    ofDrawRectangle(x, y, 1, 1); // Dibujar píxel
                }
            }
            float ellipT = ellip.detectEllipsoid(viewPortPosition, rayDirection, ellip.center, ellip.semiAxis);
            if (ellipT != 0) {
                Vector3D hitPoint = ray.origin.add(ray.direction.scale(ellipT));
                Vector3D color = ellip.color;
                ofSetColor(color.x * 255, color.y * 255, color.z * 255);
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
