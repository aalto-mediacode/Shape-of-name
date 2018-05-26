#pragma once

#include "ofMain.h"
#include "JLParticle.h"

#define NUM_OF_PARTICLES 1000

class ofApp : public ofBaseApp
{
    
private:
    
    float scrWidth;
    float scrHeight;
    int stopFrameCount;
    int displayWidth;
    bool imageSaved;
    string text;
    
    ofTrueTypeFont myFont;
    ofImage image;
    vector<JLParticle> myParticles;
    
    //------- private member method area ---------------------//
    
    void initDefaultData();
    void createParticles();
    void checkConnettion();
    void calcString();
    void saveImage();
    
    
    //------- public member method area ---------------------//

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
