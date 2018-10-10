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
	return find(begin(argumentOptions), end(argumentOptions), option) != end(argumentOptions);
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

		if (!optionIsValid(option))
		{
			cout << errorMessageInvalidOption << endl;
		}
		else if (option == "--help")
		{
			cout << helpMessage << endl;
		}
		else
		{
			cout << errorMessageOptionNeedsAValue << endl;
		}

		break;

	case 3:
		option = argv[1];

		if (!optionIsValid(option))
		{
			cout << errorMessageInvalidOption << endl;
			break;
		}

		value = argv[2];

		if (!valueIsValid(value))
		{
			cout << errorMessageInvalidValue << endl;
			break;
		}

		argumentsAreValid = true;
		break;

	default:
		cout << errorMessageInvalidNumberOfArguments << endl;
		break;
	}
}