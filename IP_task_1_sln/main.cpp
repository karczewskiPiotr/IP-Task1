#include "pch.h"
#include <iostream>
#include "CImg.h"
#include "ArgumentsHandler.h"

using namespace std;

int main(int argc, char* argv[])
{
	ArgumentsHandler ArgumentsHandler(argc, argv);

	ArgumentsHandler.validateArguments();

	if (!ArgumentsHandler.argumentsAreValid) return 0;

	cout << "Image name: " << ArgumentsHandler.get_imageName() << " option: " << ArgumentsHandler.get_option() << ", value: " << ArgumentsHandler.get_value() << endl;
	
	//process the images
	cimg_library::CImg<unsigned char> image(ArgumentsHandler.get_imageName().c_str()); // wczytuje zdjęcie podane przez ludzia
	cimg_library::CImg<unsigned char> processedImage = image; // tak sobie można stworzyć identyczne zdjęcie co podane przez ludzia by nie pracować na oryginale

	//Shows image in separate window
	processedImage.display();

	processedImage.save("file.bmp"); // a tak se można zapisać jako bmp

	return 0;
}

