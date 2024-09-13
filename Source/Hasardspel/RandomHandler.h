#pragma once
#include <random>

class RandomHandler
{
public:
	RandomHandler();
	int RandomNumberInRange(int aMinValue, int aMaxValue);

private:
	std::random_device myRandomDevice;
	std::mt19937 myRandomNrGeneratorAlgorithm;
};
