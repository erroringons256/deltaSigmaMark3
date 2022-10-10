#ifndef DELTASIGMAENCODER
#define DELTASIGMAENCODER
#include "iirFilter.h"
#include "circBuf.h"

#ifdef DELTASIGMA_EXPORTS
#define DELTASIGMA_API __declspec(dllexport)
#else
#define DELTASIGMA_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
#endif
DELTASIGMA_API char deltaSigmaEncode(iirFilterStream* state, double sample, double signalGain);

#ifdef __cplusplus
extern "C"
#endif
DELTASIGMA_API double randDouble();

#endif