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
#pragma region HelperFunctions
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

CImg<unsigned char> ImageProcesser::getImageWithDuplicatedEdgeLines()
{
	CImg<unsigned char> temporaryImage(width + 2, height + 2, 1, 3, 0);

	//add additional lines (like a padding) to the image so that the edge elements are taken into account
	for (int x = 1; x < width; x++)
	{
		for (unsigned int channel = 0; channel < 3; channel++)
		{
			temporaryImage(x, 0, channel) = image(x - 1, 0, channel);
			temporaryImage(x, height + 1, channel) = image(x - 1, height - 1, channel);
		}
	}
	for (int y = 0; y <= height + 1; y++)
	{
		if (y == 0)
		{
			for (unsigned int channel = 0; channel < 3; channel++)
			{
				temporaryImage(0, 0, channel) = image(0, 0, channel);
				temporaryImage(width + 1, 0, channel) = image(width - 1, 0, channel);
			}
			continue;
		}

		for (unsigned int channel = 0; channel < 3; channel++)
		{
			temporaryImage(0, y, channel) = image(0, y - 1, channel);
			temporaryImage(width + 1, y, channel) = image(width - 1, y - 1, channel);
		}

		if (y == height + 1)
		{
			for (unsigned int channel = 0; channel < 3; channel++)
			{
				temporaryImage(0, height + 1, channel) = image(0, height - 1, channel);
				temporaryImage(width + 1, height + 1, channel) = image(width - 1, height - 1, channel);
			}
			continue;
		}
	}
	temporaryImage.draw_image(1, 1, image);

	return temporaryImage;
};
#pragma endregion

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

void ImageProcesser::medianFilter()
{

	CImg<unsigned char> temporaryImage = getImageWithDuplicatedEdgeLines();
	//iterate through the image in 3x3 windows (the pixel in the center will be the one that is changed)
	unsigned int ix = 0;
	unsigned int iy = 0;
	//extend this to channels
	for (unsigned int x = 1; x <= width; x++)
	{
		for (unsigned int y = 1; y <= height; y++)
		{
			//in every window, take the elements into an array
			unsigned char red[9] = {
				temporaryImage(x - 1, y - 1, 0),
				temporaryImage(x, y - 1, 0),
				temporaryImage(x + 1, y - 1, 0),
				temporaryImage(x - 1, y, 0),
				temporaryImage(x, y, 0),
				temporaryImage(x + 1, y, 0),
				temporaryImage(x - 1, y + 1, 0),
				temporaryImage(x, y + 1, 0),
				temporaryImage(x + 1, y + 1, 0)
			};
			unsigned char green[9] = {
				temporaryImage(x - 1, y - 1, 1),
				temporaryImage(x, y - 1, 1),
				temporaryImage(x + 1, y - 1, 1),
				temporaryImage(x - 1, y, 1),
				temporaryImage(x, y, 1),
				temporaryImage(x + 1, y, 1),
				temporaryImage(x - 1, y + 1, 1),
				temporaryImage(x, y + 1, 1),
				temporaryImage(x + 1, y + 1, 1)
			};
			unsigned char blue[9] = {
				temporaryImage(x - 1, y - 1, 2),
				temporaryImage(x, y - 1, 2),
				temporaryImage(x + 1, y - 1, 2),
				temporaryImage(x - 1, y, 2),
				temporaryImage(x, y, 2),
				temporaryImage(x + 1, y, 2),
				temporaryImage(x - 1, y + 1, 2),
				temporaryImage(x, y + 1, 2),
				temporaryImage(x + 1, y + 1, 2)
			};
			//sort these elements and take the middle value
			//the middle value is now the value of the pixel in the center
			size_t redSize = sizeof(red) / sizeof(*red);
			sort(red, red + redSize);
			size_t greenSize = sizeof(green) / sizeof(*green);
			sort(green, green + greenSize);
			size_t blueSize = sizeof(blue) / sizeof(*blue);
			sort(blue, blue + blueSize);
			image(ix, iy, 0) = red[4];
			image(ix, iy, 1) = green[4];
			image(ix, iy, 2) = blue[4];
			iy++;
		}
		iy = 0;
		ix++;
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
	case median:
		medianFilter();
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
