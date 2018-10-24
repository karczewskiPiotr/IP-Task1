#include "HistogramProcesser.h"
#include <iostream>



HistogramProcesser::HistogramProcesser()
{
}

HistogramProcesser::HistogramProcesser(std::string imageName, int option)
	:Processer(imageName, option)
{
}


HistogramProcesser::~HistogramProcesser()
{
}

void HistogramProcesser::makeHistogram()
{
	if (option < 17) return;

	cimg_library::CImg<unsigned char> initialImage;
	
	try
	{
		initialImage.load(imageName.c_str());
	}
	catch (cimg_library::CImgException)
	{
		std::cout << std::endl << "Image could not be loaded. Please check whether the filename is correct." << std::endl;
		return;
	}

	if (!initialImage) return;

	image = initialImage;
	height = image.height();
	width = image.width();

	switch (option)
	{
	case hpower:
		std::cout << "Function under developement" << std::endl;
		break;
	case cmean:
		std::cout << "Function under developement" << std::endl;
		break;
	case cvariance:
		std::cout << "Function under developement" << std::endl;
		break;
	case cvarcoi:
		std::cout << "Function under developement" << std::endl;
		break;
	case casyco:
		std::cout << "Function under developement" << std::endl;
		break;
	case cvarcoii:
		std::cout << "Function under developement" << std::endl;
		break;
	case centropy:
		std::cout << "Function under developement" << std::endl;
		break;
	case sedgesharp:
		std::cout << "Function under developement" << std::endl;
		break;
	case orosenfeld:
		std::cout << "Function under developement" << std::endl;
		break;
	default:
		break;
	}

	image.save("histogram.bmp");
}
