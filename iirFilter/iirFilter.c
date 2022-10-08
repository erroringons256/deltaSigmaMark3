#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "circBuf.h"
#include "iirFilter.h"

char iirFilter_init(iirFilter* self, size_t xFilterLength, size_t yFilterLength) // Allocates all memory used by iirFilter struct and subsequently initialises struct with default values. (Identity filter + 0s in all buffers)
{
	if (xFilterLength > ((size_t)-1 / sizeof(double)) ||
		yFilterLength > ((size_t)-1 / sizeof(double)) ||
		!xFilterLength ||
		!yFilterLength)
	{
		return 1; 
	}
	self->xFilter = malloc(sizeof(double) * xFilterLength);
	self->yFilter = malloc(sizeof(double) * yFilterLength);
	if (!self->xFilter ||
		!self->yFilter)
	{
		iirFilter_deinit(self); // No need to use a reference here, since the variable passed is already a pointer
		return 1;
	}
	self->xFilterLength = xFilterLength;
	self->yFilterLength = yFilterLength;

	self->xFilter[0] = 1.0;
	self->yFilter[0] = 1.0;

	for (size_t i = 1; i < self->xFilterLength; i++)
	{
		self->xFilter[i] = 0.0;
	}
	for (size_t i = 1; i < self->yFilterLength; i++)
	{
		self->yFilter[i] = 0.0;
	}
	return 0;
}

void iirFilter_deinit(iirFilter* self) // Frees all dynamic memory used by iirFilter struct + deinits all circBufs
{
	free(self->xFilter);
	free(self->yFilter);
}

void iirFilter_setXFilter(iirFilter* self, double* xFilter) // Convenience function for setting the xFilter attribute
{
	memcpy(self->xFilter, xFilter, sizeof(double) * self->xFilterLength);
}

void iirFilter_setYFilter(iirFilter* self, double* yFilter) // Convenience function for setting the yFilter attribute
{
	memcpy(self->yFilter, yFilter, sizeof(double) * self->yFilterLength);
}