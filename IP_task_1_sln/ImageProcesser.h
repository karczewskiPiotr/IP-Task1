#pragma once
#include <string>
#include "CImg.h"

class ImageProcesser
{
private:
	void changeBrightness();
	//other methods
public:
	ImageProcesser();
	~ImageProcesser();

	void processImage(string imageName, std::string option, std::string value = "");
};

