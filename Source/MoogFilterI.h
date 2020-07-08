/*
The following code was taken from the following post:
https://www.musicdsp.org/en/latest/Filters/24-moog-vcf.html

A C++ class implementation of the filter was posted as a comment by moc.erehwon@tsaot.

That class was revised and added to for this implementation:
 - several variable names were changed for better readability
 - The processBlock function was added for easy use in JUCE projects.
 - Highpass and Bandpass filtering have been added as options
 - A saturation effect was applied. 
   (adapted from the saturation function in the StilsonMoogFilter class)
*/


#pragma once
#include <JuceHeader.h>

#define LOWPASS 0
#define HIGHPASS 1
#define BANDPASS 2

class MoogFilterI
{
public:
	void init(float sampleRate);
	
	void setCutoff(float cutoff);
	void setResonance(float resonance);
	
	// saturationAmount ranges [0..1] and is a dry/wet ratio
	// 0.0 will effectively turn off the saturation
	void setSaturation(float saturationAmount);

	void processBlock(const AudioSourceChannelInfo& bufferToFill, int passMode);

private:
	void calculateCoefficients();
	float process(float x, int passMode);
	float saturate(float input);

	float cutoff;
	float resonance;
	float saturationAmount;
	
	float sampleRate;
	float out1, out2, out3, out4;
	float in1, in2, in3, in4;

	// coefficients determined by cutoff and resonance
	float r, p, k;

	const float saturationLimit = 0.95;
};