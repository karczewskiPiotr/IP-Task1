#pragma once

class Error
{
public:
	Error();
	~Error();

	//Error functions
	void InvalidNumberOfArguments();
	void InvalidOption();
	void InvalidArguments();
	void InvalidValue();
	void OptionNeedsValue();

	//Pointers to error functions
	void (Error::*invalidNumberOfArguments)() = &Error::InvalidNumberOfArguments;
	void (Error::*invalidOption)() = &Error::InvalidOption;
	void (Error::*invalidArguments)() = &Error::InvalidArguments;
	void (Error::*invalidValue)() = &Error::InvalidValue;
	void (Error::*optionNeedsValue)() = &Error::OptionNeedsValue;
};

