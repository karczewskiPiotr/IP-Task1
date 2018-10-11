#include "pch.h"
#include "ImageProcesser.h"

using namespace cimg_library;
using namespace std;

void ImageProcesser::changeBrightness()
{
}

ImageProcesser::ImageProcesser(std::string imageName, std::string option, std::string value = "")
	:imageName(imageName.c_str()), option(option), value(stoi(value))
{
}

ImageProcesser::~ImageProcesser()
{
}

void ImageProcesser::processImage()
{
};
