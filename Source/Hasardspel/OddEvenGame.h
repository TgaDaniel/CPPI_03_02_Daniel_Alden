#pragma once
#include "Player.h"

namespace OddEvenGame
{
	class OddEvenTable
	{
	public:
		OddEvenTable(const GameUtilities::GameConditions& aConditions, Player::PlayerInformation& aPLayerInfo, const GameUtilities::GeneralCasinoRules aGeneralRules);

		void Play();

	private:
		static int myTotalWinAmountOddOrEven;
		static int myTotalValueChangeOddOrEven;

		int myBet;

		const GameUtilities::GameConditions& myConditions;
		Player::PlayerInformation& myPLayerInfo;
		const GameUtilities::GeneralCasinoRules myGeneralRules;

		void DisplayOddOrEvenGameStatBoard(const bool aGuess, const int aFirstDie, const int aSecondDie);
	};
}
