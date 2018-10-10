#include "pch.h"
#include "CImg.h"
#include <iostream>
#include "ArgumentsHandler.h"

using namespace std;
//Namespace of CImg library for easier declarations
using namespace cimg_library;

//argc - arguments counter
//argv - table with values of read arguments

// argv[0] - name of the program, argv[1] - help | option, argv[2] - value
int main(int argc, char* argv[])
{
	ArgumentsHandler ArgumentsHandler(argc, argv);

	ArgumentsHandler.validateArguments();

	if (ArgumentsHandler.argumentsAreValid)
	{
		cout << "Option: " << ArgumentsHandler.get_option() << ", value: " << ArgumentsHandler.get_value() << endl;
		//process the images
	}
	return 0;
}

