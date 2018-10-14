#include "pch.h"
#include "ImageProcesser.h"

using namespace cimg_library;
using namespace std;

ImageProcesser::ImageProcesser(std::string imageName, int option, int value)
	:imageName(imageName), option(option), value(value)
{
}

ImageProcesser::~ImageProcesser()
{
}

void ImageProcesser::swapPixelsRGBValues(unsigned int x_1, unsigned int y_1, unsigned int x_2, unsigned int y_2)
{
	unsigned char temp;
	for (unsigned int channel = 0; channel < 3; channel++)
	{
		temp = image(x_1, y_1, channel);
		image(x_1, y_1, channel) = image(x_2, y_2, channel);
		image(x_2, y_2, channel) = temp;
	}
}

#pragma region Functions

void ImageProcesser::changeBrightness()
{
}

void ImageProcesser::horizontalFlip()
{
	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width / 2; x++)
		{
			swapPixelsRGBValues(x, y, width - 1 - x, y);
		}
	}
}

void ImageProcesser::verticalFlip()
{
	for (unsigned int y = 0; y < height / 2; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			swapPixelsRGBValues(x, y, x, height - 1 - y);
		}
	}
}

void ImageProcesser::diagonalFlip()
{
	for (unsigned int y = 0; y < height / 2; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			swapPixelsRGBValues(x, y, width - 1 - x, height - 1 - y);
		}
	}
}
#pragma endregion

void ImageProcesser::processImage()
{
	cimg_library::CImg<unsigned char> initialImage;
	try
	{
		initialImage.load(imageName.c_str());
	}
	catch (CImgException)
	{
		cout << endl << errorMessageWrongFilename << endl;
	}

	if (!initialImage) return;
	image = initialImage;
	height = image.height();
	width = image.width();

	switch (option)
	{
	case brightness:
		break;
	case contrast:

		break;
	case negative:
		break;
	case hflip:
		horizontalFlip();
		break;
	case vflip:
		verticalFlip();
		break;
	case dflip:
		diagonalFlip();
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

	image.display("Processed image preview", false);
	image.save("processedImage.bmp");
};
