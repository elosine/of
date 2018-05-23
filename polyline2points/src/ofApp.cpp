#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    float i = 0;
    while (i < TWO_PI) { // make a heart
        float r = (2-2*sin(i) + sin(i)*sqrt(abs(cos(i))) / (sin(i)+1.4)) * -80;
        float x = ofGetWidth()/2 + cos(i) * r;
        float y = ofGetHeight()/2 + sin(i) * r;
        line.addVertex(ofVec2f(x,y));
        i+=0.005*HALF_PI*0.5;
    }
    line.close(); // close the shape
    
    
    
    //polyline from SVG
//    void ofApp::setup(){
//        
//        svg.load("1.svg");
//        
//        for (int i = 0; i < svg.getNumPath(); i++) {
//            ofPath shape = svg.getPathAt(i);
//            for(int j = 0; j < shape.getOutline().size(); j++) {
//                ofPolyline line = shape.getOutline().at(j);
//                edgeLine.addVertexes(line);
//            }
//        }
//        edgeLine.setPhysics(0.0, 0.1, 0.7);
//        edgeLine.create(box2d.getWorld());
//    }
//    
//    
//    void ofApp::draw(){
//        edgeLine.draw();
//    }
    
    

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    line.draw();
    line2.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    

    ofPolyline newline = line.getResampledByCount(1000);
    vector<ofPoint>& vertices  = newline.getVertices();
    
    for(int i=0; i<vertices.size(); i++){
    cout << vertices[i] << endl;
    }
    cout<<vertices.size()<<endl;

    }

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    ofPoint pt;
    pt.set(x,y);
    line2.addVertex(pt);

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    line2.clear();

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
