#pragma once
#include "Player.h"

namespace GameUtilities
{

	struct GeneralCasinoRules
	{
		int maxWinAmountPerTable = 300;
		int reactionAmount = 100;
	};


	struct GameConditions
	{
		int minRandomValue;
		int maxRandomValue;
		int winMultiplier;
	};

	int HandleBetting(Player::PlayerInformation& aPlayerInfo);

	bool CheckIfEven(int aValue);

}
