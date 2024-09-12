#pragma once
#include "GameUtilities.h"
#include "GuessTheNumberGame.h"
#include "GuessTheSquareGame.h"
#include "OddEvenGame.h"
#include "Player.h"
#include "RockPaperScissorsGame.h"
#include "RouletteGame.h"

namespace Casino
{
	enum class Tables
	{
		OddOrEvenTable = 1,
		NumberGuessingTable,
		RockPaperScissors,
		GuessTheSquare,
		Roulette,
		ShowGameStats,
		LeaveCasino
	};

	class CasinoHandler
	{
	public:
		CasinoHandler(Player::PlayerInformation& aPlayer, const GameUtilities::GeneralCasinoRules aRules);
		void Start();

	private:
		Player::PlayerInformation& myPLayer;
		const GameUtilities::GeneralCasinoRules myRules;

		GuessTheNumber::GuessTheNumberTable myGuessTheNumber;
		OddEvenGame::OddEvenTable myOddEven;
		GuessTheSquare::GuessTheSquareTable myGuessTheSquare;
		RockPaperScissors::RockPaperScissorsTable myRockPaperScissors;
		Roulette::RouletteTable myRoulette;
	};
}
