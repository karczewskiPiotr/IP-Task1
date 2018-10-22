#include "Error.h"
#include <iostream>

Error::Error()
{
}


Error::~Error()
{
}

void Error::InvalidNumberOfArguments()
{
	std::cout << "Invalid number of arguments. Please use --help to see the possible arguments." << std::endl;
}

void Error::InvalidOption()
{
	std::cout << "Invalid option. Please use --help to see the possible arguments." << std::endl;
}

void Error::InvalidArguments()
{
	std::cout << "Invalid arguments. Please use --help to see the possible arguments." << std::endl;
}

void Error::InvalidValue()
{
	std::cout << "Invalid value. Please use --help to see the possible arguments." << std::endl;
}

void Error::OptionNeedsValue()
{
	std::cout << "Option needs a value. Please use --help to see the possible arguments." << std::endl;
}
