#pragma once
#include <array>

#include "GameUtilities.h"
#include "Player.h"

namespace GuessTheSquare
{

	class GuessTheSquareTable
	{
	public:
		GuessTheSquareTable( const GameUtilities::GameConditions& aConditions, Player::PlayerInformation& aPlayerInfo, const GameUtilities::GeneralCasinoRules aGeneralRules);

		void Play();

	private:
		const GameUtilities::GameConditions& myConditions;
		Player::PlayerInformation& myPLayerInfo;
		const GameUtilities::GeneralCasinoRules myGeneralRules;
		std::array<bool,5> mySquares;

		void DisplaySquares() const;
		void DisplaySquares(int aDisplaySquare) const;
	};
}
