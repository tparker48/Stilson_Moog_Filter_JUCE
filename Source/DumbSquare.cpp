#include "DumbSquare.h"

void DumbSquare::init(float fs)
{
    twoPi = 2.0 * MathConstants<float>::pi;
    sampleRate = fs;
    float hz = 440;

    float cyclesPerSample = hz / sampleRate;
    delta = cyclesPerSample * twoPi;
    theta = 0.0;
}

void DumbSquare::fillBlock(const AudioSourceChannelInfo& bufferToFill)
{
    int numSamples = bufferToFill.numSamples;
    int startSample = bufferToFill.startSample;
    AudioSampleBuffer* buffer = bufferToFill.buffer;

    for (int s = 0; s < numSamples; s++)
    {
        for (int chan = 0; chan < buffer->getNumChannels(); chan++)
        {
            buffer->setSample(chan, startSample + s, buffer->getSample(chan,startSample+s) + gain*sqWave(theta));
        }
        updateTheta();
    }
}

void DumbSquare::setFrequency(float hz)
{
    float cyclesPerSample = hz / sampleRate;
    delta = cyclesPerSample * twoPi;
}

void DumbSquare::setGain(float gain)
{
    this->gain = gain;
}

float DumbSquare::sqWave(float angle)
{
    if (sin(angle) >= 0) return 1.0;
    else return -1.0;
}

void DumbSquare::updateTheta()
{
    theta += delta;
    if (theta >= twoPi) theta -= twoPi;
}