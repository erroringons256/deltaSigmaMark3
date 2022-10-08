#ifndef IIRFILTER
#define IIRFILTER
#include "circBuf.h"
#include "stddef.h"

#ifdef IIRFILTER_EXPORTS
#define IIRFILTER_API __declspec(dllexport)
#else
#define IIRFILTER_API __declspec(dllimport)
#endif

// iirFilter.c
typedef struct iirFilter_struct
{
	double* xFilter;
	double* yFilter;
	size_t xFilterLength;
	size_t yFilterLength;
} iirFilter;

#ifdef __cplusplus
extern "C"
#endif
IIRFILTER_API char iirFilter_init(iirFilter*, size_t, size_t);

#ifdef __cplusplus
extern "C"
#endif
IIRFILTER_API void iirFilter_deinit(iirFilter*);

#ifdef __cplusplus
extern "C"
#endif
IIRFILTER_API void iirFilter_setXFilter(iirFilter*, double*);

#ifdef __cplusplus
extern "C"
#endif
IIRFILTER_API void iirFilter_setYFilter(iirFilter*, double*);

// iirFilterStream.c
typedef struct iirFilterStream_struct
{
	size_t filterNum;
	iirFilter* filter;
	circBuf* xState;
	circBuf* yState;
} iirFilterStream;

#ifdef __cplusplus
extern "C"
#endif
IIRFILTER_API char iirFilterStream_init(iirFilterStream*, size_t, size_t*, size_t*);

#ifdef __cplusplus
extern "C"
#endif
IIRFILTER_API void iirFilterStream_deinit(iirFilterStream*);

#ifdef __cplusplus
extern "C"
#endif
IIRFILTER_API double iirFilterStream_compute(iirFilterStream*, double);

#ifdef __cplusplus
extern "C"
#endif
IIRFILTER_API void iirFilterStream_repeatedCompute(iirFilterStream*, size_t, double*, double*);

#endif