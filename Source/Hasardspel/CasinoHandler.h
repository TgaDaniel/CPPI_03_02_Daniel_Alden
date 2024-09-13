#pragma once
#include "GameUtilities.h"
#include "GuessTheNumberGame.h"
#include "GuessTheSquareGame.h"
#include "OddEvenGame.h"
#include "Player.h"
#include "RandomHandler.h"
#include "RockPaperScissorsGame.h"
#include "RouletteGame.h"

namespace Casino
{
	enum class Tables
	{
		OddOrEvenTable = 1,
		HighStakeNumberGuessing,
		LowStakeNumberGuessing,
		RockPaperScissors,
		GuessTheSquare,
		Roulette,
		ShowGameStats,
		LeaveCasino
	};

	class CasinoHandler
	{
	public:
		CasinoHandler() = delete;
		CasinoHandler(Player::PlayerInformation& aPlayer, const GameUtilities::GeneralCasinoRules aRules, RandomHandler& aRandomHandler);
		void Start();

	private:
		Player::PlayerInformation& myPLayer;
		const GameUtilities::GeneralCasinoRules myRules;
		RandomHandler& myRandomHandler;

		GuessTheNumber::GuessTheNumberTable myGuessTheNumberLowStake;
		GuessTheNumber::GuessTheNumberTable myGuessTheNumberHighStake;
		OddEvenGame::OddEvenTable myOddEven;
		GuessTheSquare::GuessTheSquareTable myGuessTheSquare;
		RockPaperScissors::RockPaperScissorsTable myRockPaperScissors;
		Roulette::RouletteTable myRoulette;
	};
}
