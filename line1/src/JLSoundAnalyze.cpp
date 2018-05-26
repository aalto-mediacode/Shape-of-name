//
//  JLSoundAnalyzer
//  JLSoundAnalyzer
//
//  Created by jlsy012 on 2017. 12. 13..
//

#include "JLSoundAnalyzer.h"


//--------- private member method area ----------------//



//--------- public member method area -----------------//

JLSoundAnalyzer::JLSoundAnalyzer()
{
    initDefaultData();
}

JLSoundAnalyzer::~JLSoundAnalyzer()
{
    delete fftSmooth;
    delete prevFftSmooth;
}

void JLSoundAnalyzer::initDefaultData()
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
}

void JLSoundAnalyzer::loadSong(string fileName)
{
    mySound.load(fileName);
    
    mySound.setLoop(false);
    
    //mySound.play();
}

void JLSoundAnalyzer::update()
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

float * JLSoundAnalyzer::getFFT()
{
//    for (int i=0;i<bands;i++)
//    {
//        fftSmooth[i] = (fftSmooth[i]*100 - prevFftSmooth[i]);
//
//        prevFftSmooth[i] = fftSmooth[i];
//    }
    
    return fftSmooth;
}

void JLSoundAnalyzer::draw()
{
    ;
}
