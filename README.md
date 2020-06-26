# Stilson's Moog Filter (JUCE) 
A collection of C++ classes implementing various filters. Built within/for the JUCE framework.

## Filters Currently Added:
1. Stilson's Moog Filter (https://www.musicdsp.org/en/latest/Filters/145-stilson-s-moog-filter-code.html)
2. Moog Filter 1 (https://www.musicdsp.org/en/latest/Filters/24-moog-vcf.html)
3. Moog Filter 2 (https://www.musicdsp.org/en/latest/Filters/26-moog-vcf-variation-2.html)
4. Butterworth Filter (https://www.musicdsp.org/en/latest/Filters/243-butterworth-optimized-c-class.html)

## Info
The JUCE project in this repo was built around testing the filters. Adding a particular filter to your own project only requires the .h and .cpp files corresponding to that filter.
  
- Building the test/example application requires a JUCE installation on your machine
- Adding the filter to your project is as simple as dragging <Filter Name>.h and <Filter Name>.cpp into your own JUCE project via Projucer
- Note: implemented for single channel (mono) only. The processBlock functions will filter channel 0 of the given AudioSampleBuffer.

## Usage (Stilson Moog Filter)
The usage is straighforward and can be seen in the MainComponent.h and MainComponent.cpp code.
- init(float sampleRate) must be called before you start using the filter
- setCutoff(float cutoff) adjusts the filter cutoff frequency
- setResonance(float resonance) adjusts the resonance (ranges from 0.0 to 1.0 inclusive)
- setSaturationAmount(float saturationAmount) adjusts amount of saturation (ranges from 0.0 to 1.0 inclusive)
- processBlock(const AudioSourceChannelInfo& bufferToFill, int passMode) applies the filter to the samples in bufferToFill
   - passMode = 0 for Lowpass, 1 for Highpass, and 2 for Bandpass

The other filters have very similair APIs. Looking at the respective header files should reveal how to initialize, set cutoff frequency, resonance, etc.

The usage for each filter is demonstrated in MainComponent.cpp .
