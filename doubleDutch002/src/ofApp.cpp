#include "ofApp.h"
#include "BulletSoftBody/btSoftRigidDynamicsWorld.h"

void ofApp::setup(){
    
    ofBackground(0);
    sender.setup(HOST, PORT);
    receiver.setup(PORTR);
    
    ofSetCoordHandedness(OF_RIGHT_HANDED);
    
    // Setup post-processing chain
    post.init(ofGetWidth(), ofGetHeight());
    post.createPass<BloomPass>()->setEnabled(true);
    
    
    world.setup();
    world.setCamera(&cam);
    
    
    for(int i=0; i<numRopes; i++){
        zs[i] = ofRandom(-150, 150);
        ys[i] = ofRandom(-150, 150);
        ofVec3f nodeA = ofVec3f( -ofGetWidth()/2, ys[i], zs[i]);
        ofVec3f nodeZ = ofVec3f( ofGetWidth()/2,ys[i],zs[i]);
        ropes.push_back( new ofxBulletRope() );
        ((ofxBulletRope*)ropes[i])->create( &world, nodeA, nodeZ, numNodes );
        ropes[i]->add();
        ropes[i]->setMass(10.1f);
        ropes[i]->setStiffness(1, 1, 1);
        ropes[i]->setFixedAt(0);
        ropes[i]->setFixedAt(numNodes+1);
    }
    
//  Fill Spheres Array
    for(int i=0;i<ropes.size();i++){
        spheres.push_back(std::vector<ofSpherePrimitive>());
        sMesh.push_back(std::vector<ofMesh>());
        ctrs.push_back(std::vector<ofPoint>());

        for(int j=0;j<numNodes;j++){
            spheres[i].push_back( ofSpherePrimitive(30,8) );
            
            sMesh[i].push_back( spheres[i][j].getMesh() );
            ctrs[i].push_back( sMesh[i][j].getCentroid() );
        }
    }
    
    for(int i=0;i<numRopes;i++){
        for(int j=0;j<numNodes;j++){
            vector<ofVec3f>& verts = sMesh[i][j].getVertices();
            int rad = ofRandom(vSizeL, vSizeH);
        
                for(unsigned int k = 0; k < verts.size(); k++){
                    verts[k].x = ctr.x + ofRandom(-rad, rad);
                    verts[k].y = ctr.y + ofRandom(-rad, rad);
                    verts[k].z = ctr.z + ofRandom(-rad, rad);
                }
        }
    }
    
     // Setup light
    light.setPosition(0, 2000, -750);
    
    for(int i=0;i<numRopes;i++){ aniTs[i] = 20; }
    
    // de Kooning Seated Woman
//    colors[0] = ofColor(176, 30, 7);
//    colors[1] = ofColor(196, 0, 0);
//    colors[2] = ofColor(185, 103, 10);
//    colors[3] = ofColor(235, 225, 136);
//    colors[4] = ofColor(21, 149, 102);
//    colors[5] = ofColor(111, 166, 21);
//    colors[6] = ofColor(203, 133, 28);
//    colors[7] = ofColor(224, 178, 0);
//    colors[8] = ofColor(106, 150, 36);
    
    // Kandinsky yellow-red-blue
//    colors[0] = ofColor(49, 47, 165);
//    colors[1] = ofColor(124, 145, 252);
//    colors[2] = ofColor(134, 96, 200);
//    colors[3] = ofColor(119, 115, 206);
//    colors[4] = ofColor(143, 108, 53);
//    colors[5] = ofColor(176, 158, 92);
//    colors[6] = ofColor(29, 21, 50);
//    colors[7] = ofColor(38, 11, 22);
//    colors[8] = ofColor(165, 152, 208);
    
    // Matisse La Danse
//    colors[0] = ofColor(6, 130, 96);
//    colors[1] = ofColor(17, 105, 174);
//    colors[2] = ofColor(209, 98, 45);
//    colors[3] = ofColor(93, 50, 37);
//    colors[4] = ofColor(88, 113, 162);
//    colors[5] = ofColor(0, 130, 88);
//    colors[6] = ofColor(0, 102, 173);
//    colors[7] = ofColor(224, 99, 30);
//    colors[8] = ofColor(0, 130, 94);
    
    // Jasper Johns Target
        colors[0] = ofColor(195, 14, 22);
        colors[1] = ofColor(10, 99, 225);
        colors[2] = ofColor(244, 197, 9);
        colors[3] = ofColor(21, 133, 78);
        colors[4] = ofColor(245, 81, 0);
        colors[5] = ofColor(120, 51, 255);
        colors[6] = ofColor(203, 50, 39);
        colors[7] = ofColor(0, 64, 190);
        colors[8] = ofColor(251, 206, 0);
    
    // Klee Southern Tunisian Gardens
//        colors[0] = ofColor(174, 42, 6);
//        colors[1] = ofColor(224, 183, 54);
//        colors[2] = ofColor(44, 150, 115);
//        colors[3] = ofColor(157, 122, 43);
//        colors[4] = ofColor(207, 222, 195);
//        colors[5] = ofColor(204, 43, 0);
//        colors[6] = ofColor(215, 157, 20);
//        colors[7] = ofColor(0, 158, 95);
//        colors[8] = ofColor(198, 125, 0);

    ofHideCursor();
}

void ofApp::update(){
    
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
    
    //move in circle
    
//    xPos = xOrig + radius * cos(angle);
//    yPos = yOrig + radius * sin(angle);
    
    if(freq > 72 && freq < 73){
        float nypos = ofMap(amp, -30, -10, -nyRange, nyRange);
        nypos = ofClamp(nypos, -nyRange, nyRange);
        if(amp < -50){nypos = 0;}
        ropes[0]->setNodePositionAt(0,  ofVec3f(-ofGetWidth()/2, nypos, zs[0]) );
    }
    
    if(freq > 74 && freq < 75){
        float nypos = ofMap(amp, -30, -10, -nyRange, nyRange);
        nypos = ofClamp(nypos, -nyRange, nyRange);
        if(amp < -50){nypos = 0;}
        ropes[1]->setNodePositionAt((numNodes+1),  ofVec3f(ofGetWidth()/2, nypos, zs[1]) );
    }
    
    if(freq > 70 && freq < 71){
        float nypos = ofMap(amp, -30, -10, -nyRange, nyRange);
        nypos = ofClamp(nypos, -nyRange, nyRange);
        if(amp < -50){nypos = 0;}
        ropes[2]->setNodePositionAt(0,  ofVec3f(-ofGetWidth()/2, nypos, zs[2]) );
        ropes[2]->setNodePositionAt((numNodes+1),  ofVec3f(ofGetWidth()/2, -nypos, zs[2]) );
    }
    
    if(freq > 57 && freq < 58){
        float nypos = ofMap(amp, -30, -10, -nyRange, nyRange);
        nypos = ofClamp(nypos, -nyRange, nyRange);
        if(amp < -50){nypos = 0;}
        ropes[3]->setNodePositionAt(0,  ofVec3f(-ofGetWidth()/2, nypos, zs[3]) );
    }
    
    if(freq > 59.5 && freq < 60.5){
        float nypos = ofMap(amp, -30, -10, -nyRange, nyRange);
        nypos = ofClamp(nypos, -nyRange, nyRange);
        if(amp < -50){nypos = 0;}
        ropes[4]->setNodePositionAt((numNodes+1),  ofVec3f(ofGetWidth()/2, nypos, zs[4]) );
    }
    
    if(freq > 62 && freq < 63){
        float nypos = ofMap(amp, -30, -10, -nyRange, nyRange);
        nypos = ofClamp(nypos, -nyRange, nyRange);
        if(amp < -50){nypos = 0;}
        ropes[5]->setNodePositionAt(0,  ofVec3f(-ofGetWidth()/2, nypos, zs[5]) );
        ropes[5]->setNodePositionAt((numNodes+1),  ofVec3f(ofGetWidth()/2, -nypos, zs[5]) );
    }
    
    if(freq > 77.5 && freq < 78.5){
        float nypos = ofMap(amp, -30, -10, -nyRange, nyRange);
        nypos = ofClamp(nypos, -nyRange, nyRange);
        if(amp < -50){nypos = 0;}
        ropes[6]->setNodePositionAt(0,  ofVec3f(-ofGetWidth()/2, nypos, zs[6]) );
    }
    
    if(freq > 79.7 && freq < 81){
        float nypos = ofMap(amp, -30, -10, -nyRange, nyRange);
        nypos = ofClamp(nypos, -nyRange, nyRange);
        if(amp < -50){nypos = 0;}
        ropes[7]->setNodePositionAt((numNodes+1),  ofVec3f(ofGetWidth()/2, nypos, zs[7]) );
    }
    
    if(freq > 82 && freq < 83){
        float nypos = ofMap(amp, -30, -10, -nyRange, nyRange);
        nypos = ofClamp(nypos, -nyRange, nyRange);
        if(amp < -50){nypos = 0;}
        ropes[8]->setNodePositionAt(0,  ofVec3f(-ofGetWidth()/2, nypos, zs[8]) );
        ropes[8]->setNodePositionAt((numNodes+1),  ofVec3f(ofGetWidth()/2, -nypos, zs[8]) );
    }
    

    
    for(int i=0;i<ropes.size();++i){
        for(int j=0; j<numNodes; j++){
            ofPoint n = ropes[i]->getNodePos(j);
            spheres[i][j].setPosition(n);
        }
    }
   
    

     for(int i=0;i<numRopes;i++){
         
          if(ofGetFrameNum()%aniTs[i] == 0){
              aniTs[i] = round( ofRandom(fRangeL, fRangeH) );
              int nNds = round( ofRandom( 1, (numNodes-1) ) );
              pNodes.clear();
              
              for(int j=0;j<nNds;j++){
                  int ndch = round( ofRandom( 1, (numNodes-1) ) );
                  vector<ofVec3f>& verts = sMesh[i][ndch].getVertices();
                  int rad = ofRandom(vSizeL, vSizeH);
                  
                  for(unsigned int k = 0; k < verts.size(); k++){
                      verts[k].x = ctr.x + ofRandom(-rad, rad);
                      verts[k].y = ctr.y + ofRandom(-rad, rad);
                      verts[k].z = ctr.z + ofRandom(-rad, rad);
                  }
              }
          }
     }

     
 
    


    


    
    
}


void ofApp::draw(){
    

    // copy enable part of gl state
    glPushAttrib(GL_ENABLE_BIT);
    
    // setup gl state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    light.enable();
    
    // begin scene to post process
    post.begin(cam);

    for(int i=0;i<ropes.size();++i){
        ofSetColor(colors[i]);
//      ropes[i]->draw();
        for(int j=0; j<numNodes; j++){
            

            
            ofPoint nd = ropes[i]->getNodePos(j);
            glPushMatrix();
            ofTranslate(nd);
            
            //planet.draw();
            sMesh[i][j].drawWireframe();
            glPopMatrix();
            
        }
    }
   
    
    
    // end scene and draw
    post.end();
    
    // set gl state back to original
    glPopAttrib();
    
    
}

void ofApp::keyPressed(int key){
   
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    


}


