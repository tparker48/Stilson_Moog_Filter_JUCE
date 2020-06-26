/*
This class is an adaption of the Moog VCF variation 2, posted here:
https://www.musicdsp.org/en/latest/Filters/26-moog-vcf-variation-2.html

Comes from a Stilson/Smith CCRMA paper
*/

#include "MoogFilterII.h"

void MoogFilterII::init()
{
	out1 = 0.0f;
	out2 = 0.0f;
	out3 = 0.0f;
	out4 = 0.0f;
	in1 = 0.0f;
	in2 = 0.0f;
	in3 = 0.0f;
	in4 = 0.0f;
}

// Set coefficients given frequency & resonance [0.0...1.0]
void MoogFilterII::set(float cutoff, float resonance)
{
	cutoff = cutoff / 5000.0f;
	resonance = resonance * 4.0f;
	this->cutoff = cutoff;
	this->resonance = resonance;
}


// Filter (in [-1.0...+1.0])
float MoogFilterII::processSample(float input)
{
	float f = cutoff * 1.16;
	float fb = resonance * (1.0 - 0.15 * f * f);
	input -= out4 * fb;
	input *= 0.35013 * (f * f) * (f * f);
	out1 = input + 0.3 * in1 + (1 - f) * out1; // Pole 1
	in1 = input;
	out2 = out1 + 0.3 * in2 + (1 - f) * out2;  // Pole 2
	in2 = out1;
	out3 = out2 + 0.3 * in3 + (1 - f) * out3;  // Pole 3
	in3 = out2;
	out4 = out3 + 0.3 * in4 + (1 - f) * out4;  // Pole 4
	in4 = out3;
	return out4;
}

void MoogFilterII::processBlock(const AudioSourceChannelInfo& bufferToFill)
{
	int startSample = bufferToFill.startSample;
	int numSamples = bufferToFill.numSamples;
	AudioSampleBuffer* buffer = bufferToFill.buffer;

	for (int s = 0; s < numSamples; s++)
	{
		buffer->setSample(0, startSample + s, processSample(buffer->getSample(0, startSample + s)));
	}
}