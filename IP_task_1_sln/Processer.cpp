#include "Processer.h"



int Processer::truncate(int value)
{
	if (value < 0) return 0;
	if (value > 255) return 255;

	return value;
}


Processer::Processer()
{
}

Processer::Processer(std::string imageName, int option)
	:imageName(imageName), option(option)
{
}


Processer::~Processer()
{
}
