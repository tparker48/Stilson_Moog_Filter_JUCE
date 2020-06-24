#pragma once
#include <JuceHeader.h>

// Simple Square Wav Osc to test with various filter types...

class DumbSquare
{
public:
    void init(float fs);
    void fillBlock(const AudioSourceChannelInfo& bufferToFill);
    void setFrequency(float hz);
    void setGain(float gain);

private:
    float sqWave(float angle);
    void updateTheta();

    float theta, delta, twoPi, sampleRate;
    float gain;
};