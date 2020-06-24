# Stilson's Moog Filter (JUCE) 
A C++ class implementing Tim Stilson's Moog Filter. Built within/for the JUCE framework.

## Info
The JUCE project in this repo was built around testing the filter. The relevant files are StilsonMoogFilter.h and StilsonMoogFilter.cpp

- The code for the filter was based on the following post from musicdsp.org :
  - https://www.musicdsp.org/en/latest/Filters/145-stilson-s-moog-filter-code.html
  
- Building the test/example application would require a JUCE installation on your machine
- Adding the filter to your project is as simple as dragging StilsonMoogFilter.h and StilsonMoogFilter.cpp into your own JUCE project via Projucer
- Note: implemented for single channel only

## Usage
The usage is straighforward and can be seen in the MainComponent.h and MainComponent.cpp code.
- init(float sampleRate) must be called before you start using the filter
- setCutoff(float cutoff) adjusts the filter cutoff frequency
- setResonance(float resonance) adjusts the resonance (ranges from 0.0 to 1.0 inclusive)
- setSaturationAmount(float saturationAmount) adjusts amount of saturation (ranges from 0.0 to 1.0 inclusive)
- processBlock(const AudioSourceChannelInfo& bufferToFill, int passMode) applies the filter to the samples in bufferToFill
   - passMode = 0 for Lowpass, 1 for Highpass, and 2 for Bandpass

