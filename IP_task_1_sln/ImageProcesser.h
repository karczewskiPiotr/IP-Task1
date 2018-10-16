#pragma once
#include <string>
#include "CImg.h"
#include <iostream>

class ImageProcesser
{
private:
	enum options
	{
		brightness = 2, contrast, negative, hflip, vflip, dflip, shrink, enlarge, min, max, media, mse, pmse, snr, psnr, md
	};

	std::string imageName;
	int option;
	int value;

	cimg_library::CImg<unsigned char> image;
	unsigned int height;
	unsigned int width;

	std::string errorMessageWrongFilename = "Image could not be loaded. Please check whether the filename is correct.";

	void swapPixelsRGBValues(unsigned int x_1, unsigned int y_1, unsigned int x_2, unsigned int y_2);

	int truncate(int value);

	void changeBrightness(int modifier);
	void changeToNegative();
	void changeContrast(int modifier);
	void shrinkImage(double modifier);
	void enlargeImage(double modifier);
	void horizontalFlip();
	void verticalFlip();
	void diagonalFlip();

public:
	ImageProcesser(std::string imageName, int option, int value);
	~ImageProcesser();

	void processImage();
};

