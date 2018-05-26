//
//  JLLine.cpp
//  line1
//
//  Created by jlsy012 on 2018. 4. 28..
//

#include "JLLine.h"


// private member method area ///////////////////////////////////

void JLLine::initDefaultData()
{
    curAngle = 0;
    
    color.set(255,255,255,2);
    
    //color.setHsb(255, 255, 100,128);
}

// public member method area ////////////////////////////////////

JLLine::JLLine()
{
    initDefaultData();
}

JLLine::~JLLine()
{
    ;
}

void JLLine::setLength(int recvLength)
{
    length = recvLength;
    
    halfLength = (length/2.0);
}

void JLLine::setPosition(ofPoint &pos)
{
    curPos.set(pos);
    
    ofLog()<< curPos;
}

void JLLine::setPosition(int x,int y)
{
    curPos.set(x,y);
    
    ofLog()<< curPos;
}

void JLLine::setAngle(float angle)
{
    curAngle = angle;
}

ofPoint JLLine::getCurPosition()
{
    return curPos;
}

void JLLine::update()
{
    curAngle += ofRandom(-1,1);
    
    curPos.x += ofRandom(-2,2);
    curPos.y += ofRandom(-2,2);
    
    //color.setHueAngle(curAngle);
}

void JLLine::draw()
{
    ofSetColor(color);
    
    ofPushMatrix();
    
    ofTranslate(curPos);
    
    ofRotateZ(curAngle);
    
    ofDrawLine(-halfLength, 0, +halfLength, 0);
    
    ofDrawCircle(0, 0, 1);
    
    ofPopMatrix();
}



// public event handling area //////////////////////////////////


