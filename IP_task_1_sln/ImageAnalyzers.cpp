#include <iostream>
#include "ImageProcesser.h"

using namespace std;

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
	cout << "The Maximum Difference for the images is: " << endl << "Original image and the image with noise: " << maxDiff1 << endl
		<< "Original image and the denoised image: " << maxDiff2 << endl;
}