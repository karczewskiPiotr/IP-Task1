#include "pch.h"
#include <iostream>
#include "ArgumentsHandler.h"

using namespace std;

int main(int argc, char* argv[])
{
	ArgumentsHandler ArgumentsHandler(argc, argv);

	ArgumentsHandler.validateArguments();

	if (ArgumentsHandler.argumentsAreValid)
	{
		cout << "Image name: " << ArgumentsHandler.get_imageName() << " option: " << ArgumentsHandler.get_option() << ", value: " << ArgumentsHandler.get_value() << endl;
		//process the images
	}
	return 0;
}

