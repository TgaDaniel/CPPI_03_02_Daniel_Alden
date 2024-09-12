#pragma once
#include "GameUtilities.h"
#include "Player.h"

namespace Roulette
{
	struct CellValues
	{
		int cellNumber = 0;
		bool isRed = false;
	};

	struct RouletteConditions
	{
		int straightWinMultiplier = 5;
		int colorWinMultiplier = 3;
		int oddEvenWinMultiplier = 3;
		int columnwinMultiplier = 2;
	};

	void RouletteGame(RouletteConditions aConditions, GameUtilities::GeneralCasinoRules aGeneralRules, Player::PlayerInformation& aPLayerInfo);

}
