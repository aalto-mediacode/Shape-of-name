//
//  JLFish.hpp
//  test_flocking
//
//  Created by jlsy012 on 2018. 1. 29..
//

#include "ofMain.h"


class JLFish
{
    
    
    
private:
    
    ofVec2f loc;
    ofVec2f velocity;
    ofVec2f center;
    ofVec2f acc;
    ofVec2f steer;
    ofVec2f distSum;
    ofImage imageFish;
    
    float radious;
    float maxForce;
    float maxSpeed;
    float distNeighbor;
    
    int myWidth;
    int myHeight;
    
    
    
public:
    
    JLFish(float x , float y , int width , int height);
    ~JLFish();
    void update();
    void refresh();
    void align(vector<JLFish *> *listFish);
    void cohesion(vector<JLFish *> *listFish);
    void separation(vector<JLFish *> *listFish);
    void applyForce(int recvCount);
    void checkBorders();
    
    
    
    
    
    
    
    
    
    
    
    ;
    
    
    
    
    
};
