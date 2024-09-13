#pragma once
#include <array>

#include "GameUtilities.h"
#include "Player.h"
#include "RandomHandler.h"

namespace GuessTheSquare
{

	class GuessTheSquareTable
	{
	public:
		GuessTheSquareTable( int aWinMultiplier, Player::PlayerInformation& aPlayerInfo, const GameUtilities::GeneralCasinoRules aGeneralRules);

		void Play(RandomHandler& aRandomHandler);

	private:
		 int myTotalWinAmount;
		 int myTotalValueChange;

		const GameUtilities::GameConditions myConditions;
		Player::PlayerInformation& myPLayerInfo;
		const GameUtilities::GeneralCasinoRules myGeneralRules;
		std::array<bool,5> mySquares;

		void DisplaySquares() const;
		void DisplaySquares(int aDisplaySquare) const;
	};
}
