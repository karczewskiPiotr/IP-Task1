#include "ArgumentsHandler.h"
#include "Error.h"
#include <algorithm>
#include <iostream>

using namespace std;

ArgumentsHandler::ArgumentsHandler(int argc, char* argv[])
	:argc(argc), argv(argv)
{
}

ArgumentsHandler::~ArgumentsHandler()
{
}

int ArgumentsHandler::convertToInt(std::string option)
{
	for (int i = 0; i < 17; i++)
	{
		if (options[i] == option) return i + 1;
	}
	return 0;
}

bool ArgumentsHandler::optionIsValid(string option)
{
	return find(begin(options), end(options), option) != end(options);
}

bool ArgumentsHandler::optionRequiresValue(string option)
{
	return option == "--brightness" || option == "--contrast" || option == "--enlarge" || option == "--shrink" || option == "--median" || option == "--min" || option == "--max";
}

bool ArgumentsHandler::valueIsValid(string value)
{
	int dot_counter = 0;
	for (string::iterator iterator = value.begin(); iterator != value.end(); ++iterator)
	{
		if (*iterator < 48 || *iterator > 57)
		{
			if (option == "--brightness" || option == "--contrast")
			{
				if (iterator == value.begin() && *iterator == 45) continue;
				if (*iterator != 46) return false;
				else if (*iterator == 46) dot_counter += 1;
			}
			else if (option == "--enlarge" || option == "--shrink")
			{
				if (*iterator != 46) return false;
				else if (*iterator == 46) dot_counter += 1;
			}
			if (option == "--median" || option == "--min" || option == "--max") return false;
		}
		if (dot_counter > 1) return false;
	}
	return true;
}

bool ArgumentsHandler::isNameOfFile(std::string name)
{
	return name.size() >= 4 && name.compare(name.size() - 4, 4, ".bmp") == 0;
}

void ArgumentsHandler::helpMessage()
{
	std::cout << R"(Command line format:
	name --command [-argument=value [...]]

Available commands:

	Elementary operations:
	--brightness
		Image brightness modification
			Adds provided value to the pixel's RGB channels keeping it within
			range from 0 to 255.
	--contrast
		Image contrast modification
			Chnages pixel's RGB values via use of linear function.
	--negative
		Negative
			Negates pixel's RGB values with the use of bitwise negation operator.
	
	Geometric operations:
	--hflip
		Horizontal flip
			Swaps every pixel's channel values from left to half the image's
			width with the corresponding pixel from the right half.
	--vflip
		Vertical flip
			Swaps every pixel's channel values from top to half the image's
			height with the corresponding pixel from the bottom half.
	--dflip
		Diagonal flip
			Swaps every pixel's channel values from top to half the image's
			height with the pixel placed diagonally on the bottom half.
	--shrink 
		Image shrinking
			Shrinks the image by interpolating pixel's RGB values in 2 x 2 grid
			by taking 0.25 of each surrounding pixel with respect to the original image.
	--enlarge
		Image enlargement
			Enlarges the image with the use of bilinear interpolation. Estimating distance 
			between original pixels in 2 x 2 grid program calculates the weighted sum of these
			pixels' RGB values and assigns it to blank pixels in enlarged image.
	Filters:
		General information:
			A moving window with side length of 2 * value + 1 is created.
			Eg. --min 1 produces a window of size 3x3.
			The image is then traversed by the window (with the pixel which
			we want to change in the center) and if the window is to
			exceed the image's height or width, it is shortened to match
			the image's size.
			Eg. a 3x3 window in pixel (0,0) will be shortened to a 2x2 window.
			For every channel, a dynamic array is filled with it's values
			and then an operation is performed according to the chosen option.
			Every operation is performed on a temporary image.
	--min value
		Min filter
			Takes the minimum value for every channel and substitutes it in place
			of the channel at the pixel's position on a temporary image.
	--max value
		Max filter
			Takes the maximum value for every channel and substitutes it in place
			of the channel at the pixel's position on a temporary image.
	--median value
		Median filter
			Sorts the values of every channel, takes the median and substitutes
			it in place of the channel at the pixel's position on a temporary image.

	Similarity measures:
		General information:
			Used to compare the effectiveness of noise removal methods.
			The correct format:
			name originalImage.bmp --option noisyImage.bmp denoisedImage.bmp
	--mse
		Mean square error
	--pmse
		Peak mean square error
	--snr
		Signal to noise ratio
	--psnr
		Peak signal to noise ratio
	--md
		Maximum difference)";
}

void ArgumentsHandler::validateArguments()
{
	//Definition of type beeing a pointer to a void function within class Error
	typedef void (Error::*Error_fnc_ptr)();

	Error error;

	switch (argc)
	{
	case 2:
		option = argv[1];

		try
		{
			option == "--help" ? helpMessage() : throw error.invalidArguments;
		}
		catch (Error_fnc_ptr exception)
		{
			(error.*exception)();
		}
		break;
	case 3:
		imageName = argv[1];
		option = argv[2];

		try
		{
			if (optionIsValid(option) && option != "--help")
			{
				argumentsAreValid = optionRequiresValue(option) ? throw error.optionNeedsValue : true;
			}
			else throw error.invalidOption;
		}
		catch (Error_fnc_ptr exception)
		{
			(error.*exception)();
		}
		break;
	case 4:
		imageName = argv[1];
		option = argv[2];
		value = argv[3];

		try
		{

			if (optionIsValid(option) && option != "--help")
			{
				if (!optionRequiresValue(option)) { throw error.invalidNumberOfArguments; }
				else if (!valueIsValid(value)) { throw error.invalidValue; }
				else { argumentsAreValid = true; break; }
			}
			else throw error.invalidOption;
			break;

		}
		catch (Error_fnc_ptr exception)
		{
			(error.*exception)();
		}
		break;
	case 5:
		imageName = argv[1];
		noisyImageName = argv[3];
		denoisedImageName = argv[4];
		option = argv[2];

		try
		{
			if (optionIsValid(option))
			{
				if (optionRequiresValue(option) || option == "--help" || option == "--negative") { throw error.invalidArguments; }
				else if (isNameOfFile(noisyImageName) && isNameOfFile(denoisedImageName)) { argumentsAreValid = true; break; }
				else throw error.invalidValue;
			}
			else throw error.invalidArguments;
		}
		catch (Error_fnc_ptr exception)
		{
			(error.*exception)();
		}
		break;
	default:
		error.InvalidNumberOfArguments();
		break;
	}
}

string ArgumentsHandler::get_imageName() const
{
	return imageName;
}

std::string ArgumentsHandler::get_noisyImageName() const
{
	return noisyImageName;
}

std::string ArgumentsHandler::get_denoisedImageName() const
{
	return denoisedImageName;
}

string ArgumentsHandler::get_option() const
{
	return option;
}

double ArgumentsHandler::get_value() const
{
	return value.length() > 0 ? stod(value) : 0;
}