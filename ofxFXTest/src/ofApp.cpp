#include "ofApp.h"

float size = 5;

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableAlphaBlending();
    width = 640;
    height = 480;
    
    ofSetWindowShape(width, height);
    
    glow.allocate(width, height);
}

//--------------------------------------------------------------
void ofApp::update(){
    glow.setRadius(size);
    glow.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    glow.begin();
    ofBackground(0);
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA );
    ofSetColor(ofColor::greenYellow);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotate(ofGetElapsedTimef() * 10., .5, .23, .27);
       ofDrawBox(0,0, 0, 100);
    ofPopMatrix();
    
    glow.end();
    
    glow.draw();
    
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == OF_KEY_UP)
        size += 1.5;
    else if(key == OF_KEY_DOWN)
        size -= 1.5;
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
