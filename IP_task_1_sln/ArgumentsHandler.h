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
	std::string imageName;

	std::string options[17] { "--brightness", "--contrast", "--help", "--negative", "--hflip", "--vflip", "--dflip", "--shrink", "--enlarge", "--min", "--max", "--media", "--mse", "--pmse", "--snr", "--psnr", "--md" };

	bool optionIsValid(std::string option);
	bool optionRequiresValue(std::string option);
	bool valueIsValid(std::string value);

public:
	ArgumentsHandler(int argc, char* argv[]);
	~ArgumentsHandler();

	bool argumentsAreValid = false;

	void helpMessage();
	void printArguments();
	void validateArguments();

	std::string get_imageName() const;
	std::string get_option() const;
	std::string get_value() const;
};