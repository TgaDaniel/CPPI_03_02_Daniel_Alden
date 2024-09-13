#pragma once
#include "Player.h"

namespace GameUtilities
{

	struct GeneralCasinoRules
	{
		int maxWinAmountPerTable = 300;
		int reactionAmount = 100;
	};

	struct TableBetParameters
	{
		int minBet{10};
		int maxBet{100};
	};

	struct GameConditions
	{
		int minRandomValue = 1;
		int maxRandomValue = 6 ;
		int winMultiplier = 2;
	};

	int HandleBetting(Player::PlayerInformation& aPlayerInfo, bool aUseBetParams = false, TableBetParameters aBetParams = {1,100});

	bool CheckIfEven(int aValue);

}
