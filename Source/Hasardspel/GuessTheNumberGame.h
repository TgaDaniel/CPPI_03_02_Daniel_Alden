#pragma once

#include "GameUtilities.h"
#include "Player.h"

namespace GuessTheNumber {

	class GuessTheNumberTable
	{
	public:
		GuessTheNumberTable(GameUtilities::GameConditions& aConditions, Player::PlayerInformation& aPlayerInformation, GameUtilities::GeneralCasinoRules aRules);

		void Play();

	private:
		static int myTotalWinAmountGuessingGame;
		static int myTotalValueChangeGuessingGame;

		int myBet;
		int myFirstDie;
		int mySecondDie;
		int myGuess;

		const GameUtilities::GameConditions& myConditions;
		Player::PlayerInformation& myPlayerInfo;
		const GameUtilities::GeneralCasinoRules myGeneralRules;

		void DisplayGuessNumberGameStatBoard() const;
	};


}
