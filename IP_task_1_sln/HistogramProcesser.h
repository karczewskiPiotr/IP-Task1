#pragma once
#include "Processer.h"

class HistogramProcesser : public Processer
{
private:
	enum options
	{
		hpower = 18, cmean, cvariance, cvarcoi, casyco, cvarcoii, centropy, sedgesharp, orosenfeld
	};

public:
	HistogramProcesser();
	HistogramProcesser(std::string imageName, int option);
	~HistogramProcesser();

	void makeHistogram();
};

