#include "pch.h"
#include "ImageProcesser.h"

using namespace cimg_library;
using namespace std;

void ImageProcesser::changeBrightness()
{
}

ImageProcesser::ImageProcesser(std::string imageName, std::string option, int value)
	:imageName(imageName), option(option), value(value)
{
}

ImageProcesser::~ImageProcesser()
{
}

void ImageProcesser::processImage()
{
	cimg_library::CImg<unsigned char> image; // wczytuje zdjêcie podane przez ludzia
	try
	{
		image.load(imageName.c_str());
	}
	catch (CImgException)
	{
		image.assign();
		cout << endl << errorMessageWrongFilename << endl;
	}

	if (!image) return;

	cimg_library::CImg<unsigned char> processedImage = image;
	//Shows image in separate window
	image.display("zdjontko", false, 0, true);
	processedImage.save("file.bmp"); // a tak se mo¿na zapisaæ jako bmp
};
