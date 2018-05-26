//
//  JLLine.hpp
//  line1
//
//  Created by jlsy012 on 2018. 4. 28..
//

#ifndef JLLine_hpp
#define JLLine_hpp

#include <stdio.h>
#include "ofMain.h"


class JLLine
{
    
// private member property area /////////////////////////////////
    
private:
    
    ofPoint curPos;
    ofColor color;
    int length;
    float halfLength;
    float curAngle;

// public member property area //////////////////////////////////

// private member method area ///////////////////////////////////
    
private:
    
    void initDefaultData();

// public member method area ////////////////////////////////////
    
public:
    
     JLLine();
     ~JLLine();
    
    void setPosition(ofPoint &pos);
    void setPosition(int x,int y);
    void setLength(int recvLength);
    void setAngle(float angle);
    ofPoint getCurPosition();
    void update();
    void draw();
    
    
    

// public event handling area //////////////////////////////////
    
};

#endif /* JLLine_hpp */
