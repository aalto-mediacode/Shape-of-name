//
//  particle.h
//  soundvis
//
//  Created by jlsy012 on 2018.05.15
//

#pragma once

#define APPROX_DIST 20

#include "ofMain.h"

class JLParticle
{
    
    //--------- private member property area---------------//
    
    
private:
    

    float noiseScale;
    float curApproxDist;
    float curSpeed;
    float curScale1;
    float curScale2;
    float colorAlpha;
    
    ofPoint orgPos;
    ofPoint curPos;
    ofPoint targetPos;
    ofPoint curAcc;
    ofColor startColor;
    ofColor endColor;
    ofColor curColor;
    
    
    bool shouldGo;
    
    
    
    //--------- public member property area ---------------//
    
    //--------- private member method area ----------------//
    
    void initDefaultData();
    void move();
    
    //--------- public member method area -----------------//
    
    
public:
    
    JLParticle(ofColor c1, ofColor c2, float dist, float speed , float scale1, float scale2);
    
    void setup();
    void setOrgPos(ofPoint pos);
    void setTargetPos(ofPoint pos);
    void setTargetPos2(ofPoint pos);
    void setAcc(ofPoint acc);
    void update();
    void draw();
    bool isConnected(ofPoint &destPos);
    ofPoint& getcurPos();
    
    
};
