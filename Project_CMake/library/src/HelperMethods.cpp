#include "ImageProcesser.h"

void ImageProcesser::swapPixelsRGBValues(unsigned int x_1, unsigned int y_1, unsigned int x_2, unsigned int y_2)
{
	unsigned char temp;
	for (unsigned int channel = 0; channel < 3; channel++)
	{
		temp = image(x_1, y_1, channel);
		image(x_1, y_1, channel) = image(x_2, y_2, channel);
		image(x_2, y_2, channel) = temp;
	}
}

int ImageProcesser::truncate(int value)
{
	if (value < 0) return 0;
	if (value > 255) return 255;

	return value;
}

unsigned char ImageProcesser::getMedian(unsigned char* channelValues, size_t arraySize)
{
	std::sort(channelValues, channelValues + arraySize);
	if (arraySize % 2 == 0)
	{
		return (channelValues[(arraySize / 2) - 1] + channelValues[arraySize / 2]) / 2;
	}
	else
	{
		return channelValues[arraySize / 2];
	}
}

unsigned char ImageProcesser::getMin(unsigned char* channelValues, size_t size)
{
	unsigned char smallest = channelValues[0];
	for (unsigned short int i = 1; i < size; i++)
	{
		if (channelValues[i] < smallest) smallest = channelValues[i];
	}
	return smallest;
}

unsigned char ImageProcesser::getMax(unsigned char* channelValues, size_t size)
{
	unsigned char highest = channelValues[0];
	for (unsigned short int i = 1; i < size; i++)
	{
		if (channelValues[i] > highest) highest = channelValues[i];
	}
	return highest;
}
