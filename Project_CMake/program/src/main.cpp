#include "ArgumentsHandler.h"
#include "ImageProcesser.h"

using namespace std;

int main(int argc, char* argv[])
{
	ArgumentsHandler ArgumentsHandler(argc, argv);

	ArgumentsHandler.validateArguments();

	if (!ArgumentsHandler.argumentsAreValid) return 0;

	ImageProcesser ImageProcesser(ArgumentsHandler.get_imageName(), ArgumentsHandler.convertToInt(ArgumentsHandler.get_option()), ArgumentsHandler.get_value(), ArgumentsHandler.get_noisyImageName(), ArgumentsHandler.get_denoisedImageName());

	ImageProcesser.processImage();

	return 0;
}

