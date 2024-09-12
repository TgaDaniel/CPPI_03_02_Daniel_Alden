#pragma once
#include <random>
namespace RandomHandler
{
	static std::random_device locRandomDevice;
	static std::mt19937 locRandomNrGeneratorAlgorithm(locRandomDevice());

	int RandomNumberInRange(int aMinValue, int aMaxValue);
}