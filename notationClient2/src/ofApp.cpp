#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    idname = "zzzzz";
    
    textInput = NULL;
    setGUI1();
    gui1->loadSettings("gui1Settings.xml");
    
    // load fonts to display stuff
    font.load("futura_book.otf", 12);
    titleFont.load("futura_book.otf", 20);
    
    velocity = 100.0;
    gravity = 9.81;
    accel = 0.03;
    dir = 1;
    
    
    //Client side
    clientDestination	= "169.120.0.0";
    clientSendPort = 57120;
    clientSender.setup(clientDestination, clientSendPort);
    
    clientRecvPort = 12321;
    clientReceiver.setup(clientRecvPort);
    

    for (int i=0; i<ofGetHeight(); ++i)
    {
        crvTab.push_back(ofGetHeight()-i);
    }
    cirx = 0;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofxOscMessage m;
    m.setAddress("/getkdata");
    m.addStringArg(idname);
    clientSender.sendMessage(m, false);
    

    
    
    gravity = gravity *  ( 1+(accel*dir) );
    velocity = velocity + (gravity*dir);
    if ( velocity >= ofGetHeight()-5 )
    {
        dir = -1;
    }
    
    ciry = round(crvTab[cirx]);
    
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
        if(m.getAddress() == "/hello")
        {
            cout << "fdsak" << endl;
            
            // get the first argument (we're only sending one) as a string
            if(m.getNumArgs() > 0){
                if(m.getArgType(0) == OFXOSC_TYPE_INT32){
                    cout << m.getAddress() << endl;
                    cout << m.getArgAsInt(0) << endl;
                }
            }
        }
        if(m.getAddress() == "/reply")
        {
            // get the first argument (we're only sending one) as a string
            if(m.getNumArgs() > 0){
                if(m.getArgType(0) == OFXOSC_TYPE_STRING){
                    string oldMessages = clientMessages;
                    clientMessages = m.getArgAsString(0) + "\n" + oldMessages;
                   
                }
            }
        }
        
        
        if(m.getAddress() == "/bounce")
        {
            
            if(m.getArgType(0) == OFXOSC_TYPE_FLOAT)
            {
                gravity = m.getArgAsFloat(0);
                accel = m.getArgAsFloat(1);
            }
            velocity = 100;
            dir = 1;
            
            
        }
        
        if(m.getAddress() == "/kdat")
        {
            
            if(m.getArgType(0) == OFXOSC_TYPE_FLOAT)
            {
                cirx = round( ofGetHeight()*m.getArgAsFloat(0) );
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
    ofBackground(ofColor::lightSeaGreen);
    
    
    clientTyping = "";
    
    for(unsigned int i = 0; i < clientMessages.size(); i++)
    {
        string oldTyping = clientTyping;
        clientTyping = oldTyping + clientMessages[i];
    }
    //Display the messages
    
    font.drawString(clientTyping, 542, 100);
    
    ofSetColor(0,0,0);
    ofCircle(900, velocity, 50);
    
    
    ofSetColor(ofColor::darkorange);
    for (int i=0; i<crvTab.size(); ++i) {
        ofDrawCircle(i, crvTab[i], 3);
    }
    
    ofSetColor(0,0,0);
    ofDrawCircle( cirx, ciry, 30);
    
    
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
            idname = output;
            cout<<output<<endl;
            ofxOscMessage m;
            m.setAddress("/id");
            m.addStringArg(output);
            clientSender.sendMessage(m, false);
        }
        string output = ti->getTextString();
        cout << output << endl;
        
    }
    if(name == "TEXT INPUT2")
    {
        ofxUITextInput *ti = (ofxUITextInput *) e.widget;
        if(ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER)
        {
            string output = ti->getTextString();
            clientDestination = output;
            
            clientSender.setup(clientDestination, clientSendPort);
            cout << output << endl;
        }
        
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
    
    gui1 = new ofxUISuperCanvas("Networked Notation");
    
    gui1->addSpacer();
    gui1->setWidgetFontSize(OFX_UI_FONT_MEDIUM);
    textInput = gui1->addTextInput("TEXT INPUT", "Input ID");
    textInput->setAutoUnfocus(false);
    textInput->setAutoClear(false);
    
    gui1->addSpacer();
    gui1->setWidgetFontSize(OFX_UI_FONT_MEDIUM);
    textInput = gui1->addTextInput("TEXT INPUT2", "Input Server IP");
    textInput->setAutoUnfocus(false);
    textInput->setAutoClear(false);
    
    
    
    //    vector<string> items;
    //    items.push_back("Violin"); items.push_back("Viola"); items.push_back("Cello");
    //    items.push_back("Bass"); items.push_back("Trumpet"); items.push_back("Percussion");
    //
    //    gui1->addSpacer();
    //    gui1->setWidgetFontSize(OFX_UI_FONT_MEDIUM);
    //    ddl = gui1->addDropDownList("DROP DOWN LIST", items);
    //    ddl->setAllowMultiple(true);
    //
    //    gui1->addSpacer();
    //    gui1->addLabel("LABEL BUTTON", OFX_UI_FONT_MEDIUM);
    //    gui1->addLabelButton("LABEL BTN", false);
    //
    //
    //    gui1->setGlobalButtonDimension(OFX_UI_GLOBAL_BUTTON_DIMENSION);
    //
    
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
