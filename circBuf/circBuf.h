#ifndef CIRCBUF
#define CIRCBUF
#include <stddef.h>


#ifdef CIRCBUF_EXPORTS
#define CIRCBUF_API __declspec(dllexport)
#else
#define CIRCBUF_API __declspec(dllimport)
#endif

typedef struct circBuf_struct
{
	double* content;
	size_t offset;
	size_t mask;
} circBuf;

#ifdef __cplusplus
extern "C"
#endif
CIRCBUF_API char circBuf_init(circBuf*, size_t);

#ifdef __cplusplus
extern "C"
#endif
CIRCBUF_API double circBuf_getElement(circBuf*, size_t);

#ifdef __cplusplus
extern "C"
#endif
CIRCBUF_API void circBuf_setElement(circBuf*, size_t, double);

#ifdef __cplusplus
extern "C"
#endif
CIRCBUF_API void circBuf_addToElement(circBuf*, size_t, double);

#ifdef __cplusplus
extern "C"
#endif
CIRCBUF_API void circBuf_multiplyByElement(circBuf*, size_t, double);

#ifdef __cplusplus
extern "C"
#endif
CIRCBUF_API void circBuf_roll(circBuf*, size_t);

#ifdef __cplusplus
extern "C"
#endif
CIRCBUF_API void circBuf_getBuffer(circBuf*, double*);

#ifdef __cplusplus
extern "C"
#endif
CIRCBUF_API void circBuf_setBuffer(circBuf*, double*);

#ifdef __cplusplus
extern "C"
#endif
CIRCBUF_API void circBuf_deinit(circBuf*);

#endif