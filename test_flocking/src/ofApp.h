#pragma once

#include "ofMain.h"
#include "JLFish.h"

class ofApp : public ofBaseApp
{
private:
    
    int myWidth;
    int myHeight;
    vector<JLFish *> listFish;
    ofVec2f steer;
    ofImage imageBackground;
    ofImage imageObject1;
    ofImage imageObject2;
    ofImage imageObject3;

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
