#ifndef IIRFILTER
#define IIRFILTER
#include "circBuf.h"
#include "stddef.h"

#ifdef IIRFILTER_EXPORTS
#define IIRFILTER_API __declspec(dllexport)
#else
#define IIRFILTER_API __declspec(dllimport)
#endif

#ifndef CPREFIX
#ifdef __cplusplus
#define CPREFIX extern "C"
#else
#define CPREFIX
#endif
#endif

// iirFilter.c
typedef struct iirFilter_struct
{
	double* xFilter;
	double* yFilter;
	size_t xFilterLength;
	size_t yFilterLength;
} iirFilter;


CPREFIX IIRFILTER_API char iirFilter_init(iirFilter* self, size_t xFilterLength, size_t yFilterLength);
CPREFIX IIRFILTER_API void iirFilter_deinit(iirFilter* self);
CPREFIX IIRFILTER_API void iirFilter_setXFilter(iirFilter* self, double* xFilter);
CPREFIX IIRFILTER_API void iirFilter_setYFilter(iirFilter* self, double* yFilter);

// iirFilterStream.c
typedef struct iirFilterStream_struct
{
	size_t filterNum;
	iirFilter* filter;
	circBuf* xState;
	circBuf* yState;
} iirFilterStream;

CPREFIX IIRFILTER_API char iirFilterStream_init(iirFilterStream* self, size_t filterNum, size_t* xFilterLength, size_t* yFilterLength);
CPREFIX IIRFILTER_API void iirFilterStream_deinit(iirFilterStream* self);
CPREFIX IIRFILTER_API double iirFilterStream_compute(iirFilterStream* self, double inputSample);
CPREFIX IIRFILTER_API void iirFilterStream_repeatedCompute(iirFilterStream*, size_t signalLength, double* inputSample, double* outputSample);

#endif 