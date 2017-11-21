#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    
    box.set(100);
    sphere.set(20, 10);
    
    light.enable();
    
    bOrbit = bRoll = true;
    angleH = roll = 0.0f;
    distance = 500.f;
    
    cam.setPosition(0, 0, 1000);
}

//--------------------------------------------------------------
void ofApp::update(){
    if (bOrbit) {
        angleH += 1.f;
        if (angleH > 360.f) angleH = 0.f;
        
        angleV += 0.25f;
        if (angleV > 360.f) angleV = 0.;
    }
    if (bRoll) roll += 0.5f;
    
    // convert angleV to range [-90,90] for latitude
    float vFac = sin(angleV * M_PI / 180.f) * 90.f;
    sphere.orbit(angleH, vFac, distance);
    sphere.roll(roll);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor(128);
    //ofEnableAlphaBlending();
    
    
    // translate to center of camera viewport and draw scene
    cam.begin();
    
    ofSetColor(200, 100, 0, 255);
    box.draw();
    box.drawAxes(200);
    
    ofSetColor(100, 200, 0, 255);
    sphere.draw();
    sphere.drawAxes(200);
    
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'h') {
        bOrbit = !bOrbit;
    }
    else if (key == 'r') {
        bRoll = !bRoll;
    }
    else if (key == OF_KEY_UP) {
        distance = MIN( (distance += 2.5f), 1000);
    }
    else if (key == OF_KEY_DOWN) {
        distance = MAX( (distance -= 2.5f), 150);
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
