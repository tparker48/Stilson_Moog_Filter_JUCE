/*
This class is an adaption of the Moog VCF variation 2, posted here:
https://www.musicdsp.org/en/latest/Filters/26-moog-vcf-variation-2.html

Comes from a Stilson/Smith CCRMA paper
*/

#pragma once
#include <JuceHeader.h>

class MoogFilterII
{
public:
	void init(float sampleRate);
	void set(float cutoff, float resonance);
	float processSample(float in);
	void processBlock(const AudioSourceChannelInfo& bufferToFill);

private:
    float sampleRate;
	float cutoff, resonance;
	float out1, out2, out3, out4;
	float in1, in2, in3, in4;
};
