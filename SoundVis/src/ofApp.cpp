#include "ofApp.h"


//----------------------   private member method area   ------------------

void ofApp::initDefaultData()
{
    imageSaved = false;
    
    displayWidth = (ofGetScreenHeight()/1.5)/2;
    
    scrWidth = ofGetScreenWidth();
    scrHeight = ofGetScreenHeight();

    calcString();
    
    createParticles();
}

void ofApp::calcString()
{
    int totalPoint;
    int speed;
    float dist;
    float scale;
    string text;
    
    text = "Thu";
    
    totalPoint = 0;
    
    speed = text.length();
    
    for (int i=0;i<text.length();i++)
    {
        totalPoint += text[i]*1.5;
    }
    
    dist = (totalPoint / text.length());
    
    scale = text[0] + text[text.length()-1];
}

void ofApp::saveImage()
{
    int startPos;
    
    startPos = ofGetWidth()/2-displayWidth;
    
    image.grabScreen(0, 0,ofGetWidth(), ofGetHeight());
    
    image.save(text+".png");
    
    //ofSaveImage(image.getPixels(),text+".jpg",OF_IMAGE_QUALITY_BEST);
}

void ofApp::createParticles()
{
    int temp1,temp2;
    int totalPoint,speed;
    float dist,scale,distScale;
    JLParticle *temp;
    ofColor c1,c2;
    ofPoint pos;
    
    text = "Tisra";
    
    totalPoint = 0;
    
    speed = text.length();
    
    distScale = ofMap(displayWidth,300,700,1.3,0.8);
    
    for (int i=0;i<text.length();i++)
    {
        totalPoint += text[i]*6;
    }
    
    stopFrameCount = totalPoint/15;
    
    dist = (totalPoint / (text.length()*((text.length()*distScale))));
    
    scale = totalPoint/1000.0;
    
    temp1 = text[0];
    temp2 = temp1;
    
    if (text.length() > 0)
    {
        temp2 = text[text.length()-1];
    }
    
    temp2 = ofMap((temp1),32,90,0,360);
    temp1 = (temp2+180);
    
    if (temp1 > 360)
    {
        temp1 -= 360;
    }
    
    c1 = ofColor::fromHsb(0, 255, 255);
    c2 = ofColor::fromHsb(0, 255, 255);
    
    c1.setHueAngle(temp1);
    c2.setHueAngle(temp2);
    
    for (int i=0;i<NUM_OF_PARTICLES;i++)
    {
        temp = new JLParticle(c1,c2,dist,speed,totalPoint,scale);
        
        pos.set(ofRandom(scrWidth) , ofRandom(scrHeight));
        
        temp->setup();
        temp->setOrgPos(pos);
        
        myParticles.push_back(*temp);
    }
}

void ofApp::checkConnettion()
{
    int tempCount;
    bool connected;
    
    ofSetColor(255,30);
    
    tempCount = myParticles.size();
    
    for (int i=0;i<tempCount;i++)
    {
        for (int j=i;j<tempCount;j++)
        {
            connected = myParticles[i].isConnected(myParticles[j].getcurPos());
            
            if (connected == true)
            {
                ofDrawLine(myParticles[i].getcurPos(),myParticles[j].getcurPos());
            }
        }
    }
}

//----------------------   public member method area    ------------------

void ofApp::setup()
{
    //ofSetWindowShape(1024,768);
    
    ofToggleFullscreen();
    
    myFont.load("ITCAvantGardePro-Bk.otf", 10,true,true,true,0);
    
    ofBackground(0);
    
    ofSetBackgroundAuto(false);
    
    initDefaultData();
}

//--------------------------------------------------------------
void ofApp::update()
{
    for (int i=0;i<myParticles.size();i++)
    {
        myParticles[i].update();
    }
    
}

//--------------------------------------------------------------
void ofApp::draw()
{
    if (stopFrameCount*2 >= ofGetFrameNum())
    {
        checkConnettion();
        
        for (int i=0;i<myParticles.size();i++)
        {
            myParticles[i].draw();
        }
        
        ofSetColor(0);
        
        ofDrawRectangle(0,0,ofGetWidth()/2-displayWidth , ofGetHeight());
        ofDrawRectangle(ofGetWidth()/2+displayWidth , 0 , ofGetWidth() , ofGetHeight());
    }
    else
    {
        if (imageSaved == false)
        {
            saveImage();
            
            imageSaved = true;
        }
        
        //image.draw(0,0);
        
        ofSetColor(255);
        
        myFont.drawStringAsShapes(text,ofGetWidth()/2+displayWidth+100, ofGetHeight()-20);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
    
}
