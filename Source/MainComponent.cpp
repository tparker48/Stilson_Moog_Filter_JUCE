#include "MainComponent.h"

MainComponent::MainComponent()
{
    setSize (600, 400);
    
    filterCutoff.setSliderStyle(Slider::LinearBarVertical);
    filterCutoff.setRange(50.0, MAX_CUTOFF_FREQ, 1.0);
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
    saturation.setTextValueSuffix(" saturation (stilson only)");
    saturation.setValue(.3);
    addAndMakeVisible(&saturation);

    addAndMakeVisible(filterSelect);
    filterSelect.addItem("No Filter (Loud)", NO_FILTER);
    filterSelect.addItem("Default JUCE Filter", JUCE_FILTER);
    filterSelect.addItem("Stilson Moog Filter", STILSON_MOOG_FILTER);
    filterSelect.addItem("Moog Filter 1", MOOG_FILTER_1);
    filterSelect.addItem("Moog Filter 2", MOOG_FILTER_2);
    filterSelect.addItem("Butterworth Filter", BUTTERWORTH_FILTER);
    filterSelect.setSelectedId(JUCE_FILTER);

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
    stilson.setSaturationAmount(0.5);

    butterworth.SetSampleRate((float)sampleRate);

    moog1.init((float)sampleRate);
    moog1.setCutoff(cutoff);
    moog1.setResonance(res);

    moog2.init((float)sampleRate);
    moog2.set(cutoff, res);

    filterMode = NO_FILTER;
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();

    sqOsc1.fillBlock(bufferToFill);
    sqOsc2.fillBlock(bufferToFill);

    filterMode = filterSelect.getSelectedId();

    // filter using specified mode
    switch (filterMode)
    {
    case JUCE_FILTER:
        juceFilter.processSamples(bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample), bufferToFill.buffer->getNumSamples());
        break;
    case STILSON_MOOG_FILTER:
        stilson.processBlock(bufferToFill, LOWPASS);
        break;
    case MOOG_FILTER_1:
        moog1.processBlock(bufferToFill, LOWPASS);
        break;
    case MOOG_FILTER_2:
        moog2.processBlock(bufferToFill, LOWPASS);
        break;
    case BUTTERWORTH_FILTER:
        butterworth.processBlock(bufferToFill);
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
    moog1.setCutoff(cutoff);
    moog1.setResonance(res);
    moog1.setSaturation(sat);
    moog2.set(cutoff, res);
    butterworth.Set(cutoff, res);
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
    filterSelect.setBounds(240, 50, 100, 20);
}