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
	int option;
	int value;

	cimg_library::CImg<unsigned char> image;
	unsigned int height;
	unsigned int width;

	std::string errorMessageWrongFilename = "Image could not be loaded. Please check whether the filename is correct.";

	void swapPixelsRGBValues(unsigned int x_1, unsigned int y_1, unsigned int x_2, unsigned int y_2);
	cimg_library::CImg<unsigned char> getImageWithDuplicatedEdgeLines();

	int truncate(int value);
	unsigned char getMedian(std::vector<unsigned char> &channelValues);

	void changeBrightness(int modifier);
	void changeToNegative();
	void changeContrast(int modifier);
	void enlargeImage(double modifier);
	void horizontalFlip();
	void verticalFlip();
	void diagonalFlip();

	void medianFilter(int radius);

public:
	ImageProcesser(std::string imageName, int option, int value);
	~ImageProcesser();

	void processImage();
};

