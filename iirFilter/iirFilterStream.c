#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "circBuf.h"
#include "iirFilter.h"

char iirFilterStream_init(iirFilterStream* self, size_t filterNum, size_t* xFilterLength, size_t* yFilterLength) // Allocates and initialises memory used by iirFilterStream struct, the iirFilter structs, and the circBufs for intermediate values.
{
	if (!filterNum ||
		!xFilterLength ||
		!yFilterLength ||
		filterNum > (size_t)-1 / sizeof(iirFilter) ||
		filterNum > (size_t)-1 / sizeof(circBuf))
	{
		return 1;
	}
	self->filter = malloc(filterNum * sizeof(iirFilter));
	self->xState = malloc(filterNum * sizeof(circBuf));
	self->yState = malloc(filterNum * sizeof(circBuf));
	if (!self->filter || !self->xState || !self->yState)
	{
		return 1;
	}
	self->filterNum = filterNum;
	size_t errorCount = 0;
	for (size_t i = 0; i < filterNum; i++)
	{
		errorCount += iirFilter_init(self->filter + i, xFilterLength[i], yFilterLength[i]);
		errorCount += circBuf_init(self->xState + i, xFilterLength[i]);
		errorCount += circBuf_init(self->yState + i, yFilterLength[i]);
	}
	if (errorCount > 0)
	{
		iirFilterStream_deinit(self);
		return 1;
	}
	return 0;
}

void iirFilterStream_deinit(iirFilterStream* self) // Deinitialises all filters used by iirFilterChain, then deallocates all memory used by the struct itself
{
	for (size_t i = 0; i < self->filterNum; i++)
	{
		iirFilter_deinit(self->filter + i);
	}
	free(self->filter);
}

double iirFilterStream_compute(iirFilterStream* self, double inputSample)
{
	// Shift circBuf and write input into first iirFilters' xState
	circBuf_roll(self->xState, self->xState[0].mask); // mask is size-1, so shifting by that will result in every sample being shifted one to the back of the buffer.
	circBuf_roll(self->yState, self->yState[0].mask);
	circBuf_setElement(self->xState, 0, inputSample);
	circBuf_setElement(self->yState, 0, 0.0);
	
	// Compute yState of iirFilter, then copy it into the next xState
	for (size_t j = 0; j < self->filterNum - 1; j++)
	{
		for (size_t k = 0; k < self->filter[j].xFilterLength; k++)
		{
			circBuf_addToElement(self->yState + j, 0, self->filter[j].xFilter[k] * circBuf_getElement(self->xState + j, k));
		}
		for (size_t k = 1; k < self->filter[j].yFilterLength; k++)
		{
			circBuf_addToElement(self->yState + j, 0, -self->filter[j].yFilter[k] * circBuf_getElement(self->yState + j, k));
		}
		circBuf_multiplyByElement(self->yState + j, 0, 1.0 / self->filter[j].yFilter[0]);
		circBuf_roll(self->xState + j + 1, self->xState[j + 1].mask);
		circBuf_roll(self->yState + j + 1, self->yState[j + 1].mask);
		circBuf_setElement(self->xState + j + 1, 0, circBuf_getElement(self->yState + j, 0));
		circBuf_setElement(self->yState + j + 1, 0, 0.0);
	}

	// Perform last filter computation (this needs to be done separately, as the result gets copied into the output buffer rather than the next filters' xState
	for (size_t k = 0; k < self->filter[self->filterNum - 1].xFilterLength; k++)
	{
		circBuf_addToElement(self->yState + self->filterNum - 1, 0, self->filter[self->filterNum - 1].xFilter[k] * circBuf_getElement(self->xState + self->filterNum - 1, k));
	}
	for (size_t k = 1; k < self->filter[self->filterNum - 1].yFilterLength; k++)
	{
		circBuf_addToElement(self->yState + self->filterNum - 1, 0, -self->filter[self->filterNum - 1].yFilter[k] * circBuf_getElement(self->yState + self->filterNum - 1, k));
	}
	circBuf_multiplyByElement(self->yState + self->filterNum - 1, 0, 1.0 / self->filter[self->filterNum - 1].yFilter[0]);
	return circBuf_getElement(self->yState + self->filterNum - 1, 0);
}

void iirFilterStream_repeatedCompute(iirFilterStream* self, size_t signalLength, double* inputSample, double* outputSample)
{
	for (size_t i = 0; i < signalLength; i++)
	{
		outputSample[i] = iirFilterStream_compute(self, inputSample[i]);
	}
}