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

int ImageProcesser::truncate(int value)
{
	if (value < 0) return 0;
	if (value > 255) return 255;

	return value;
}

unsigned char ImageProcesser::getMedian(unsigned char* channelValues, size_t arraySize)
{
	sort(channelValues, channelValues + arraySize);
	if (arraySize % 2 == 0)
	{
		return (channelValues[(arraySize / 2) - 1] + channelValues[arraySize / 2]) / 2;
	}
	else
	{
		return channelValues[arraySize / 2];
	}
}

unsigned char ImageProcesser::getMin(unsigned char* channelValues, size_t size)
{
	unsigned char smallest = channelValues[0];
	for (unsigned short int i = 1; i < size; i++)
	{
		if (channelValues[i] < smallest) smallest = channelValues[i];
	}
	return smallest;
}

unsigned char ImageProcesser::getMax(unsigned char* channelValues, size_t size)
{
	unsigned char highest = channelValues[0];
	for (unsigned short int i = 1; i < size; i++)
	{
		if (channelValues[i] > highest) highest = channelValues[i];
	}
	return highest;
}
#pragma endregion

#pragma region Functions

void ImageProcesser::changeBrightness(int modifier)
{
	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			image(x, y, 0) = truncate(image(x, y, 0) + modifier);
			image(x, y, 1) = truncate(image(x, y, 1) + modifier);
			image(x, y, 2) = truncate(image(x, y, 2) + modifier);
		}
	}
}

void ImageProcesser::changeToNegative()
{
	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			image(x, y, 0) = ~image(x, y, 0);
			image(x, y, 1) = ~image(x, y, 1);
			image(x, y, 2) = ~image(x, y, 2);
		}
	}
}

void ImageProcesser::changeContrast(int modifier)
{
	double factor = (259.0 * (modifier + 255.0)) / (255.0 * (259.0 - modifier));
	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			image(x, y, 0) = truncate((int)(factor * (image(x, y, 0) - 128) + 128));
			image(x, y, 1) = truncate((int)(factor * (image(x, y, 1) - 128) + 128));
			image(x, y, 2) = truncate((int)(factor * (image(x, y, 2) - 128) + 128));
		}
	}
}

void ImageProcesser::enlargeImage(double modifier)
{
	unsigned int enlargedWidth = width * modifier;
	unsigned int enlargedHeight = height * modifier;
	float step = 1 / modifier;
	cimg_library::CImg<unsigned char> enlargedImage(enlargedWidth, enlargedHeight, 1, 3, 0);

	for (unsigned int x = 0; x < enlargedWidth; x++)
	{
		for (unsigned int y = 0; y < enlargedHeight; y++)
		{
			if (step == 1) step = 1 / modifier;
			//px, py - coordinates of upper left pixel (of 4 adjecent pixels) in the original image
			int p1x = x / modifier;
			int p1y = y / modifier;

			//positions of 3 neighboring pixels
			int p2x = p1x + 1;
			int p2y = p1y;

			int p3x = p1x;
			int p3y = p1y + 1;

			int p4x = p1x + 1;
			int p4y = p1y + 1;

			// p1x,p1y	p2x,p2y
			// p3x,p3y	p4x,p4y

			for (unsigned int channel = 0; channel < 3; channel++)
			{
				float sum1 = ((p2x - (p1x + step)) / (p2x - p1x)) * image(p1x, p1y, channel) + (((p1x + step) - p1x) / (p2x - p1x)) * image(p2x, p2y, channel);
				float sum2 = ((p4x - (p3x + step)) / (p4x - p3x)) * image(p3x, p3y, channel) + (((p3x + step) - p3x) / (p4x - p3x)) * image(p4x, p4y, channel);
				float finalSum = ((p3y - (p1y + step)) / (p3y - p1y)) * sum1 + (((p1y + step) - p1y) / (p3y - p1y)) * sum2;
				enlargedImage(x, y, channel) = truncate((int)finalSum);
			}

			step += 1 / modifier;
		}
	}
	enlargedImage.display("Processed image preview", false);
	enlargedImage.save("enlargedImage.bmp");
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

void ImageProcesser::minFilter(int radius)
{
	if (radius == 0) return;
	unsigned short int channels = image.spectrum();
	CImg<unsigned char> imageCopy = image;
	struct Window
	{
		short int x0;
		short int x1;
		short int y0;
		short int y1;
	};

	Window window;
	unsigned short int x;
	unsigned short int y;
	unsigned short int channel;
	unsigned short int i;
	unsigned short int j;
	unsigned short int index;
	for (x = 0; x < width; x++)
	{
		window.x0 = x - radius;
		window.x1 = x + radius;

		if (window.x0 < 0)
		{
			window.x0 = 0;
		}
		else if (window.x1 > width - 1)
		{
			window.x1 = width - 1;
		}

		for (y = 0; y < height; y++)
		{
			window.y0 = y - radius;
			window.y1 = y + radius;
			if (window.y0 < 0)
			{
				window.y0 = 0;
			}
			else if (window.y1 > height - 1)
			{
				window.y1 = height - 1;
			}

			for (channel = 0; channel < channels; channel++)
			{
				size_t arraySize = (window.x1 - window.x0 + 1) * (window.y1 - window.y0 + 1);
				unsigned char* channelValues = new unsigned char[arraySize];
				index = 0;
				for (i = window.x0; i <= window.x1; i++)
				{
					for (j = window.y0; j <= window.y1; j++)
					{
						channelValues[index] = image(i, j, channel);
						index++;
					}
				}
				imageCopy(x, y, channel) = getMin(channelValues, arraySize);
				delete[] channelValues;
			}
		}
	}
	image = imageCopy;
}

void ImageProcesser::maxFilter(int radius)
{
	if (radius == 0) return;
	unsigned short int channels = image.spectrum();
	CImg<unsigned char> imageCopy = image;
	struct Window
	{
		short int x0;
		short int x1;
		short int y0;
		short int y1;
	};

	Window window;
	unsigned short int x;
	unsigned short int y;
	unsigned short int channel;
	unsigned short int i;
	unsigned short int j;
	unsigned short int index;
	for (x = 0; x < width; x++)
	{
		window.x0 = x - radius;
		window.x1 = x + radius;

		if (window.x0 < 0)
		{
			window.x0 = 0;
		}
		else if (window.x1 > width - 1)
		{
			window.x1 = width - 1;
		}

		for (y = 0; y < height; y++)
		{
			window.y0 = y - radius;
			window.y1 = y + radius;
			if (window.y0 < 0)
			{
				window.y0 = 0;
			}
			else if (window.y1 > height - 1)
			{
				window.y1 = height - 1;
			}

			for (channel = 0; channel < channels; channel++)
			{
				size_t arraySize = (window.x1 - window.x0 + 1) * (window.y1 - window.y0 + 1);
				unsigned char* channelValues = new unsigned char[arraySize];
				index = 0;
				for (i = window.x0; i <= window.x1; i++)
				{
					for (j = window.y0; j <= window.y1; j++)
					{
						channelValues[index] = image(i, j, channel);
						index++;
					}
				}
				imageCopy(x, y, channel) = getMax(channelValues, arraySize);
				delete[] channelValues;
			}
		}
	}
	image = imageCopy;
}

void ImageProcesser::medianFilter(int radius)
{
	if (radius == 0) return;
	unsigned short int channels = image.spectrum();
	CImg<unsigned char> imageCopy = image;
	struct Window
	{
		short int x0;
		short int x1;
		short int y0;
		short int y1;
	};

	Window window;
	unsigned short int x;
	unsigned short int y;
	unsigned short int channel;
	unsigned short int i;
	unsigned short int j;
	unsigned short int index;
	for (x = 0; x < width; x++)
	{
		window.x0 = x - radius;
		window.x1 = x + radius;

		if (window.x0 < 0)
		{
			window.x0 = 0;
		}
		else if (window.x1 > width - 1)
		{
			window.x1 = width - 1;
		}

		for (y = 0; y < height; y++)
		{
			window.y0 = y - radius;
			window.y1 = y + radius;
			if (window.y0 < 0)
			{
				window.y0 = 0;
			}
			else if (window.y1 > height - 1)
			{
				window.y1 = height - 1;
			}

			for (channel = 0; channel < channels; channel++)
			{
				size_t arraySize = (window.x1 - window.x0 + 1) * (window.y1 - window.y0 + 1);
				unsigned char* channelValues = new unsigned char[arraySize];
				index = 0;
				for (i = window.x0; i <= window.x1; i++)
				{
					for (j = window.y0; j <= window.y1; j++)
					{
						channelValues[index] = image(i, j, channel);
						index++;
					}
				}

				imageCopy(x, y, channel) = getMedian(channelValues, arraySize);
				delete[] channelValues;
			}
		}
	}
	image = imageCopy;
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

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

	switch (option)
	{
	case brightness:
		changeBrightness(value);
		break;
	case contrast:
		changeContrast(value);
		break;
	case negative:
		changeToNegative();
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
		enlargeImage(value);
		break;
	case min:
		minFilter(value);
		break;
	case max:
		maxFilter(value);
		break;
	case median:
		medianFilter(value);
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

	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / (double)1000000;

	cout << "Algorithm duration: " << duration << " seconds";
	image.display("Processed image preview", false);
	image.save("processedImage.bmp");
};
