#ifndef CIRCBUF
#define CIRCBUF
#include <stddef.h>


#ifdef CIRCBUF_EXPORTS
#define CIRCBUF_API __declspec(dllexport)
#else
#define CIRCBUF_API __declspec(dllimport)
#endif

#ifndef CPREFIX
#ifdef __cplusplus
#define CPREFIX extern "C"
#else
#define CPREFIX
#endif
#endif

typedef struct circBuf_struct
{
	double* content;
	size_t offset;
	size_t mask;
} circBuf;

CPREFIX CIRCBUF_API char circBuf_init(circBuf* self, size_t length);
CPREFIX CIRCBUF_API double circBuf_getElement(circBuf* self, size_t n);
CPREFIX CIRCBUF_API void circBuf_setElement(circBuf* self, size_t n, double x);
CPREFIX CIRCBUF_API void circBuf_addToElement(circBuf* self, size_t n, double x);
CPREFIX CIRCBUF_API void circBuf_multiplyByElement(circBuf* self, size_t n, double x);
CPREFIX CIRCBUF_API void circBuf_roll(circBuf* self, size_t n);
CPREFIX CIRCBUF_API void circBuf_getBuffer(circBuf* self, double* out);
CPREFIX CIRCBUF_API void circBuf_setBuffer(circBuf* self, double* in);
CPREFIX CIRCBUF_API void circBuf_deinit(circBuf* self);

#endif