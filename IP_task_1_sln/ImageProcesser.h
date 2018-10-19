#pragma once
#include <string>
#include "CImg.h"
#include <iostream>
#include <vector>
#include <chrono>

class ImageProcesser
{
private:
	enum options
	{
		brightness = 2, contrast, negative, hflip, vflip, dflip, shrink, enlarge, min, max, median, mse, pmse, snr, psnr, md
	};

	std::string imageName;
	std::string noisyImageName;
	std::string denoisedImageName;

	int option;
	int value;

	cimg_library::CImg<unsigned char> image;
	unsigned short int height;
	unsigned short int width;

	void swapPixelsRGBValues(unsigned int x_1, unsigned int y_1, unsigned int x_2, unsigned int y_2);

	int truncate(int value);
	unsigned char getMedian(unsigned char* channelValues, size_t arraySize);
	unsigned char getMin(unsigned char* channelValues, size_t arraySize);
	unsigned char getMax(unsigned char* channelValues, size_t arraySize);

	void changeBrightness(int modifier);
	void changeToNegative();
	void changeContrast(int modifier);
	void shrinkImage(double modifier);
	void enlargeImage(double modifier);
	void horizontalFlip();
	void verticalFlip();
	void diagonalFlip();

	void medianFilter(int radius);
	void minFilter(int radius);
	void maxFilter(int radius);

public:
	ImageProcesser(std::string imageName, int option, int value, std::string noisyImageName, std::string denoisedImageName);
	~ImageProcesser();

	void processImage();
};

