#pragma once
#include <string>
#include "CImg.h"
#include <iostream>

class ImageProcesser
{
private:
	std::string imageName;
	std::string option;
	int value;

	std::string errorMessageWrongFilename = "Image could not be loaded. Please check whether the filename is correct.";

	void changeBrightness();
	//other methods
public:
	ImageProcesser(std::string imageName, std::string option, int value);
	~ImageProcesser();

	void processImage();
};

