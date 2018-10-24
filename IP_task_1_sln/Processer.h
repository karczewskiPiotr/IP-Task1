#pragma once
#include <string>
#include "CImg.h"

class Processer
{
protected:
	std::string imageName;
	int option;

	cimg_library::CImg<unsigned char> image;
	unsigned short int height;
	unsigned short int width;

	int truncate(int value);
	
public:
	Processer();
	Processer(std::string imageName, int option);
	~Processer();
};

