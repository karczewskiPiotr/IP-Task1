#include <iostream>
#include "ArgumentsHandler.h"
#include "ImageProcesser.h"

using namespace std;

int main(int argc, char* argv[])
{
	ArgumentsHandler ArgumentsHandler(argc, argv);

	ArgumentsHandler.validateArguments();

	if (!ArgumentsHandler.argumentsAreValid) return 0;
	cout << "Image name: " << ArgumentsHandler.get_imageName() << " option: " << ArgumentsHandler.get_option() << ", value: " << ArgumentsHandler.get_value() << ", noisy_image: " << ArgumentsHandler.get_noisyImageName() << ", denoised_image: " << ArgumentsHandler.get_denoisedImageName() << endl;

	//cout for debugging

	ImageProcesser ImageProcesser(ArgumentsHandler.get_imageName(), ArgumentsHandler.convertToInt(ArgumentsHandler.get_option()), ArgumentsHandler.get_value(), ArgumentsHandler.get_noisyImageName(), ArgumentsHandler.get_denoisedImageName());

	ImageProcesser.processImage();

	return 0;
}

