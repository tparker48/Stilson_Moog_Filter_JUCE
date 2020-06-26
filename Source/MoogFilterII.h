/*
This class is an adaption of the Moog VCF variation 2, posted here:
https://www.musicdsp.org/en/latest/Filters/26-moog-vcf-variation-2.html

Comes from a Stilson/Smith CCRMA paper

added highpass and bandpass options
*/

#pragma once

#define LOWPASS 0
#define HIGHPASS 1
#define BANDPASS 2

#include <JuceHeader.h>

class MoogFilterII
{
public:
	void init(float sampleRate);
	void set(float cutoff, float resonance);
	float processSample(float in, int passMode);
	void processBlock(const AudioSourceChannelInfo& bufferToFill, int passMode);

private:
    float sampleRate;
	float cutoff, resonance;
	float out1, out2, out3, out4;
	float in1, in2, in3, in4;
};
