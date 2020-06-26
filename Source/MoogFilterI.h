/*
This code taken from the following post:
https://www.musicdsp.org/en/latest/Filters/24-moog-vcf.html

More specifically, the comment by moc.erehwon@tsaot, at 2007-02-05 17:22:24
which provided a C++ adaptation of the original post.

Other than adding the processBlock function, the original code was unchanged
*/

#pragma once
#include <JuceHeader.h>

class MoogFilterI
{
public:
	MoogFilterI();
	void init();
	void calc();
	float process(float x);
	void processBlock(const AudioSourceChannelInfo& bufferToFill);
	~MoogFilterI();
	float getCutoff();
	void setCutoff(float c);
	float getRes();
	void setRes(float r);

protected:
	float saturate(float input);

	float cutoff;
	float res;
	float fs;
	float y1, y2, y3, y4;
	float oldx;
	float oldy1, oldy2, oldy3;
	float x;
	float r;
	float p;
	float k;
};