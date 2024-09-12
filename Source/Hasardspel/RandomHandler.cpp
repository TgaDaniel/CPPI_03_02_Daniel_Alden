#include "RandomHandler.h"

namespace RandomHandler
{
	/// <summary>
/// Generates a random number within the range of <c>aMinValue</c> and <c>aMaxValue</c>
/// </summary>
/// <param name="aMinValue">Lowest possible generated value</param>
/// <param name="aMaxValue">Highest possible generated value</param>
/// <returns>A integer between <c>aMinValue</c> and <c>aMaxValue</c></returns>
	int RandomNumberInRange(const int aMinValue, const int aMaxValue)
	{
		std::uniform_int_distribution<int> numberDistributer(aMinValue, aMaxValue);
		return numberDistributer(locRandomNrGeneratorAlgorithm);
	}
}