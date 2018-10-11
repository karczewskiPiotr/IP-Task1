#include "pch.h"
#include "ArgumentsHandler.h"

using namespace std;

ArgumentsHandler::ArgumentsHandler(int argc, char* argv[])
{
	this->argc = argc;
	this->argv = argv;
}

ArgumentsHandler::~ArgumentsHandler()
{
}

bool ArgumentsHandler::optionIsValid(string option)
{
	return find(begin(options), end(options), option) != end(options);
}

bool ArgumentsHandler::optionRequiresValue(string option)
{
	return option == "--brightness" || option == "--contrast";
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

void ArgumentsHandler::printArguments()
{
	cout << "argc = " << argc << endl;
	for (int i = 0; i < argc; i++)
	{
		cout << argv[i] << endl;
	}
}

void ArgumentsHandler::validateArguments()
{
	switch (argc)
	{
	case 2:
		option = argv[1];

		if (option == "--help")
		{
			cout << helpMessage << endl;
		}
		else
		{
			cout << errorMessageInvalidArguments << endl;
		}

		break;
	case 3:
		imageName = argv[1];
		option = argv[2];

		if (optionIsValid(option))
		{
			if (optionRequiresValue(option))
			{
				cout << errorMessageOptionNeedsAValue << endl;
			}
			else
			{
				argumentsAreValid = true;
				break;
			}
		}
		else
		{
			cout << errorMessageInvalidOption << endl;
		}
		break;
	case 4:
		imageName = argv[1];
		option = argv[2];
		value = argv[3];
		if (optionIsValid(option))
		{
			if (!optionRequiresValue(option))
			{
				cout << errorMessageInvalidNumberOfArguments << endl;
			}
			else if (!valueIsValid(value))
			{
				cout << errorMessageInvalidValue << endl;
			}
			else
			{
				argumentsAreValid = true;
				break;
			}
		}
		else
		{
			cout << errorMessageInvalidOption << endl;
		}
		break;
	default:
		cout << errorMessageInvalidNumberOfArguments << endl;
		break;
	}
}

string ArgumentsHandler::get_option() const
{
	return option;
}

string ArgumentsHandler::get_value() const
{
	return value;
}
string ArgumentsHandler::get_imageName() const
{
	return imageName;
}