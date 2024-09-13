#pragma once

#include "GameUtilities.h"
#include "Player.h"
#include "RandomHandler.h"

namespace GuessTheNumber
{

	class GuessTheNumberTable
	{
	public:
		GuessTheNumberTable(int aWinMultiplier, Player::PlayerInformation& aPlayerInformation, GameUtilities::GeneralCasinoRules aRules, const GameUtilities::TableBetParameters aTableBetParams);

		void Play(RandomHandler& aRandomHandler);

	private:

		int myTotalWinAmount;
		int myTotalValueChange;
		int myBet;
		int myFirstDie;
		int mySecondDie;
		int myGuess;

		const GameUtilities::TableBetParameters myTableBetParameters;

		const GameUtilities::GameConditions myConditions;
		Player::PlayerInformation& myPlayerInfo;
		const GameUtilities::GeneralCasinoRules myGeneralRules;

		void DisplayGuessNumberGameStatBoard() const;
		bool ValidatePlayerCanBet() const;
	};


}
