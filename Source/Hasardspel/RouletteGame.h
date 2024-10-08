#pragma once
#include "GameUtilities.h"
#include "Player.h"
#include "RandomHandler.h"

namespace Roulette
{
	enum class BetType
	{
		Straight = 1,
		Color,
		OddOrEven,
		Column,
		Leave
	};

	struct CellValues
	{
		int cellNumber = 0;
		bool isRed = false;
	};

	struct RouletteConditions
	{
		int straightWinMultiplier = 5;
		int colorWinMultiplier = 3;
		int oddEvenWinMultiplier = 3;
		int columnwinMultiplier = 2;
	};

	class RouletteTable
	{
	public:
		RouletteTable(const RouletteConditions aConditions, Player::PlayerInformation& aPLayerInfo, const GameUtilities::GeneralCasinoRules aGeneralRules);

		void Play(RandomHandler& aRandomHandler);

	private:

		const int myBoardColumnSize;
		const int myBoardRowSize;

		CellValues myGameBoard[3][12];

		int myTotalWinAmount;
		int myValueChange;

		int myBet;

		const RouletteConditions myConditions;
		const GameUtilities::GeneralCasinoRules myGeneralRules;
		Player::PlayerInformation& myPLayerInfo;

		void InitializeRouletteBoard();
		void DisplayGameBoard(bool aShowBallPosition = false, int aWinningNr = 0);
		int CalculateColumn(int aNumber);
		bool CalculateIfNumberIsRed(int aNumber);
		BetType ChooseBetType();
		void DisplayPlayerBets(BetType aBetType, int aGuess, bool aDisplayWinning = false, int aWinningNumber = 0);
		void HandleWinnings(int aWinMultiplier);
		void HandleLoss();
	};


}
