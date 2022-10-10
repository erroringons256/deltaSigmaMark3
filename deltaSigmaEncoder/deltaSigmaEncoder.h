#ifndef DELTASIGMAENCODER
#define DELTASIGMAENCODER
#include "iirFilter.h"
#include "circBuf.h"

#ifdef DELTASIGMA_EXPORTS
#define DELTASIGMA_API __declspec(dllexport)
#else
#define DELTASIGMA_API __declspec(dllimport)
#endif

#ifndef CPREFIX
#ifdef __cplusplus
#define CPREFIX extern "C"
#else
#define CPREFIX
#endif
#endif

//deltaSigmaEncoder.c
CPREFIX DELTASIGMA_API char deltaSigmaEncode(iirFilterStream* state, double sample, double signalGain);
CPREFIX DELTASIGMA_API double randDouble();

#endif