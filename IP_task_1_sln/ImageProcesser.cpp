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

int ImageProcesser::truncate(int value)
{
	if (value < 0) return 0;
	if (value > 255) return 255;

	return value;
}

int getMedian(vector<unsigned char> channelValues)
{
	if (channelValues.size() == 0)
	{
		return 0;
	}
	sort(channelValues.begin(), channelValues.end());
	size_t size = channelValues.size();
	if (size % 2 == 0)
	{
		return (channelValues[(size / 2) - 1] + channelValues[size / 2]) / 2;
	}

	return channelValues[size / 2];
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

//void ImageProcesser::medianFilter()
//{
//	//rewrite this so that it does not use the getImage... function
//	// there need to be cases considered on every edge
//	// in the case of normal edges (not the corners) for x-1 or y-1 we should take x or y
//	// for corners (x-1, y-1 or...) take (x,y)
//	CImg<unsigned char> temporaryImage = getImageWithDuplicatedEdgeLines();
//	//iterate through the image in 3x3 windows (the pixel in the center will be the one that is changed)
//	unsigned int ix = 0;
//	unsigned int iy = 0;
//	//extend this to channels
//	for (unsigned int x = 1; x <= width; x++)
//	{
//		for (unsigned int y = 1; y <= height; y++)
//		{
//			//in every window, take the elements into an array
//			unsigned char red[9] = {
//				temporaryImage(x - 1, y - 1, 0),
//				temporaryImage(x, y - 1, 0),
//				temporaryImage(x + 1, y - 1, 0),
//				temporaryImage(x - 1, y, 0),
//				temporaryImage(x, y, 0),
//				temporaryImage(x + 1, y, 0),
//				temporaryImage(x - 1, y + 1, 0),
//				temporaryImage(x, y + 1, 0),
//				temporaryImage(x + 1, y + 1, 0)
//			};
//			unsigned char green[9] = {
//				temporaryImage(x - 1, y - 1, 1),
//				temporaryImage(x, y - 1, 1),
//				temporaryImage(x + 1, y - 1, 1),
//				temporaryImage(x - 1, y, 1),
//				temporaryImage(x, y, 1),
//				temporaryImage(x + 1, y, 1),
//				temporaryImage(x - 1, y + 1, 1),
//				temporaryImage(x, y + 1, 1),
//				temporaryImage(x + 1, y + 1, 1)
//			};
//			unsigned char blue[9] = {
//				temporaryImage(x - 1, y - 1, 2),
//				temporaryImage(x, y - 1, 2),
//				temporaryImage(x + 1, y - 1, 2),
//				temporaryImage(x - 1, y, 2),
//				temporaryImage(x, y, 2),
//				temporaryImage(x + 1, y, 2),
//				temporaryImage(x - 1, y + 1, 2),
//				temporaryImage(x, y + 1, 2),
//				temporaryImage(x + 1, y + 1, 2)
//			};
//			//sort these elements and take the middle value
//			//the middle value is now the value of the pixel in the center
//			size_t redSize = sizeof(red) / sizeof(*red);
//			sort(red, red + redSize);
//			size_t greenSize = sizeof(green) / sizeof(*green);
//			sort(green, green + greenSize);
//			size_t blueSize = sizeof(blue) / sizeof(*blue);
//			sort(blue, blue + blueSize);
//			image(ix, iy, 0) = red[4];
//			image(ix, iy, 1) = green[4];
//			image(ix, iy, 2) = blue[4];
//			iy++;
//		}
//		iy = 0;
//		ix++;
//	}
//}

void ImageProcesser::medianFilter(int radius)
{
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	if (radius == 0) return;
	//the parameter passed is the level - (--median 0 = 1x1 window, 1 = 3x3 window, 2 = 5x5 window, etc.)
	//rewrite this so that it does not use the getImage... function
	// there need to be cases considered on every edge
	// in the case of normal edges (not the corners) for x-1 or y-1 we should take x or y
	// for corners (x-1, y-1 or...) take (x,y)

	//iterate through the image in 3x3 windows (the pixel in the center will be the one that is changed)

	struct Window
	{
		unsigned short int x0;
		unsigned short int x1;
		unsigned short int y0;
		unsigned short int y1;
		vector<unsigned char> red;
		vector<unsigned char> green;
		vector<unsigned char> blue;
	};

	Window window;
	for (unsigned short int x = 0; x < width; x++)
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

		for (unsigned short int y = 0; y < height; y++)
		{
			//cout << "x: " << x << " y: " << y << endl;
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

			for (unsigned short int i = window.x0; i <= window.x1; i++)
			{
				for (unsigned short int j = window.y0; j <= window.y1; j++)
				{
					window.red.push_back(image(i, j, 0));
					window.green.push_back(image(i, j, 1));
					window.blue.push_back(image(i, j, 2));
				}
			}

			image(x, y, 0) = getMedian(window.red);
			image(x, y, 1) = getMedian(window.green);
			image(x, y, 2) = getMedian(window.blue);

			//instead of clearing the vector, swap its elements
			window.red.clear();
			window.green.clear();
			window.blue.clear();
		}
	}
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / (double)1000000;

	cout << duration << " seconds";
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

		break;
	case max:

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

	image.display("Processed image preview", false);
	image.save("processedImage.bmp");
};
