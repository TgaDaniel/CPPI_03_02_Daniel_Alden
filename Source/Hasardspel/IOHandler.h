#pragma once

#include "GameUtilities.h"
namespace IOHandler
{
	void FlushCinBuffer();
	void PauseThenClearScreen();
	bool ValidateInput();
	bool TwoCharacterOptionInput(char aTrueChar, char aFalseChar);
	void ReactionText(const GameUtilities::GeneralCasinoRules& aGeneralRules, int aTableValueChange, const Player::PlayerInformation& aPlayer);
	void HandleAllInWin(Player::PlayerInformation& aPlayer);
}
