#include "ofApp.h"

// private member method area ///////////////////////////////////

void ofApp::initDefaultData()
{
    JLLine *line;
    
    Max_Frame_Count = 0;
    
    Max_Line = 400;
    
    for (int i=0;i<Max_Line;i++)
    {
        line = new JLLine();
        
        line->setLength(ofRandom(50,200));
        line->setAngle(ofRandom(0,360));
        line->setPosition(ofRandom(0,ofGetWindowWidth()),ofRandom(0,ofGetWindowHeight()));
        
        lineList.push_back(line);
    }
    
    soundAnalyzer.loadSong("test.mp3");
}

void ofApp::checkRelation()
{
    int dist;
    JLLine *srcLine;
    JLLine *tarLine;
    
    for (int i=0;i<lineList.size();i++)
    {
        srcLine = lineList.at(i);
        
        for (int j=i+1;j<lineList.size();j++)
        {
            tarLine = lineList.at(j);
            
            dist = ofDist(srcLine->getCurPosition().x,srcLine->getCurPosition().y,tarLine->getCurPosition().x,tarLine->getCurPosition().y);
            
            if (abs(dist) < 1000)
            {
                srcLine->update();
                tarLine->update();
                
                break;
            }
        }
    }
}


// public member method area ////////////////////////////////////



void ofApp::setup()
{
    //ofSetWindowShape(1024,768);
    
    //ofSetupOpenGL(ofGetScreenWidth(), ofGetScreenHeight(), OF_FULLSCREEN);
    
    ofToggleFullscreen();
    
    ofSetCircleResolution(100);
    
    ofBackground(0);
    
    ofSetBackgroundAuto(false);
    
    glLineWidth(1.0);
    
    ofSetSmoothLighting(true);
    //glEnable(GL_DEPTH_TEST);
    //glDisable(GL_CULL_FACE);
    
    initDefaultData();
}

void ofApp::update()
{
    JLLine *line;
    
    for (int i=0;i<lineList.size();i++)
    {
        line = lineList.at(i);
        
        //line->update();
    }
    
    checkRelation();
}

void ofApp::draw()
{
    JLLine *line;
    
    if (ofGetFrameNum() < 600)
    {
        for (int i=0;i<lineList.size();i++)
        {
            line = lineList.at(i);
            
            line->draw();
        }
    }
    
}

// public event handling area //////////////////////////////////

void ofApp::keyPressed(int key)
{
    
}


void ofApp::keyReleased(int key)
{
    
}


void ofApp::mouseMoved(int x, int y )
{
    
}


void ofApp::mouseDragged(int x, int y, int button)
{
    
}


void ofApp::mousePressed(int x, int y, int button)
{
    
}


void ofApp::mouseReleased(int x, int y, int button)
{
    
}


void ofApp::mouseEntered(int x, int y)
{
    
}


void ofApp::mouseExited(int x, int y)
{
    
}


void ofApp::windowResized(int w, int h)
{
    
}


void ofApp::gotMessage(ofMessage msg)
{
    
}


void ofApp::dragEvent(ofDragInfo dragInfo)
{
    
}
