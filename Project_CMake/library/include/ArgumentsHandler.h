#pragma once
#include <string>

class ArgumentsHandler
{
private:
	int argc;
	char** argv;

	std::string option;
	std::string value;
	std::string imageName;
	std::string noisyImageName;
	std::string denoisedImageName;

	std::string options[17] {  "--help", "--brightness", "--contrast", "--negative", "--hflip", "--vflip", "--dflip", "--shrink", "--enlarge", "--min", "--max", "--median", "--mse", "--pmse", "--snr", "--psnr", "--md" };

	bool optionIsValid(std::string option);
	bool optionRequiresValue(std::string option);
	bool valueIsValid(std::string value);
	bool isNameOfFile(std::string name);

public:
	ArgumentsHandler(int argc, char* argv[]);
	~ArgumentsHandler();

	bool argumentsAreValid = false;

	int convertToInt(std::string option);

	void helpMessage();
	void validateArguments();

	std::string get_imageName() const;
	std::string get_noisyImageName() const;
	std::string get_denoisedImageName() const;
	std::string get_option() const;
	double get_value() const;
};