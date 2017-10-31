#pragma once

#include "ofMain.h"
#include "ofxBullet.h"
#include "ofxOsc.h"
#include "ofxPostProcessing.h"


#define HOST "localhost"
#define PORT 57120
#define PORTR 12321

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	ofxBulletWorldSoft			world;
	//ofxBulletBox*				ground;

    ofxBulletRope*				rope;
    ofxBulletRope*				rope2;
	
	vector<ofColor>				shapeColors;
	ofColor						colors[4];
	
	ofCamera					camera;
	ofLight						light;
    
    ofxOscReceiver receiver;
    ofxOscSender sender;
    
    float amp, freq;
    
    
    ofxPostProcessing post;
		
};
