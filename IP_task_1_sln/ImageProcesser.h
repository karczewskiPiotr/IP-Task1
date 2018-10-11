#pragma once
#include <string>
#include "CImg.h"

class ImageProcesser
{
private:
	const char* imageName;
	std::string option;
	int value;
	
	void changeBrightness();
	//other methods
public:
	ImageProcesser(std::string imageName, std::string option, std::string value);
	~ImageProcesser();

	void processImage();
};

