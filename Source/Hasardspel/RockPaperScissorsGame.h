#pragma once

#include "GameUtilities.h"
#include "Player.h"

namespace RockPaperScissors
{
	class RockPaperScissorsTable
	{
	public:
		void Play(const GameUtilities::GameConditions aConditions, const GameUtilities::GeneralCasinoRules aGeneralRules, Player::PlayerInformation& aPlayerInformation);

	private:

	};

}
