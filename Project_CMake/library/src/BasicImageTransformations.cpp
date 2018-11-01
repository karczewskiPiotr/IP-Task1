#include "ImageProcesser.h"

void ImageProcesser::changeBrightness(int modifier)
{
	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			image(x, y, 0) = truncate(image(x, y, 0) + modifier);
			image(x, y, 1) = truncate(image(x, y, 1) + modifier);
			image(x, y, 2) = truncate(image(x, y, 2) + modifier);
		}
	}
}

void ImageProcesser::changeToNegative()
{
	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			image(x, y, 0) = ~image(x, y, 0);
			image(x, y, 1) = ~image(x, y, 1);
			image(x, y, 2) = ~image(x, y, 2);
		}
	}
}

void ImageProcesser::changeContrast(int modifier)
{
	double factor = (259.0 * (modifier + 255.0)) / (255.0 * (259.0 - modifier));
	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			image(x, y, 0) = truncate((int)(factor * (image(x, y, 0) - 128) + 128));
			image(x, y, 1) = truncate((int)(factor * (image(x, y, 1) - 128) + 128));
			image(x, y, 2) = truncate((int)(factor * (image(x, y, 2) - 128) + 128));
		}
	}
}

void ImageProcesser::horizontalFlip()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width / 2; x++)
		{
			swapPixelsRGBValues(x, y, width - 1 - x, y);
		}
	}
}

void ImageProcesser::verticalFlip()
{
	for (int y = 0; y < height / 2; y++)
	{
		for (int x = 0; x < width; x++)
		{
			swapPixelsRGBValues(x, y, x, height - 1 - y);
		}
	}
}

void ImageProcesser::diagonalFlip()
{
	for (int y = 0; y < height / 2; y++)
	{
		for (int x = 0; x < width; x++)
		{
			swapPixelsRGBValues(x, y, width - 1 - x, height - 1 - y);
		}
	}
}

void ImageProcesser::shrinkImage(double modifier)
{
	unsigned int enlargedWidth = (unsigned int)(width / modifier);
	unsigned int enlargedHeight = (unsigned int)(height / modifier);
	double finalSum;
	cimg_library::CImg<unsigned char> enlargedImage(enlargedWidth, enlargedHeight, 1, 3, 0);
	int p1x, p1y, p2x, p2y, p3x, p3y, p4x, p4y;

	for (unsigned int y = 0; y < enlargedHeight; y++)
	{
		for (unsigned int x = 0; x < enlargedWidth; x++)
		{
			p1x = (int)(x * modifier);
			p1y = (int)(y * modifier);

			p2x = p1x + 1;
			p2y = p1y;

			p3x = p1x;
			p3y = p1y + 1;

			p4x = p1x + 1;
			p4y = p1y + 1;

			for (unsigned int channel = 0; channel < 3; channel++)
			{
				finalSum = 0.25*image(p1x, p1y, channel) + 0.25*image(p2x, p2y, channel) + 0.25*image(p3x, p3y, channel) + 0.25*image(p4x, p4y, channel);
				enlargedImage(x, y, channel) = truncate((int)finalSum);
			}
		}
	}

	image = enlargedImage;
}

void ImageProcesser::enlargeImage(double modifier)
{
	unsigned int enlargedWidth = (unsigned int)(width * modifier);
	unsigned int enlargedHeight = (unsigned int)(height * modifier);
	double sum1, sum2, finalSum, step = 1 / modifier;
	cimg_library::CImg<unsigned char> enlargedImage(enlargedWidth, enlargedHeight, 1, 3, 0);
	int p1x, p1y, p2x, p2y, p3x, p3y, p4x, p4y;

	for (unsigned int y = 0; y < enlargedHeight; y++)
	{
		for (unsigned int x = 0; x < enlargedWidth; x++)
		{
			if (step >= 1) step = 1 / modifier;
			p1x = (int)(x / modifier);
			p1y = (int)(y / modifier);

			p2x = p1x + 1;
			p2y = p1y;

			p3x = p1x;
			p3y = p1y + 1;

			p4x = p1x + 1;
			p4y = p1y + 1;

			for (unsigned int channel = 0; channel < 3; channel++)
			{
				sum1 = ((p2x - (p1x + step)) / (p2x - p1x)) * image(p1x, p1y, channel) + (((p1x + step) - p1x) / (p2x - p1x)) * image(p2x, p2y, channel);
				sum2 = ((p4x - (p3x + step)) / (p4x - p3x)) * image(p3x, p3y, channel) + (((p3x + step) - p3x) / (p4x - p3x)) * image(p4x, p4y, channel);
				finalSum = ((p3y - (p1y + step)) / (p3y - p1y)) * sum1 + (((p1y + step) - p1y) / (p3y - p1y)) * sum2;
				enlargedImage(x, y, channel) = truncate((int)finalSum);
			}

			step += 1 / modifier;
		}
	}

	image = enlargedImage;
}