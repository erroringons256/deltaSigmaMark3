#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "circBuf.h"
static size_t smallestPowerOf2GreaterOrEqualThan(size_t);

char circBuf_init(circBuf* self, size_t size)
{
	self->mask = smallestPowerOf2GreaterOrEqualThan(size) - 1;
	if (self->mask >= (size_t)-1 / sizeof(double))
	{
		return 1;
	}
	self->content = malloc(sizeof(double) * (self->mask + 1));
	if (!self->content)
	{
		return 1;
	}
	self->offset = 0;
	for (size_t i = 0; i < self->mask + 1; i++)
	{
		self->content[i] = 0.0;
	}
	return 0;
}

double circBuf_getElement(circBuf* self, size_t n)
{
	return self->content[self->mask & (n + self->offset)];
}

void circBuf_setElement(circBuf* self, size_t n, double x)
{
	self->content[self->mask & (n + self->offset)] = x;
}

void circBuf_addToElement(circBuf* self, size_t n, double x)
{
	self->content[self->mask & (n + self->offset)] += x;
}

void circBuf_multiplyByElement(circBuf* self, size_t n, double x)
{
	self->content[self->mask & (n + self->offset)] *= x;
}

void circBuf_roll(circBuf* self, size_t n)
{
	self->offset = (self->offset + n) & self->mask;
}

void circBuf_getBuffer(circBuf* self, double* out)
{
	memcpy(out, self->content + self->offset, (self->mask - self->offset + 1) * sizeof(double));
	memcpy(out + self->mask - self->offset + 1, self->content, self->offset * sizeof(double));
}

void circBuf_setBuffer(circBuf* self, double* in)
{
	memcpy(self->content, in, (self->mask + 1) * sizeof(double));
	self->offset = 0;
}

void circBuf_deinit(circBuf* self)
{
	free(self->content);
}

static size_t smallestPowerOf2GreaterOrEqualThan(size_t n)
{
	size_t y = 1;
	while (y < n && y != 0) // 0 is the result of an overflow
	{
		y *= 2;
	}
	return y;
}