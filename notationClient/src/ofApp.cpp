#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    textInput = NULL;
    setGUI1();
    gui1->loadSettings("gui1Settings.xml");
    
    
    //Client side
    clientDestination	= "129.161.54.45";
    clientSendPort = 57120;
    clientSender.setup(clientDestination, clientSendPort);
    
    clientRecvPort = 12321;
    clientReceiver.setup(clientRecvPort);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    // Client side:
    
    // OSC receiver queues up new messages, so you need to iterate
    // through waiting messages to get each incoming message
    
    // check for waiting messages
    while(clientReceiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        clientReceiver.getNextMessage(&m);
        ofLogNotice("Client just received a message");
        // check the address of the incoming message
        if(m.getAddress() == "/chatlog"){
            // get the first argument (we're only sending one) as a string
            if(m.getNumArgs() > 0){
                if(m.getArgType(0) == OFXOSC_TYPE_STRING){
                    string oldMessages = clientMessages;
                    clientMessages = m.getArgAsString(0) + "\n" + oldMessages;
                }
            }
        }
    }
    
    //this is purely workaround for a mysterious OSCpack bug on 64bit linux
    // after startup, reinit the receivers
    // must be a timing problem, though - in debug, stepping through, it works.
    if(ofGetFrameNum() == 60){
        clientReceiver.setup(clientRecvPort);
    }


}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(ofColor::aqua);
    
    

}

void ofApp::guiEvent(ofxUIEventArgs &e){
    
    string name = e.getName();
    int kind = e.getKind();
    cout << "got event from: " << name << endl;
    if(name == "TEXT INPUT")
    {
        ofxUITextInput *ti = (ofxUITextInput *) e.widget;
        if(ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER)
        {
            string output = ti->getTextString();
            ofxOscMessage m;
            m.setAddress("/id");
            m.addStringArg(clientTyping);
            clientSender.sendMessage(m, false);
        }
        else if(ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS)
        {
            cout << "ON FOCUS: ";
        }
        else if(ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS)
        {
            cout << "ON BLUR: ";
        }
        string output = ti->getTextString();
        cout << output << endl;
        
    }
}


//--------------------------------------------------------------

void ofApp::exit()
{
    gui1->saveSettings("gui1Settings.xml");
    
    delete gui1;
   
}

//--------------------------------------------------------------

void ofApp::setGUI1()
{
    
    gui1 = new ofxUISuperCanvas("PANEL 2: ADVANCED");
    
    gui1->addSpacer();
    gui1->setWidgetFontSize(OFX_UI_FONT_MEDIUM);
    textInput = gui1->addTextInput("TEXT INPUT", "Input Text");
    textInput->setAutoUnfocus(false);
    textInput->setAutoClear(false);
    gui1->addLabel("AUTO CLEAR DISABLED", OFX_UI_FONT_SMALL);
    gui1->addTextInput("TEXT INPUT2", "Input Text")->setAutoClear(false);
    gui1->setWidgetFontSize(OFX_UI_FONT_MEDIUM);
    
    vector<string> items;
    items.push_back("Violin"); items.push_back("Viola"); items.push_back("Cello");
    items.push_back("Bass"); items.push_back("Trumpet"); items.push_back("Percussion");

    gui1->addSpacer();
    gui1->setWidgetFontSize(OFX_UI_FONT_MEDIUM);
    ddl = gui1->addDropDownList("DROP DOWN LIST", items);
    ddl->setAllowMultiple(true);
    
    gui1->addSpacer();
    gui1->addLabel("LABEL BUTTON", OFX_UI_FONT_MEDIUM);
    gui1->addLabelButton("LABEL BTN", false);

    
    gui1->setGlobalButtonDimension(OFX_UI_GLOBAL_BUTTON_DIMENSION);

    
    gui1->setPosition(212, 0);
    gui1->autoSizeToFitWidgets();
    
    ofAddListener(gui1->newGUIEvent,this,&ofApp::guiEvent);
}



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
