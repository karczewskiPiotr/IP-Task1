#pragma once
#include <iostream>
#include <string>
#include <algorithm>

class ArgumentsHandler
{
private:
	int argc;
	char** argv;

	std::string option;
	std::string value;

	std::string argumentOptions[17] = { "--help", "--brightness", "--contrast", "negative", "--hflip", "--vflip", "--dflip", "--shrink", "--enlarge", "--min", "--max", "--media", "--mse", "--pmse", "--snr", "--psnr", "--md" };

	std::string errorMessageInvalidNumberOfArguments = "Invalid number of arguments. Please use --help to see the possible arguments.";
	std::string errorMessageInvalidOption = "Invalid option. Please use --help to see the possible arguments.";
	std::string errorMessageInvalidValue = "Invalid value. Please use --help to see the possible arguments.";
	std::string errorMessageOptionNeedsAValue = "Option needs a value. Please use --help to see the possible arguments.";
	std::string helpMessage = "sam se pomusz jak ci zara no wlasnie";

	bool optionIsValid(std::string option);
	bool valueIsValid(std::string value);

public:
	ArgumentsHandler(int argc, char* argv[]);
	~ArgumentsHandler();

	bool argumentsAreValid = false;

	void printArguments();
	void validateArguments();

	std::string get_option() const
	{
		return option;
	}
	std::string get_value() const
	{
		return value;
	}
};