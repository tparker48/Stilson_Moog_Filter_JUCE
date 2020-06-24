#pragma once

#include <JuceHeader.h>
#include "DumbSquare.h"
#include "StilsonMoogFilter.h"

#define JUCE_FILTER 0
#define STILSON_MOOG_FILTER 1

class MainComponent   : public AudioAppComponent
{
public:
    MainComponent();
    ~MainComponent();

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint (Graphics& g) override;
    void resized() override;

private:

    DumbSquare sqOsc1, sqOsc2;

    int filterMode;

    StilsonMoogFilter stilson;
    IIRFilter juceFilter;

    float cutoff, res, sat;

    Slider filterCutoff;
    Slider filterRes;
    Slider saturation;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};