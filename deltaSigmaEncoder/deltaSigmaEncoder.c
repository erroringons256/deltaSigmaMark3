#include "circBuf.h"
#include "iirFilter.h"
#include "deltaSigmaEncoder.h"
#include <stdlib.h>

char deltaSigmaEncode(iirFilterStream* state, double sample, double signalGain)
{
	double u = signalGain * sample - circBuf_getElement(state->yState, 0);
	char y = (u + randDouble()) >= 0;
	iirFilterStream_compute(state, 2.0 * (double)y - 1.0 - u);
	return y;
}

double randDouble()
{
	return (2.0 / RAND_MAX) * (double)rand() - 1;
}