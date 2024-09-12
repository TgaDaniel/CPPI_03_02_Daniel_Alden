#pragma once
#include "GameUtilities.h"

namespace GuessTheSquare
{
	void GuessTheSquareGame(bool aSquareArray[], int aSquareArraySize, const GameUtilities::GameConditions aConditions, GameUtilities::PlayerInformation& aPlayerInfo, const GameUtilities::GeneralCasinoRules aGeneralRules);
}
