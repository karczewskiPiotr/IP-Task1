#include "pch.h"
#include "ImageProcesser.h"
#include "ArgumentsHandler.h"

using namespace cimg_library;
using namespace std;

ImageProcesser::ImageProcesser(std::string imageName, int option, int value)
	:imageName(imageName), option(option), value(value)
{
}

ImageProcesser::~ImageProcesser()
{
}

#pragma region Functions

void ImageProcesser::changeBrightness()
{
}

#pragma endregion

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

	switch (option)
	{
	case brightness:
		break;
	case contrast:

		break;
	case negative:
		std::cout << "WORKS" << std::endl;
		break;
	case hflip:

		break;
	case vflip:

		break;
	case dflip:
		
		break;
	case shrink:

		break;
	case enlarge:

		break;
	case min:

		break;
	case max:

		break;
	case media:

		break;
	case mse:
		
		break;
	case pmse:

		break;
	case snr:

		break;
	case psnr:

		break;
	case md:

		break;
	default:
		break;
	}

	cimg_library::CImg<unsigned char> processedImage = image;
	//Shows image in separate window
	image.display("zdjontko", false, 0, true);
	processedImage.save("file.bmp"); // a tak se mo¿na zapisaæ jako bmp
};
