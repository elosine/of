#include "ofApp.h"

#include "BulletSoftBody/btSoftRigidDynamicsWorld.h"

#ifndef round
#define round(x) (x<0?ceil((x)-0.5):floor((x)+0.5))
#endif

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	//ofBackground( 10, 10, 10);
    
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
	
	jointLength = .35f;
    
    ofVec3f node1 = camera.screenToWorld(ofVec3f( 0, ofGetHeight()/2, 0));
    ofVec3f node2 = camera.screenToWorld(ofVec3f( ofGetWidth()+10, ofGetHeight()/2, 0));
    
    ofVec3f node3 = camera.screenToWorld(ofVec3f( ofGetWidth()/2, ofGetHeight()/2, 0));
	
	shapes.push_back( new ofxBulletSphere() );
	((ofxBulletSphere*)shapes[0])->create( world.world, node3, 0.07f, .01f );
	shapes[0]->add();
	
	shapeColors.push_back( colors[(int)round(ofRandom(0, 3))] );
	
//	joints.push_back( new ofxBulletJoint() );
//	joints[joints.size()-1]->create( world.world, shapes[0], ofVec3f(0, 0, 0));
//	joints[joints.size()-1]->add();
    
   
	
	rope = new ofxBulletRope();
    //rope->create(&world, ofVec3f(0, 2, 0), ofVec3f(0, 5.5, 0), 50);
    rope->create(&world, node1, node2, 100);
	rope->add();
	rope->setMass(0.5f);
    rope->setStiffness(1, 1, 1);
    //rope->setFixedAt(0);
    //rope->setNodePositionAt(0, node1);

	//rope->attachRigidBodyAt(26, shapes[0]->getRigidBody());
    rope->setFixedAt(0);
    rope->setFixedAt(101);

    
    
    rope2 = new ofxBulletRope();
    rope2->create(&world, node3, node2, 20);
    rope2->add();
    rope2->setMass(0.5f);
    rope2->setStiffness(1, 1, 1);
    rope2->attachRigidBodyAt(0, shapes[0]->getRigidBody());
    rope2->setFixedAt(21);

//	patch = new ofxBulletPatch();
//	patch->create(&world, ofVec3f(-2, 2, -2), ofVec3f(-2, 2, 2), ofVec3f(2, 2, 2), ofVec3f(2, 2, -2));
//	patch->add();
//	patch->attachRigidBodyAt(0, shapes[0]->getRigidBody());
    
	bDrawDebug	= false;
	bSpacebar	= false;
	bAddEllipsoid = false;
	bShapesNeedErase = false;
	
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
	ofSetWindowTitle(ofToString(ofGetFrameRate(), 0));

	if (bAddEllipsoid) {
		ofxBulletEllipsoid *e = new ofxBulletEllipsoid();
		e->create(&world, ofVec3f(ofRandom(-20, 20), -5, ofRandom(-20, 20)), ofVec3f(ofRandom(0.5, 1), ofRandom(0.5, 1), ofRandom(0.5, 1)));
		e->add();
		ellipsoids.push_back(e);

		bAddEllipsoid = false;
	}
	
	mousePos = camera.screenToWorld( ofVec3f((float)ofGetMouseX(), (float)ofGetMouseY(), 0) );
	//joints[0]->updatePivotPos( mousePos, 2.f );
    
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
    
    if(bSpacebar) {
		for (int i = 1; i < joints.size(); i++) {
			delete joints[i];
		}
		joints.erase(joints.begin()+1, joints.end());
		bSpacebar = false;
		bShapesNeedErase = true;
	}
	
	for (int i = 1; i < joints.size(); i++) {
		if(i == 1) {
			joints[i]->updatePivotPos( shapes[i-1]->getPosition(), jointLength*2.f );
		} else {
			joints[i]->updatePivotPos( shapes[i-1]->getPosition(), jointLength );
		}
	}
    
  
    
}

//--------------------------------------------------------------
void ofApp::draw() {
	glEnable( GL_DEPTH_TEST );
   //ofBackgroundGradient( ofColor( 255 ), ofColor( 128 ) );
    ofBackground(0);

	camera.begin();
	
	ofSetLineWidth(1.f);
	if(bDrawDebug) world.drawDebug();
	
	//ofSetColor(255, 255, 255);
	//ofSphere(mousePos, .15f);
	
//	ofEnableLighting();
//	light.enable();
    //light.setPosition( mousePos );
  //  light.setPosition( ofVec3f(0.24, -3.81, 4.23) );
    //cout << mousePos << endl;
	
	ofSetColor(100, 100, 100);
	//ground->draw();
    
    
    ofSetColor(ofColor::lime);
    ofSetLineWidth(3);
    rope->draw();
    //rope2->draw();
    
    ofSetColor(255, 255, 255);
//	patch->draw();
    
    ofSetColor(0, 255, 0);
	for(int i = 0; i < ellipsoids.size(); i++) {
		ellipsoids[i]->draw();
	}
	
//	ofSetColor(255, 0, 255);
//	for(int i = 0; i < shapes.size(); i++) {
//		ofSetColor(shapeColors[i]);
//		shapes[i]->draw();
//	}
//	ofSetColor(220, 220, 220);
//	for(int i = 0; i < joints.size(); i++) {
//		joints[i]->draw();
//	}
//	light.disable();
//	ofDisableLighting();
	
	camera.end();
	glDisable(GL_DEPTH_TEST);
	
//	ofSetColor(255, 255, 255);
//	stringstream ss;
//	ss << "framerate: " << ofToString(ofGetFrameRate(),0) << endl;
//	ss << "num shapes: " << (shapes.size()) << endl;
//	ss << "draw debug (d): " << ofToString(bDrawDebug, 0) << endl;
//	ss << "break joints with spacebar: " << bSpacebar << endl;
//	ss << "append node to rope (n)" << endl;
//	ss << "drop an ellipsoid (e)" << endl;
//	ofDrawBitmapString(ss.str().c_str(), 10, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
		case ' ':
			bSpacebar = true;
			break;
		case 'd':
			bDrawDebug = !bDrawDebug;
			break;
        case 'n':
            rope->appendNode();
            break;
		case 'e':
			bAddEllipsoid = true;
			break;
		default:
			break;
	}
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
	if(bShapesNeedErase) {
		for (int i = 1; i < shapes.size(); i++) {
			delete shapes[i];
		}
		shapes.erase( shapes.begin()+1, shapes.end() );
		bShapesNeedErase = false;
		shapeColors.erase(shapeColors.begin()+1, shapeColors.end());
	}
	
	float rsize = ofRandom(.15, .3);
	
	ofVec3f diff;
	if(shapes.size() < 2) {
		diff = mousePos - shapes[0]->getPosition();
	} else {
		diff = shapes[shapes.size()-2]->getPosition() - shapes[shapes.size()-1]->getPosition();
	}
	diff.normalize();
	if(shapes.size() < 2) {
		diff *= -(jointLength*2.f);
	} else {
		diff *= -jointLength;
	}
	diff += shapes[shapes.size()-1]->getPosition();
	
	shapes.push_back( new ofxBulletSphere() );
	((ofxBulletSphere*)shapes[shapes.size()-1])->create( world.world, diff, .8, rsize );
	shapes[shapes.size()-1]->add();
	
	shapeColors.push_back( colors[(int)round(ofRandom(0, 3))] );
	
	
	joints.push_back( new ofxBulletJoint() );
	joints[joints.size()-1]->create(world.world, shapes[shapes.size()-1], shapes[shapes.size()-2]->getPosition());
	joints[joints.size()-1]->add();
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
