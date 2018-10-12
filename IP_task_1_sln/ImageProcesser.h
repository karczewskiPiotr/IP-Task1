#pragma once
#include <string>
#include "CImg.h"
#include <iostream>

class ImageProcesser
{
private:
	enum options
	{
		brightness = 1, contrast, negative = 4, hflip, vflip, dflip, shrink, enlarge, min, max, media, mse, pmse, snr, psnr, md
	};

	std::string imageName;
	int option;
	int value;

	std::string errorMessageWrongFilename = "Image could not be loaded. Please check whether the filename is correct.";

	void changeBrightness();
	//other methods
public:
	ImageProcesser(std::string imageName, int option, int value);
	~ImageProcesser();

	void processImage();
};

