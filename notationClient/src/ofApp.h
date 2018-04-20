#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxOsc.h"

struct Ball {
    int x;
    int y;
    int vx;
    int vy;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
        void draw();
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        Ball whiteBall;
        Ball yellowBall;
    
    ofTrueTypeFont font; // standard font
    ofTrueTypeFont titleFont; // font for some info in the title line
    string clientMessages; // string containing the received messages for display

    
    
    void setGUI1();
    
    ofxUISuperCanvas *gui1;
    ofxUITextInput *textInput;
    ofxUIDropDownList *ddl;

    void guiEvent(ofxUIEventArgs &e);
    
    
    // Client side:
    
    ofxOscSender clientSender; // all-important ofxOscSender object
    string clientDestination; // IP address we're sending to
    int clientSendPort; // port we're sending to
    string clientTyping; // what we're going to send: some stuff you typed
    
    ofxOscReceiver clientReceiver; // OSC receiver
    int clientRecvPort; // port where we listen for messages
    


		
};
