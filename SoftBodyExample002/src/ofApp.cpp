#include "ofApp.h"

#include "BulletSoftBody/btSoftRigidDynamicsWorld.h"

#ifndef round
#define round(x) (x<0?ceil((x)-0.5):floor((x)+0.5))
#endif

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
    
    sender.setup(HOST, PORT);
    receiver.setup(PORTR);
  
	camera.setPosition(ofVec3f(0, -4.f, -10.f));
	camera.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));
	
	world.setup();
	world.setCamera(&camera);
	
//	ground = new ofxBulletBox();
//	ground->create( world.world, ofVec3f(0., 5.5, 0.), 0., 50., 1.f, 50.f );
//	ground->setProperties(.25, .95);
//	ground->add();
	
	colors[0] = ofColor(15,197,138);
	colors[1] = ofColor(220, 0, 220);
	colors[2] = ofColor(220, 180, 60);
	colors[3] = ofColor(255, 20, 50);
	
    
    ofVec3f node1 = camera.screenToWorld(ofVec3f( 0, ofGetHeight()/2, 0));
    ofVec3f node2 = camera.screenToWorld(ofVec3f( ofGetWidth()+10, ofGetHeight()/2, 0));
    ofVec3f node3 = camera.screenToWorld(ofVec3f( ofGetWidth()/2, ofGetHeight()/2, 0));
	
    rope = new ofxBulletRope();
    //rope->create(&world, ofVec3f(0, 2, 0), ofVec3f(0, 5.5, 0), 50);
    rope->create(&world, node1, node2, 100);
	rope->add();
	rope->setMass(0.5f);
    rope->setStiffness(1, 1, 1);
    //rope->setFixedAt(0);
    //rope->setNodePositionAt(0, node1);

    rope->setFixedAt(0);
    rope->setFixedAt(101);

    
    rope2 = new ofxBulletRope();
    rope2->create(&world, node3, node2, 20);
    rope2->add();
    rope2->setMass(0.5f);
    rope2->setStiffness(1, 1, 1);
    rope2->setFixedAt(21);
	
	ofHideCursor();
}

//--------------------------------------------------------------
void ofApp::update() {
    
    ofxOscMessage m;
    m.setAddress("/getFreqAmp");
    sender.sendMessage(m, false);
    
    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        if(m.getAddress() == "/freqAmp"){
            
            freq = m.getArgAsFloat(0);
            amp = m.getArgAsFloat(1);
        }
        
    }

	world.update();
	//ofSetWindowTitle(ofToString(ofGetFrameRate(), 0));

    if(freq > 80 && freq < 90){
       // float nypos = ofMap(amp, -30, -10, ofGetHeight(), 0);
        float nypos = ofMap(amp, -30, -10, ofGetHeight()/2, 0);
        nypos = ofClamp(nypos, -5, ofGetHeight()+5);
        if(amp < -50){
            nypos = ofGetHeight()/2;
        }
        
//        rope->setNodePositionAt(0, camera.screenToWorld( ofVec3f(-10, nypos, 0) ));
//        rope->setNodePositionAt(51, camera.screenToWorld( ofVec3f(ofGetWidth()+10, ofGetHeight()-nypos, 0) ));
        
        rope->setNodePositionAt(0, camera.screenToWorld( ofVec3f(-5, nypos, 0) ));
        rope->setNodePositionAt(101, camera.screenToWorld( ofVec3f(ofGetWidth()+5, ofGetHeight()-nypos, 0) ));
        //rope->setNodePositionAt(101, camera.screenToWorld( ofVec3f(ofGetWidth()+5, nypos, 0) ));

        
//        rope->setNodePositionAt(0, camera.screenToWorld( ofVec3f((ofGetWidth()/2) - 100, nypos, 0) ));
//        rope->setNodePositionAt(51, camera.screenToWorld( ofVec3f( (ofGetWidth()/2) + 100, ofGetHeight()-nypos, 0) ));
        
    }
    
}

//--------------------------------------------------------------
void ofApp::draw() {
	glEnable( GL_DEPTH_TEST );
   //ofBackgroundGradient( ofColor( 255 ), ofColor( 128 ) );
    ofBackground(0);

	camera.begin();
	
	ofSetLineWidth(1.f);
	
//	ofEnableLighting();
//	light.enable();
    //light.setPosition( mousePos );
  //  light.setPosition( ofVec3f(0.24, -3.81, 4.23) );
	
	ofSetColor(100, 100, 100);
	//ground->draw();
    
    ofSetColor(ofColor::lime);
    ofSetLineWidth(3);
    rope->draw();
    //rope2->draw();
    
//	light.disable();
//	ofDisableLighting();
	
	camera.end();
	glDisable(GL_DEPTH_TEST);
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) { 
	
}
