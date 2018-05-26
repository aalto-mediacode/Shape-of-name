//
//  JLFish.cpp
//  test_flocking
//
//  Created by jlsy012 on 2018. 1. 29..
//

#include "JLFish.h"
#include <string.h>




//----------- publilc member method area -----------------

JLFish::JLFish(float x , float y , int width , int height)
{
    int fishNo;
    string fishName;
    
    fishNo = ofRandom(2,8);
    
    fishName = "fish0"+std::to_string(fishNo)+".png";
    
    imageFish.load(fishName);
    
    imageFish.resize(ofRandom(20,50), ofRandom(7,30));
    
    myWidth = width;
    myHeight = height;
    
    center.set(imageFish.getWidth()/2 , imageFish.getHeight()/2);
    
    radious = center.x/30;
    maxSpeed = 8;
    maxForce = 0.3;
    
    distNeighbor = 1;
    
    loc.set(x, y);
    acc.set(0,0);
    velocity.set(ofRandom(-5,5), ofRandom(-5,5));
    velocity *= ofRandom(0.8,3);
}

JLFish::~JLFish()
{
    ;
}

void JLFish::applyForce(int recvCount)
{
    distSum /= (float)recvCount;
    distSum = distSum.normalize();
    distSum *= maxSpeed;
    
    steer = (distSum - velocity);
    steer.limit(maxForce);
    
    acc += steer/4;
}

void JLFish::align(vector<JLFish *> *listFish)
{
    int count;
    float tempDist;
    
    count = 0;
    
    distSum.set(0);
    
    for (JLFish *fishFriend : *listFish)
    {
        tempDist = loc.distance(fishFriend->loc);
        
        if (tempDist > 0 && (tempDist < distNeighbor))
        {
            distSum += fishFriend->velocity;
            
            count++;
        }
    }
    
    if (count > 0)
    {
        applyForce(count);
    }
}

void JLFish::cohesion(vector<JLFish *> *listFish)
{
    float tempDist;
    float targetSeparation;
    int count;
    ofVec2f tempDiff;
    
    count = 0;
    
    distSum.set(0);
    
    targetSeparation = (radious * 50);
    
    for (JLFish *fishFriend : *listFish)
    {
        tempDist = loc.distance(fishFriend->loc);
        
        if (tempDist > targetSeparation)
        {
            tempDiff = (loc - fishFriend->loc);
            tempDiff.normalize();
            tempDiff *= -tempDist;
            distSum += tempDiff;
            count++;
        }
    }
    
    if (count > 0)
    {
        applyForce(count);
    }
}

void JLFish::separation(vector<JLFish *> *listFish)
{
    float tempDist;
    float targetSeparation;
    int count;
    ofVec2f tempDiff;
    
    count = 0;
    
    distSum.set(0);
    
    targetSeparation = (radious * 2);
    
    for (JLFish *fishFriend : *listFish)
    {
        tempDist = loc.distance(fishFriend->loc);
        
        if ( tempDist > 0 && tempDist < targetSeparation)
        {
            tempDiff = (loc - fishFriend->loc);
            tempDiff.normalize();
            tempDiff /= tempDist;
            distSum += tempDiff;
            count++;
        }
    }
    
    if (count > 0)
    {
        applyForce(count);
    }

}
void JLFish::update()
{
    velocity += acc;

    velocity.limit(maxSpeed);
    
    loc += velocity;
    
    acc *= 0;
}

void JLFish::checkBorders()
{
    if (loc.x < -radious)
    {
        loc.x = (myWidth+radious);
    }
    
    if (loc.y < -radious)
    {
        loc.y = (myHeight+radious);
    }
    
    if (loc.x > myWidth+radious)
    {
        loc.x = -radious;
    }
    
    if (loc.y > myHeight+radious)
    {
        loc.y = -radious;
    }
}

void JLFish::refresh()
{
    float angle;

    ofSetColor(100, 255, 255,50);
        
    angle = ofRadToDeg(atan2(velocity.y, velocity.x)) + 180;
    
    ofPushMatrix();
    
    ofTranslate(loc);
    
    ofDrawCircle(0,0, radious);
    
    ofPopMatrix();
}
