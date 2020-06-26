/*
This code taken from the following post:
https://www.musicdsp.org/en/latest/Filters/24-moog-vcf.html

More specifically, the comment by moc.erehwon@tsaot, at 2007-02-05 17:22:24
which provided a C++ adaptation of the original post.

Other than adding the processBlock function, the original code was unchanged
*/

#include "MoogFilterI.h"

MoogFilterI::MoogFilterI()
{
	fs = 44100.0;

	init();
}

MoogFilterI::~MoogFilterI()
{
}

void MoogFilterI::init()
{
	// initialize values
	y1 = y2 = y3 = y4 = oldx = oldy1 = oldy2 = oldy3 = 0;
	calc();
};

void MoogFilterI::calc()
{
	float f = (cutoff + cutoff) / fs; //[0 - 1]
	p = f * (1.8f - 0.8f * f);
	k = p + p - 1.f;

	float t = (1.f - p) * 1.386249f;
	float t2 = 12.f + t * t;
	r = res * (t2 + 6.f * t) / (t2 - 6.f * t);
};

float MoogFilterI::process(float input)
{
	// process input
	x = input - r * y4;

	//Four cascaded onepole filters (bilinear transform)
	y1 = x * p + oldx * p - k * y1;
	y2 = y1 * p + oldy1 * p - k * y2;
	y3 = y2 * p + oldy2 * p - k * y3;
	y4 = y3 * p + oldy3 * p - k * y4;

	//Clipper band limited sigmoid
	y4 -= (y4 * y4 * y4) / 6.f;

	oldx = x; oldy1 = y1; oldy2 = y2; oldy3 = y3;
	return y4;
}

void MoogFilterI::processBlock(const AudioSourceChannelInfo& bufferToFill)
{
	int startSample = bufferToFill.startSample;
	int numSamples = bufferToFill.numSamples;
	AudioSampleBuffer* buffer = bufferToFill.buffer;

	for (int s = 0; s < numSamples; s++)
	{
		buffer->setSample(0, startSample + s, process(buffer->getSample(0, startSample + s)));
	}
}

float MoogFilterI::getCutoff()
{
	return cutoff;
}

void MoogFilterI::setCutoff(float c)
{
	cutoff = c; calc();
}

float MoogFilterI::getRes()
{
	return res;
}

void MoogFilterI::setRes(float r)
{
	res = r; calc();
}