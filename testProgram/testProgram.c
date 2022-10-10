#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "circBuf.h"
#include "iirFilter.h"
#include "deltaSigmaEncoder.h"
#define GAIN 0.713520160639131

int main()
{
	srand(time(0));
	FILE* inputFile = fopen("C:\\Users\\erroringons256\\Music\\oblivious_f64.raw", "rb");
	FILE* outputFile = fopen("C:\\Users\\erroringons256\\Music\\oblivious_f64f.raw", "wb");
	double* inputBuffer = malloc(1048576 * sizeof(double));
	char* outputBuffer = malloc(1048576 * sizeof(char));
	size_t xFilterSize[] = { 2 };
	size_t yFilterSize[] = { 1 };
	double xFilter[2] = { 2.0, -1.0 };
	double yFilter[1] = { 1.0 };
	iirFilterStream channel1;
	iirFilterStream channel2;
	iirFilterStream_init(&channel1, 1, xFilterSize, yFilterSize);
	iirFilterStream_init(&channel2, 1, xFilterSize, yFilterSize);
	iirFilter_setXFilter(channel1.filter, xFilter);
	iirFilter_setYFilter(channel1.filter, yFilter);
	iirFilter_setXFilter(channel2.filter, xFilter);
	iirFilter_setYFilter(channel2.filter, yFilter);
	if (!inputFile || !outputFile)
	{
		printf("Unable to open files!\n");
		return 1;
	}
	if (!inputBuffer || !outputBuffer)
	{
		printf("Unable to allocate buffer memory!\n");
		return 1;
	}
	
	size_t samplesRead;
	do
	{
		samplesRead = 2 * (fread(inputBuffer, sizeof(double), 1048576, inputFile) / 2);
		for (size_t i = 0; i < samplesRead; i += 2)
		{
			outputBuffer[i] = 1 + 254 * deltaSigmaEncode(&channel1, inputBuffer[i], GAIN);
			outputBuffer[i + 1] = 1 + 254 * deltaSigmaEncode(&channel2, inputBuffer[i + 1], GAIN);
		}
		fwrite(outputBuffer, sizeof(char), samplesRead, outputFile);
		
	} while (samplesRead != 0);
	free(inputBuffer);
	free(outputBuffer);
	fclose(inputFile);
	fclose(outputFile);
	return 0;
}