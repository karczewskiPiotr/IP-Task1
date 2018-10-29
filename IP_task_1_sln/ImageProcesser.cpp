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
	//image.display("Processed image preview", false);
	image.save("processedImage.bmp");
};
