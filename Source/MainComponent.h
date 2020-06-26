#pragma once

#include <JuceHeader.h>
#include "DumbSquare.h"
#include "StilsonMoogFilter.h"
#include "MoogFilterI.h"
#include "MoogFilterII.h"
#include "ButterworthFilter.h"

#define NO_FILTER 1
#define JUCE_FILTER 2
#define STILSON_MOOG_FILTER 3
#define MOOG_FILTER_1 4
#define MOOG_FILTER_2 5
#define BUTTERWORTH_FILTER 6

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

    StilsonMoogFilter stilson;
    MoogFilterI moog1;
    MoogFilterII moog2;
    ButterworthFilter butterworth;
    IIRFilter juceFilter;
    
    const float MAX_CUTOFF_FREQ = 5000.0;
    
    // Filter Parameters
    int filterMode;
    int filterSelection;
    float cutoff, res, sat;

    // GUI
    Slider filterCutoff;
    Slider filterRes;
    Slider saturation;
    ComboBox filterSelect;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};