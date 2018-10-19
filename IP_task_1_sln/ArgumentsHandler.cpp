#include "ArgumentsHandler.h"
#include "Error.h"
//#include <boost/algorithm/string/predicate.hpp>

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
	for (string::iterator iterator = value.begin(); iterator != value.end(); ++iterator)
	{
		if (*iterator < 48 || *iterator > 57)
		{
			return false;
		}
	}
	return true;
}

bool ArgumentsHandler::isNameOfFile(std::string name)
{
	return name.size() >= 4 && name.compare(name.size() - 4, 4, ".bmp") == 0;
}

void ArgumentsHandler::helpMessage()
{
	//R"()" allows to print text exactly like u see it
	std::cout << R"(Command line format:
	name --command [-argument=value [...]]
Available commands:
	--brightness - Image brightness modification
	--contrast - Image contrast modification
	--negative - Negative
	--hflip - Horizontal flip
	--vflip - Vertical flip
	--dflip - Diagonal flip
	--shrink - Image shrinking
	--enlarge - Image enlargement
	--min - Min filter
	--max - Max filter
	--median - Median filter
	--mse - Mean square
	--pmse - Peak mean square
	--snr - Signal to noise ratio
	--psnr - Peak signal to noise ratio
	--md - Maximum difference)";
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

unsigned int ArgumentsHandler::get_value() const
{
	return value.length() > 0 ? stoi(value) : 0;
}