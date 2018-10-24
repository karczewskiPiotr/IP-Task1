#include <iostream>
#include "ArgumentsHandler.h"
#include "ImageProcesser.h"
#include "HistogramProcesser.h"

using namespace std;

int main(int argc, char* argv[])
{
	ArgumentsHandler ArgumentsHandler(argc, argv);

	ArgumentsHandler.validateArguments();

	if (!ArgumentsHandler.argumentsAreValid) return 0;

	ImageProcesser ImageProcesser(ArgumentsHandler.get_imageName(), ArgumentsHandler.convertToInt(ArgumentsHandler.get_option()), ArgumentsHandler.get_value(), ArgumentsHandler.get_noisyImageName(), ArgumentsHandler.get_denoisedImageName());

	ImageProcesser.processImage();

	HistogramProcesser HistogramProcesser(ArgumentsHandler.get_imageName(), ArgumentsHandler.convertToInt(ArgumentsHandler.get_option()));

	HistogramProcesser.makeHistogram();

	return 0;
}

