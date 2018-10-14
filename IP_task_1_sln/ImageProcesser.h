#pragma once
#include <string>
#include "CImg.h"
#include <iostream>

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

	void changeBrightness();
	void horizontalFlip();
	void verticalFlip();
	void diagonalFlip();

	void medianFilter();

public:
	ImageProcesser(std::string imageName, int option, int value);
	~ImageProcesser();

	void processImage();
};

