#pragma once

#include "GameUtilities.h"
#include "Player.h"
#include "RandomHandler.h"

namespace RockPaperScissors
{
	enum class SelectHand
	{
		Rock = 1,
		Paper,
		Scissors
	};

	class RockPaperScissorsTable
	{
	public:
		RockPaperScissorsTable(int aWinMultiplier, Player::PlayerInformation& aPlayerInfo, GameUtilities::GeneralCasinoRules aRules);

		void Play(RandomHandler& aRandomHandler);

	private:
		  int myTotalWinAmount;
		  int myTotalValueChange;

		int myBet;
		SelectHand myPlayerHand;
		SelectHand myOpponentHand;

		const GameUtilities::GameConditions myConditions;
		Player::PlayerInformation& myPLayerInfo;
		const GameUtilities::GeneralCasinoRules myGeneralRules;

		void DisplayRockPaperScissorsGameStatBoard(bool aHiddenOpponent = false);
	};

}
