#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetWindowShape(1600, 1000);
    
    ofToggleFullscreen();
    ofBackground(0, 0, 0);
    ofSetColor(255, 255, 255);
    ofSetBackgroundAuto(false);
    ofEnableSmoothing();
    
    myWidth  = ofGetScreenWidth();
    myHeight = ofGetScreenHeight();
    
    imageBackground.load("background.jpg");
    imageObject1.load("object01.png");
    imageObject2.load("object02.png");
    imageObject3.load("object03.png");
    
    for (int i=0;i<500;i++)
    {
        listFish.push_back(new JLFish(ofRandom(myWidth) , ofRandom(myHeight) , myWidth , myHeight));
    }
}

//--------------------------------------------------------------
void ofApp::update()
{
    
    ;

}

//--------------------------------------------------------------
void ofApp::draw()
{
    //imageBackground.draw(0,0);
    
    ofSetColor(0,2);
    
    //ofDrawRectangle(0,0, ofGetWidth(), ofGetHeight());
    
    for(JLFish *fish : listFish)
    {
        fish->align(&listFish);
        
        fish->cohesion(&listFish);
        
        fish->separation(&listFish);
        
        fish->update();
        
        fish->checkBorders();
        
        fish->refresh();
    }
    
    
    /*
    imageObject1.draw(0,0);
    imageObject2.draw(0,0);
    imageObject3.draw(0,0);
     */
    
}

//--------------------------------------------------------------
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
