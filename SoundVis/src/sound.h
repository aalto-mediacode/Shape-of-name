//
//  sound.h
//  soundvis
//
//  Created by jlsy012 on 2017. 12. 13..
//

#pragma once

#include "ofMain.h"

class JLSound
{
    
    //--------- private member property area---------------//
    
private:
    
    
    ofSoundPlayer mySound;
    

    float *fftSmooth;
    float *prevFftSmooth;
    float smoothScale;
    int bands;
    
    //--------- public member property area ---------------//
    
    
    
    //--------- private member method area ----------------//
    
    
    
    //--------- public member method area -----------------//
    
public:
    
    void setup();
    void update();
    void draw();
    
    float *getFFT();
    
};
