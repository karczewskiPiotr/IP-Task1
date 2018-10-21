#include "ImageProcesser.h"
#include <chrono>
#include <iostream>

using namespace cimg_library;
using namespace std;

ImageProcesser::ImageProcesser(std::string imageName, int option, double value, std::string noisyImageName, std::string denoisedImageName)
	:imageName(imageName), option(option), value(value), noisyImageName(noisyImageName), denoisedImageName(denoisedImageName)
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

void ImageProcesser::shrinkImage(double modifier)
{
	unsigned int enlargedWidth = (unsigned int)(width / modifier);
	unsigned int enlargedHeight = (unsigned int)(height / modifier);
	double finalSum;
	cimg_library::CImg<unsigned char> enlargedImage(enlargedWidth, enlargedHeight, 1, 3, 0);
	int p1x, p1y, p2x, p2y, p3x, p3y, p4x, p4y;

	for (unsigned int y = 0; y < enlargedHeight; y++)
	{
		for (unsigned int x = 0; x < enlargedWidth; x++)
		{
			p1x = (int)(x * modifier);
			p1y = (int)(y * modifier);

			p2x = p1x + 1;
			p2y = p1y;

			p3x = p1x;
			p3y = p1y + 1;

			p4x = p1x + 1;
			p4y = p1y + 1;

			for (unsigned int channel = 0; channel < 3; channel++)
			{
				finalSum = 0.25*image(p1x, p1y, channel) + 0.25*image(p2x, p2y, channel) + 0.25*image(p3x, p3y, channel) + 0.25*image(p4x, p4y, channel);
				enlargedImage(x, y, channel) = truncate((int)finalSum);
			}
		}
	}

	image = enlargedImage;
}

void ImageProcesser::enlargeImage(double modifier)
{
	unsigned int enlargedWidth = (unsigned int)(width * modifier);
	unsigned int enlargedHeight = (unsigned int)(height * modifier);
	double sum1, sum2, finalSum, step = 1 / modifier;
	cimg_library::CImg<unsigned char> enlargedImage(enlargedWidth, enlargedHeight, 1, 3, 0);
	int p1x, p1y, p2x, p2y, p3x, p3y, p4x, p4y;

	for (unsigned int y = 0; y < enlargedHeight; y++)
	{
		for (unsigned int x = 0; x < enlargedWidth; x++)
		{
			if (step >= 1) step = 1 / modifier;
			p1x = (int)(x / modifier);
			p1y = (int)(y / modifier);

			p2x = p1x + 1;
			p2y = p1y;

			p3x = p1x;
			p3y = p1y + 1;

			p4x = p1x + 1;
			p4y = p1y + 1;

			for (unsigned int channel = 0; channel < 3; channel++)
			{
				sum1 = ((p2x - (p1x + step)) / (p2x - p1x)) * image(p1x, p1y, channel) + (((p1x + step) - p1x) / (p2x - p1x)) * image(p2x, p2y, channel);
				sum2 = ((p4x - (p3x + step)) / (p4x - p3x)) * image(p3x, p3y, channel) + (((p3x + step) - p3x) / (p4x - p3x)) * image(p4x, p4y, channel);
				finalSum = ((p3y - (p1y + step)) / (p3y - p1y)) * sum1 + (((p1y + step) - p1y) / (p3y - p1y)) * sum2;
				enlargedImage(x, y, channel) = truncate((int)finalSum);
			}

			step += 1 / modifier;
		}
	}

	image = enlargedImage;
}

void ImageProcesser::horizontalFlip()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width / 2; x++)
		{
			swapPixelsRGBValues(x, y, width - 1 - x, y);
		}
	}
}

void ImageProcesser::verticalFlip()
{
	for (int y = 0; y < height / 2; y++)
	{
		for (int x = 0; x < width; x++)
		{
			swapPixelsRGBValues(x, y, x, height - 1 - y);
		}
	}
}

void ImageProcesser::diagonalFlip()
{
	for (int y = 0; y < height / 2; y++)
	{
		for (int x = 0; x < width; x++)
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

void ImageProcesser::calculateMSE()
{
	double mse1 = 0, mse2 = 0, factor = 1 / (double)(width * height);
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			for (int channel = 0; channel < 3; channel++)
			{
				mse1 += pow(image(x, y, channel) - noisyImage(x, y, channel), 2);
				mse2 += pow(image(x, y, channel) - denoisedImage(x, y, channel), 2);
			}
		}
	}
	mse1 *= factor;
	mse2 *= factor;
	// We need to divide the values by 3 as we calculated it for all 3 channels
	mse1 /= 3;
	mse2 /= 3;
	cout << "The Mean Squared Error for the images is: " << endl << "Original image and the image with noise: " << mse1 << endl
		<< "Original image and the denoised image: " << mse2 << endl;
}

void ImageProcesser::calculatePMSE()
{
	int max = 0;
	double pmse1 = 0, pmse2 = 0, factor = 1 / (double)(width * height);
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			for (int channel = 0; channel < 3; channel++)
			{
				max = max < image(x, y, channel) ? image(x, y, channel) : max;
				pmse1 += pow(image(x, y, channel) - noisyImage(x, y, channel), 2);
				pmse2 += pow(image(x, y, channel) - denoisedImage(x, y, channel), 2);
			}
		}
	}
	pmse1 = (pmse1 * factor) / pow(max, 2);
	pmse2 = (pmse2 * factor) / pow(max, 2);
	cout << "The Peak Mean Squared Error for the images is: " << endl << "Original image and the image with noise: " << pmse1 << endl
		<< "Original image and the denoised image: " << pmse2 << endl;
}

void ImageProcesser::calculateSNR()
{
	double numerator = 0, denominator1 = 0, denominator2 = 0;
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			for (int channel = 0; channel < 3; channel++)
			{
				numerator += pow(image(x, y, channel), 2);
				denominator1 += pow(image(x, y, channel) - noisyImage(x, y, channel), 2);
				denominator2 += pow(image(x, y, channel) - denoisedImage(x, y, channel), 2);
			}
		}
	}
	double snr1 = 10 * log10(numerator / denominator1);
	double snr2 = 10 * log10(numerator / denominator2);
	cout << "The Signal to Noise Ratio for the images is: " << endl << "Original image and the image with noise: " << snr1 << "dB" << endl
		<< "Original image and the denoised image: " << snr2 << "dB" << endl;
}

void ImageProcesser::calculatePSNR()
{
	double mse1 = 0, mse2 = 0, factor = 1 / (double)(width * height), max = 0;
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			for (int channel = 0; channel < 3; channel++)
			{
				max = max < image(x, y, channel) ? image(x, y, channel) : max;
				mse1 += pow(image(x, y, channel) - noisyImage(x, y, channel), 2);
				mse2 += pow(image(x, y, channel) - denoisedImage(x, y, channel), 2);
			}
		}
	}
	mse1 *= factor;
	mse2 *= factor;
	mse1 /= 3;
	mse2 /= 3;

	double psnr1 = 10 * log10((max*max) / mse1);
	double psnr2 = 10 * log10((max*max) / mse2);
	cout << "The Peak Signal to Noise Ratio for the images is: " << endl << "Original image and the image with noise: " << psnr1 << "dB" << endl
		<< "Original image and the denoised image: " << psnr2 << "dB" << endl;
}

void ImageProcesser::calculateMD()
{
	double maxDiff1 = 0, maxDiff2 = 0;
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			for (int channel = 0; channel < 3; channel++)
			{
				maxDiff1 = maxDiff1 < abs(image(x, y, channel) - noisyImage(x, y, channel)) ? abs(image(x, y, channel) - noisyImage(x, y, channel)) : maxDiff1;
				maxDiff2 = maxDiff2 < abs(image(x, y, channel) - denoisedImage(x, y, channel)) ? abs(image(x, y, channel) - denoisedImage(x, y, channel)) : maxDiff2;
			}
		}
	}
	calculateMSE();
	calculatePMSE();
	calculateSNR();
	calculatePSNR();
	cout << "The Maximum Difference for the images is: " << endl << "Original image and the image with noise: " << maxDiff1 << endl
		<< "Original image and the denoised image: " << maxDiff2 << endl;
}

#pragma endregion

void ImageProcesser::processImage()
{
	cimg_library::CImg<unsigned char> initialImage;
	cimg_library::CImg<unsigned char> initialNoisyImage;
	cimg_library::CImg<unsigned char> initialDenoisedImage;
	try
	{
		initialImage.load(imageName.c_str());
		if (option >= 13 && option <= 17)
		{
			initialNoisyImage.load(noisyImageName.c_str());
			initialDenoisedImage.load(denoisedImageName.c_str());
			if (initialNoisyImage.width() != initialImage.width() || initialNoisyImage.height() != initialImage.height() || initialDenoisedImage.width() != initialImage.width() || initialDenoisedImage.height() != initialImage.height())
			{
				cout << endl << "Images you provided do not have the same size. Please check whether the filenames are correct." << endl;
				return;
			}
		}
	}
	catch (CImgException)
	{
		cout << endl << "Image could not be loaded. Please check whether the filename is correct." << endl;
		return;
	}

	if (!initialImage) return;
	image = initialImage;
	if (option >= 13 && option <= 17)
	{
		noisyImage = initialNoisyImage;
		denoisedImage = initialDenoisedImage;
	}
	height = image.height();
	width = image.width();

	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

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
		shrinkImage(value);
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
		calculateMSE();
		break;
	case pmse:
		calculatePMSE();
		break;
	case snr:
		calculateSNR();
		break;
	case psnr:
		calculatePSNR();
		break;
	case md:
		calculateMD();
		break;
	default:
		break;
	}

	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count() / (double)1000000;

	cout << "Algorithm duration: " << duration << " seconds";
	if (option == mse || option == pmse || option == snr || option == psnr || option == md) return;
	image.display("Processed image preview", false);
	image.save("processedImage.bmp");
};
