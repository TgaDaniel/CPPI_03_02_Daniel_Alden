#pragma once
namespace IOHandler
{
	void FlushCinBuffer();
	void PauseThenClearScreen();
	bool ValidateInput();
	bool TwoCharacterOptionInput(char aTrueChar, char aFalseChar);
	void ReactionText(const GameUtilities::GeneralCasinoRules& aGeneralRules, int aTableValueChange);
	void HandleAllInWin(Player::PlayerInformation& aPlayer);
}
