#pragma once

#include "GameUtilities.h"
#include "Player.h"

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
		RockPaperScissorsTable(GameUtilities::GameConditions aConditions, Player::PlayerInformation aPlayerInfo, GameUtilities::GeneralCasinoRules aRules);

		void Play();

	private:
		static int myTotalWinAmount;
		static int myTotalValueChange;

		int myBet;
		SelectHand myPlayerHand;

		const GameUtilities::GameConditions& myConditions;
		Player::PlayerInformation& myPLayerInfo;
		const GameUtilities::GeneralCasinoRules myGeneralRules;

		void DisplayRockPaperScissorsGameStatBoard(bool aHiddenOpponent = false);
	};

}