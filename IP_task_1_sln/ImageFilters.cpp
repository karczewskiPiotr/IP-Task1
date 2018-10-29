#include "ImageProcesser.h"

void ImageProcesser::minFilter(int radius)
{
	if (radius == 0) return;
	unsigned short int channels = image.spectrum();
	cimg_library::CImg<unsigned char> imageCopy = image;
	struct Window
	{
		short int x0;
		short int x1;
		short int y0;
		short int y1;
	};

	Window window;
	unsigned short int x;
	unsigned short int y;
	unsigned short int channel;
	unsigned short int i;
	unsigned short int j;
	unsigned short int index;
	for (x = 0; x < width; x++)
	{
		window.x0 = x - radius;
		window.x1 = x + radius;

		if (window.x0 < 0)
		{
			window.x0 = 0;
		}
		else if (window.x1 > width - 1)
		{
			window.x1 = width - 1;
		}

		for (y = 0; y < height; y++)
		{
			window.y0 = y - radius;
			window.y1 = y + radius;
			if (window.y0 < 0)
			{
				window.y0 = 0;
			}
			else if (window.y1 > height - 1)
			{
				window.y1 = height - 1;
			}

			for (channel = 0; channel < channels; channel++)
			{
				size_t arraySize = (window.x1 - window.x0 + 1) * (window.y1 - window.y0 + 1);
				unsigned char* channelValues = new unsigned char[arraySize];
				index = 0;
				for (i = window.x0; i <= window.x1; i++)
				{
					for (j = window.y0; j <= window.y1; j++)
					{
						channelValues[index] = image(i, j, channel);
						index++;
					}
				}
				imageCopy(x, y, channel) = getMin(channelValues, arraySize);
				delete[] channelValues;
			}
		}
	}
	image = imageCopy;
}

void ImageProcesser::maxFilter(int radius)
{
	if (radius == 0) return;
	unsigned short int channels = image.spectrum();
	cimg_library::CImg<unsigned char> imageCopy = image;
	struct Window
	{
		short int x0;
		short int x1;
		short int y0;
		short int y1;
	};

	Window window;
	unsigned short int x;
	unsigned short int y;
	unsigned short int channel;
	unsigned short int i;
	unsigned short int j;
	unsigned short int index;
	for (x = 0; x < width; x++)
	{
		window.x0 = x - radius;
		window.x1 = x + radius;

		if (window.x0 < 0)
		{
			window.x0 = 0;
		}
		else if (window.x1 > width - 1)
		{
			window.x1 = width - 1;
		}

		for (y = 0; y < height; y++)
		{
			window.y0 = y - radius;
			window.y1 = y + radius;
			if (window.y0 < 0)
			{
				window.y0 = 0;
			}
			else if (window.y1 > height - 1)
			{
				window.y1 = height - 1;
			}

			for (channel = 0; channel < channels; channel++)
			{
				size_t arraySize = (window.x1 - window.x0 + 1) * (window.y1 - window.y0 + 1);
				unsigned char* channelValues = new unsigned char[arraySize];
				index = 0;
				for (i = window.x0; i <= window.x1; i++)
				{
					for (j = window.y0; j <= window.y1; j++)
					{
						channelValues[index] = image(i, j, channel);
						index++;
					}
				}
				imageCopy(x, y, channel) = getMax(channelValues, arraySize);
				delete[] channelValues;
			}
		}
	}
	image = imageCopy;
}

void ImageProcesser::medianFilter(int radius)
{
	if (radius == 0) return;
	unsigned short int channels = image.spectrum();
	cimg_library::CImg<unsigned char> imageCopy = image;
	struct Window
	{
		short int x0;
		short int x1;
		short int y0;
		short int y1;
	};

	Window window;
	unsigned short int x;
	unsigned short int y;
	unsigned short int channel;
	unsigned short int i;
	unsigned short int j;
	unsigned short int index;
	for (x = 0; x < width; x++)
	{
		window.x0 = x - radius;
		window.x1 = x + radius;

		if (window.x0 < 0)
		{
			window.x0 = 0;
		}
		else if (window.x1 > width - 1)
		{
			window.x1 = width - 1;
		}

		for (y = 0; y < height; y++)
		{
			window.y0 = y - radius;
			window.y1 = y + radius;
			if (window.y0 < 0)
			{
				window.y0 = 0;
			}
			else if (window.y1 > height - 1)
			{
				window.y1 = height - 1;
			}

			for (channel = 0; channel < channels; channel++)
			{
				size_t arraySize = (window.x1 - window.x0 + 1) * (window.y1 - window.y0 + 1);
				unsigned char* channelValues = new unsigned char[arraySize];
				index = 0;
				for (i = window.x0; i <= window.x1; i++)
				{
					for (j = window.y0; j <= window.y1; j++)
					{
						channelValues[index] = image(i, j, channel);
						index++;
					}
				}

				imageCopy(x, y, channel) = getMedian(channelValues, arraySize);
				delete[] channelValues;
			}
		}
	}
	image = imageCopy;
}
