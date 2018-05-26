//
//  sound.m
//  soundvis
//
//  Created by jlsy012 on 2017. 12. 13..
//

#include "sound.h"


//--------- private member method area ----------------//



//--------- public member method area -----------------//

void JLSound::setup()
{
    bands = 512;
    
    smoothScale = 100;
    
    fftSmooth     = new float[8192];
    prevFftSmooth = new float[8192];
    
    for (int i=0;i<8192;i++)
    {
        fftSmooth[i] = 0;
        
        prevFftSmooth[i] = 0;
    }
    
    mySound.load("test.mp3");
    
    mySound.setLoop(true);
    
    mySound.play();
}


void JLSound::update()
{
    float *value;
    
    ofSoundUpdate();
    
    value = ofSoundGetSpectrum(bands);
    
    for (int i=0;i<bands;i++)
    {
        fftSmooth[i] *= smoothScale;
        
        //if ( fftSmooth[i] < value[i])
        {
            fftSmooth[i] = value[i] * smoothScale;
        }
    }
}

float * JLSound::getFFT()
{
//    for (int i=0;i<bands;i++)
//    {
//        fftSmooth[i] = (fftSmooth[i]*100 - prevFftSmooth[i]);
//
//        prevFftSmooth[i] = fftSmooth[i];
//    }
    
    return fftSmooth;
}

void JLSound::draw()
{
    ;
}
