//
//  particle.m
//  soundvis
//
//  Created by jlsy012 on 2017. 12. 13..
//

#include "JLParticle.h"




//--------- private member method area ----------------//


void JLParticle::initDefaultData()
{
    shouldGo = true;
}

void JLParticle::move()
{
    ofPoint temp;
    
    temp = (targetPos - curPos)/7;//.normalize();
    
    //temp = (curPos - orgPos);//.normalize();
    
    curPos += temp;
    
    ofSetColor(255,70);
    
    //ofDrawRectangle(curPos,5,5);
    //ofDrawEllipse(curPos,2,2);
}


//--------- public member method area -----------------//

JLParticle::JLParticle(ofColor c1, ofColor c2, float dist, float speed , float scale1, float scale2)
{
    curApproxDist = dist;
    curSpeed = speed/2;
    curScale1 = scale1/10;
    curScale2 = ofMap(scale2,0,2,0.000001,1.5);
    startColor = c1;
    endColor   = c2;
    
    colorAlpha = 2;//ofMap(((ofGetScreenHeight()/1.5)/2),300,700,1,3);
    
    noiseScale = (curScale2/(curScale1*2));
    
    //noiseScale = 0.002;
}

void JLParticle::setup()
{
    ofSetColor(255);
    
    initDefaultData();
}

void JLParticle::setOrgPos(ofPoint pos)
{
    orgPos.set(pos);
    curPos.set(pos);
    targetPos.set(pos);
}

void JLParticle::setTargetPos(ofPoint pos)
{
    pos = (orgPos + pos);
 
    targetPos.set(pos);
}

void JLParticle::setTargetPos2(ofPoint pos)
{
    targetPos.set(pos);
}

void JLParticle::setAcc(ofPoint acc)
{
    curAcc.set(acc);
}

ofPoint& JLParticle::getcurPos()
{
    return curPos;
}

bool JLParticle::isConnected(ofPoint &destPos)
{
    float dist,t;
    bool connected;
  
    connected = false;
    
    dist = curPos.distance(destPos);
    
    if (dist <= curApproxDist)
    {
        t = ofMap(dist , 0, curApproxDist , 0,1);
        
        curColor = startColor.getLerped(endColor,t);
        
        colorAlpha = ofMap(dist , 0, curApproxDist , 2,4);
        
        ofSetColor(curColor,colorAlpha);
        
        connected = true;
    }

    return connected;
}

void JLParticle::update()
{
    float angle;
    
    angle = (ofNoise(curPos.x * noiseScale , curPos.y * noiseScale) * curScale1) * curScale2;
    
    angle = ofDegToRad(angle);
    
    curPos.x += cos(angle) * curSpeed;
    curPos.y += sin(angle) * curSpeed;
    
    //curPos.y -= (curSpeed/2);
    
    if (curPos.x < 0 || curPos.x > ofGetWidth() || curPos.y < 0 || curPos.y > ofGetHeight())
    {
        //shouldGo = false;
        
        curPos.set(ofRandom(ofGetWidth()) , ofRandom(ofGetHeight()));
    }
}

void JLParticle::draw()
{
    if (shouldGo == true)
    {
        ofSetColor(curColor,10);
        //ofDrawEllipse(curPos.x,curPos.y,10,10);
    }
}
