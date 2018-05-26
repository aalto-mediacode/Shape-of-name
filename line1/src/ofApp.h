#pragma once

#include "ofMain.h"
#include "JLLine.h"
#include "JLSoundAnalyzer.h"

// private member property area /////////////////////////////////

// public member property area //////////////////////////////////

// private member method area ///////////////////////////////////

// public member method area ////////////////////////////////////

// public event handling area //////////////////////////////////

class ofApp : public ofBaseApp
{
    
    // private member property area /////////////////////////////////
private:
    
    int Max_Line;
    int Max_Frame_Count;
    
    JLSoundAnalyzer soundAnalyzer;
    vector<JLLine *> lineList;
    
    
    // public member property area //////////////////////////////////
public:
    

    // private member method area ///////////////////////////////////
private:
    
    void initDefaultData();
    void checkRelation();
    
    
    // public member method area ////////////////////////////////////
public:
    
    void setup();
    void update();
    void draw();
    
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
		
};
