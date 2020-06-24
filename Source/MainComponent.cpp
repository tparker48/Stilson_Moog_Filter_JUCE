#include "MainComponent.h"

MainComponent::MainComponent()
{
    setSize (300, 400);

    filterCutoff.setSliderStyle(Slider::LinearBarVertical);
    filterCutoff.setRange(50.0, 4000.0, 1.0);
    filterCutoff.setSkewFactorFromMidPoint(1000);
    filterCutoff.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    filterCutoff.setPopupDisplayEnabled(true, false, this);
    filterCutoff.setTextValueSuffix(" filter cutoff (Hz)");
    filterCutoff.setValue(1.0);
    addAndMakeVisible(&filterCutoff);

    filterRes.setSliderStyle(Slider::LinearBarVertical);
    filterRes.setRange(0.01, 1.0, 0.01);
    filterRes.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    filterRes.setPopupDisplayEnabled(true, false, this);
    filterRes.setTextValueSuffix(" filter resonance (Hz)");
    filterRes.setValue(.3);
    addAndMakeVisible(&filterRes);

    saturation.setSliderStyle(Slider::LinearBarVertical);
    saturation.setRange(0.0, 1.0, 0.01);
    saturation.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    saturation.setPopupDisplayEnabled(true, false, this);
    saturation.setTextValueSuffix(" filter saturation amount");
    saturation.setValue(.3);
    addAndMakeVisible(&saturation);

    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }
    else
    {
        setAudioChannels (0, 1);
    }
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    cutoff = filterCutoff.getValue();

    sqOsc1.init((float)sampleRate);
    sqOsc1.setGain(0.5f);
    sqOsc1.setFrequency(80.0f);

    sqOsc2.init((float)sampleRate);
    sqOsc2.setGain(0.5f);
    sqOsc2.setFrequency(180.0f);

    stilson.init((float)sampleRate);
    stilson.setCutoff(cutoff);
    stilson.setResonance(1.0);
    stilson.setSaturationAmount(1.0);

    filterMode = STILSON_MOOG_FILTER;
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();

    sqOsc1.fillBlock(bufferToFill);
    sqOsc2.fillBlock(bufferToFill);

    // filter using specified mode
    switch (filterMode)
    {
    case JUCE_FILTER:
        juceFilter.processSamples(bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample), bufferToFill.buffer->getNumSamples());
        break;
    case STILSON_MOOG_FILTER:
        stilson.processBlock(bufferToFill, BANDPASS);
        break;
    default:
        break;
    }
    
    // get resonance and cutoff from GUI sliders
    cutoff = filterCutoff.getValue();
    res = filterRes.getValue();
    sat = saturation.getValue();

    // update resonance and cutoff for all the filters
    stilson.setCutoff(cutoff);
    stilson.setResonance(res);
    stilson.setSaturationAmount(sat);
    juceFilter.setCoefficients(IIRCoefficients::makeLowPass(44100, cutoff, res));
}

void MainComponent::releaseResources()
{
}


void MainComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setColour(Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Filter test", 0, 0, getWidth(), 30, Justification::centred, 1);
}

void MainComponent::resized()
{
    filterCutoff.setBounds(40, 30, 40, getHeight() - 60);
    filterRes.setBounds(90, 30, 40, getHeight() - 60);
    saturation.setBounds(140, 30, 40, getHeight() - 60);
}
