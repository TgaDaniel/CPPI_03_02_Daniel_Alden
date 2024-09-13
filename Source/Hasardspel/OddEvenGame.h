#pragma once
#include "Player.h"

namespace OddEvenGame
{
	class OddEvenTable
	{
	public:
		OddEvenTable(int aWinMultiplier, Player::PlayerInformation& aPLayerInfo, const GameUtilities::GeneralCasinoRules aGeneralRules);

		void Play(RandomHandler& aRandomHandler);

	private:
		int myTotalWinAmountOddOrEven;
		int myTotalValueChange;

		int myBet;

		const GameUtilities::GameConditions myConditions;
		Player::PlayerInformation& myPLayerInfo;
		const GameUtilities::GeneralCasinoRules myGeneralRules;

		void DisplayOddOrEvenGameStatBoard(const bool aGuess, const int aFirstDie, const int aSecondDie);
	};
}
