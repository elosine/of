#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(255);
	ofSetCircleResolution(200);
    
    
}

//--------------------------------------------------------------
void ofApp::setupGui(){
	parameters.setName("parameters");
	parameters.add(radius.set("radius",50,1,100));
	parameters.add(color.set("color",100,ofColor(0,0),255));
	gui.setup(parameters);
	ofSetBackgroundColor(0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(color);
	ofDrawCircle(ofGetWidth()*0.5,ofGetWidth()*0.5,radius);
	ofSetColor(0);
	ofDrawBitmapString(ofGetFrameRate(),20,20);
}

//--------------------------------------------------------------
void ofApp::drawGui(ofEventArgs & args){
   
	gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key=='b')
    {
    
    ofGLFWWindowSettings settings;
    settings.width = 300;
    settings.height = 300;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = false;
    windows.push_back( ofCreateWindow(settings) );
    windows.back()->setVerticalSync(false);
        
//    ofAddListener(windows.back()->events().draw, this,&ofApp::drawRandomInWindow);
    }
    
    if(key=='a')
    {
        
        windows.back()->setWindowShouldClose();
       
    }
   
    
   
}


void ofApp::drawRandomInWindow(ofEventArgs &args){
    ofPushStyle();
    ofSetColor(ofRandom(128,255));
    ofFill();
    ofDrawRectangle(ofRandomuf()*20.f, ofRandomuf()*20.f, ofRandomuf()*80.f, ofRandomuf()*80.f);
    ofPopStyle();
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
