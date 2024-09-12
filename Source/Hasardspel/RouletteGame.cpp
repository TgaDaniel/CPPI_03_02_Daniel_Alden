#include <iostream>
#include "RouletteGame.h"

#include "GameUtilities.h"
#include "IOHandler.h"
#include "RandomHandler.h"

namespace Roulette
{
	//Number
	//column
	//Color
	//odd or even


	enum class BetType
	{
		Straight = 1,
		Color,
		OddOrEven,
		Column,
		Leave
	};

	constexpr int BOARD_COLUMN_SIZE{ 3 };
	constexpr int BOARD_ROW_SIZE{ 12 };

	/// <summary>
	/// Calulates if number is at a red position on board
	/// </summary>
	/// <param name="aNumber">Number to find out if it is red</param>
	/// <returns>True if it is red</returns>
	bool CalculateIfNumberIsRed(int aNumber)
	{
		constexpr int redIsOddInRangeAmount{ 2 };
		int redIsOddStartRanges[redIsOddInRangeAmount] = { 1,19 };
		int redIsOddEndRanges[redIsOddInRangeAmount] = { 10,28 };

		bool isRed = GameUtilities::CheckIfEven(aNumber);

		for (int i = 0; i <= redIsOddInRangeAmount; ++i)
		{
			for (int j = redIsOddStartRanges[i]; j <= redIsOddEndRanges[i]; j++)
			{
				if (aNumber == j)
				{
					return !isRed;
				}
			}
		}
		return isRed;
	}

	/// <summary>
	/// Adds the roulette game board values to a game board.
	/// </summary>
	/// <param name="aGameBoard"></param>
	void InitializeRouletteBoard(CellValues aGameBoard[BOARD_COLUMN_SIZE][BOARD_ROW_SIZE])
	{
		constexpr int step{ 3 };

		int cellNumber{ 0 };

		for (int columnIndex = 0; columnIndex < BOARD_COLUMN_SIZE; ++columnIndex)
		{

			cellNumber = step - columnIndex; //calculates the first value in the row

			for (int rowIndex = 0; rowIndex < BOARD_ROW_SIZE; ++rowIndex)
			{
				bool isRed{ CalculateIfNumberIsRed(cellNumber) };
				aGameBoard[columnIndex][rowIndex] = { cellNumber, isRed };

				cellNumber += step;
			}
		}
	}

	void DisplayGameBoard(CellValues aGameBoard[BOARD_COLUMN_SIZE][BOARD_ROW_SIZE], bool aShowBallPosition = false, int aWinningNr = 0)
	{

		std::cout << "\n--------------------------------------------------------------------------------------\n";

		for (int columnIndex = 0; columnIndex < BOARD_COLUMN_SIZE; columnIndex++)
		{
			if (aShowBallPosition && aWinningNr == 0)
			{
				std::cout << "\33[42m| \33[5mX\33[42m |\33[0m ";
			}
			else
			{
				std::cout << "\33[42m| 0 |\33[0m ";
			}

			for (int rowIndex = 0; rowIndex < BOARD_ROW_SIZE; rowIndex++)
			{
				if (aWinningNr == aGameBoard[columnIndex][rowIndex].cellNumber && aShowBallPosition)
				{
					std::cout << (aGameBoard[columnIndex][rowIndex].isRed ? "\33[41m" : "\33[0m") << "| \33[5mX" << (aGameBoard[columnIndex][rowIndex].isRed ? "\33[41m" : "\33[0m") << " |\33[0m ";
				}
				else
				{
					std::cout << (aGameBoard[columnIndex][rowIndex].isRed ? "\33[41m" : "\33[0m") << "| " << aGameBoard[columnIndex][rowIndex].cellNumber << " |\33[0m ";
				}
			}
			int columnDisplayNumber{ columnIndex + 1 };
			std::cout << "||| Col " << columnDisplayNumber;
			std::cout << "\n--------------------------------------------------------------------------------------\n";
		}


	}

	BetType ChooseBetType(RouletteConditions aConditions, CellValues aBoard[3][12])
	{
		while (true)
		{
			DisplayGameBoard(aBoard);

			constexpr int options{ 5 };

			std::cout << "\nWhat do you want to bet on?\n"
				<< " [" << static_cast<int>(BetType::Straight) << "] Straight (guess on exact number it will land on) | Win " << aConditions.straightWinMultiplier << "X your bet\n"
				<< " [" << static_cast<int>(BetType::Color) << "] Color (Guess the Color it will land on) | Win " << aConditions.colorWinMultiplier << "X your bet\n"
				<< " [" << static_cast<int>(BetType::OddOrEven) << "] Odd or even number | Win " << aConditions.oddEvenWinMultiplier << "X your money\n"
				<< " [" << static_cast<int>(BetType::Column) << "] Column (Guess the column it will land on) | Win " << aConditions.columnwinMultiplier << "X your bet\n"
				<< " [" << static_cast<int>(BetType::Leave) << "] Leave table\n"
				<< "Input: ";

			int playerInput{ 0 };
			std::cin >> playerInput;
			if (IOHandler::ValidateInput() && playerInput > 0 && playerInput <= options)
			{
				system("cls");
				return static_cast<BetType>(playerInput);
			}

			system("cls");
			std::cout << "Invalid input...\n";
			IOHandler::PauseThenClearScreen();
		}
	}

	int CalculateColumn(int aNumber)
	{
		int columns{ 3 };

		int modulusResultFirstColumn{ 0 };

		if ((aNumber % columns) == modulusResultFirstColumn) return 1;
		return aNumber % columns;
	}

	void DisplayPlayerBets(Player::PlayerInformation& aPlayerInformation, BetType aBetType, int aGuess, int aBet, bool aDisplayWinning = false, int aWinningNumber = 0)
	{
		std::cout << "\n\n	Die Game Stats--------\n"
			<< "	-----------------------\n"
			<< "	Money: " << aPlayerInformation.GetMoney() << "$"
			<< "\n	-----------------------\n"
			<< "	Bet: " << aBet << "$"
			<< "\n	-----------------------\n";

		switch (aBetType)
		{
			case BetType::Straight:
			{
				std::cout
					<< "	Player guess: " << aGuess
					<< "\n	-----------------------\n"
					<< "	Ball: " << (aDisplayWinning ? aWinningNumber : 0)
					<< "\n	-----------------------\n\n";

				break;
			}
			case BetType::Color:
			{
				std::cout
					<< "	Player guess: " << (aGuess > 0 ? "\33[31mRED\33[0m" : "BLACK")
					<< "\n	-----------------------\n"
					<< "	Ball: " << (aDisplayWinning ? CalculateIfNumberIsRed(aWinningNumber) ? "\33[31mRED\33[m" : "BLACK" : "Not rolled yet")
					<< "\n	-----------------------\n\n";

				break;
			}
			case BetType::OddOrEven:
			{
				std::cout
					<< "	Player guess: " << (aGuess > 0 ? "Even" : "Odd")
					<< "\n	-----------------------\n"
					<< "	Ball: " <<  ( aDisplayWinning ? (GameUtilities::CheckIfEven(aWinningNumber) ? "Even" : "Odd") : "Not rolled yet")
					<< "\n	-----------------------\n\n";

				break;
			}
			case BetType::Column:
			{
				std::cout
					<< "	Player guess: " << aGuess
					<< "\n	-----------------------\n"
					<< "	Ball Column: " << (aDisplayWinning ? (CalculateColumn(aWinningNumber)) : 0)
					<< "\n	-----------------------\n\n";
				break;
			}
			case BetType::Leave: default:
			{
				std::cout << "\nInvalid display data error\n";
			}
		}
	}

	void HandleWinnings(Player::PlayerInformation& aPLayer, int aWinMultiplier, int aBet, int& aTotalWinAmountAtTable, int& aValueChangeAtTable)
	{
		int winnings{ aBet * aWinMultiplier };

		aTotalWinAmountAtTable += winnings - aBet;
		aValueChangeAtTable += winnings - aBet;

		aPLayer.IncrementallyChangeMoney(winnings);
		aPLayer.AddStatisticsToLastFiveGames( winnings);

		std::cout << "\nYou won " << winnings << "$\n";
		IOHandler::PauseThenClearScreen();
	}

	void HandleLoss(Player::PlayerInformation& aPLayer, int aBet, int& aValueChangeAtTable)
	{

		aValueChangeAtTable -= aBet;

		aPLayer.AddStatisticsToLastFiveGames( -aBet);

		std::cout << "\nYou lost " << aBet << "$\n";
		IOHandler::PauseThenClearScreen();

	}

	void RouletteGame(RouletteConditions aConditions, GameUtilities::GeneralCasinoRules aGeneralRules, Player::PlayerInformation& aPLayerInfo)
	{

		CellValues gameBoard[BOARD_COLUMN_SIZE][BOARD_ROW_SIZE];
		InitializeRouletteBoard(gameBoard);

		static int totalWinAmount{ 0 };
		static int valueChange{ 0 };

		if (totalWinAmount > aGeneralRules.maxWinAmountPerTable)
		{
			std::cout << "\nYou are not welcome at this table!\n";
			IOHandler::PauseThenClearScreen();
			return;
		}

		system("cls");

		std::cout << "\nWelcome to the Roulette table!\n";

		IOHandler::ReactionText(aGeneralRules, valueChange);

		std::cout << "Want to hear the rules?(y/n):"; 

		if (IOHandler::TwoCharacterOptionInput('y', 'n'))
		{
			std::cout << "You'll guess where a ball will stop after being rolled onto the board here."
				"\nDepending on the type of bet you decide to go with you'll either win or lose based one if your guess was right\n";
			IOHandler::PauseThenClearScreen();
		}

		system("cls");

		bool playing{ true };

		while (playing)
		{
			int bet;
			int winningNumber = RandomHandler::RandomNumberInRange(0, (BOARD_COLUMN_SIZE * BOARD_ROW_SIZE));

			system("cls");

			BetType playerChoosenBetType = ChooseBetType(aConditions, gameBoard);

			switch (playerChoosenBetType)
			{
				case BetType::Straight:
				{

					bet = GameUtilities::HandleBetting(aPLayerInfo);

					system("cls");
					int playerGuess{ 0 };


					bool guessing{ true };
					while (guessing)
					{

						DisplayPlayerBets(aPLayerInfo, playerChoosenBetType, playerGuess, bet);
						DisplayGameBoard(gameBoard);

						std::cout << "\nWhich number do you think the ball will land on?: ";
						std::cin >> playerGuess;
						if (IOHandler::ValidateInput() && playerGuess >= 0 && playerGuess <= BOARD_ROW_SIZE * BOARD_COLUMN_SIZE)
						{
							guessing = false;
						}
						else
						{
							std::cout << "\nInvalid input, remember that the number you can guess range from 1 to " << (BOARD_COLUMN_SIZE * BOARD_ROW_SIZE) << "\n";
							IOHandler::PauseThenClearScreen();
						}
					}

					system("cls");

					DisplayPlayerBets(aPLayerInfo, playerChoosenBetType, playerGuess, bet);
					DisplayGameBoard(gameBoard);

					std::cout << "\nNext the ball will be thrown out and rolled onto the board...\n";
					IOHandler::PauseThenClearScreen();

					if (playerGuess == winningNumber)
					{
						DisplayPlayerBets(aPLayerInfo, playerChoosenBetType, playerGuess, bet, true, winningNumber);
						DisplayGameBoard(gameBoard, true, winningNumber);
						std::cout << "\nYou won with your guess " << playerGuess << "!!!\n";
						IOHandler::HandleAllInWin(aPLayerInfo);
						HandleWinnings(aPLayerInfo, aConditions.straightWinMultiplier, bet, totalWinAmount, valueChange);
					}
					else
					{
						DisplayPlayerBets(aPLayerInfo, playerChoosenBetType, playerGuess, bet, true, winningNumber);
						DisplayGameBoard(gameBoard, true, winningNumber);
						std::cout << "\nYou lost with your guess " << playerGuess << "!!!\n";
						HandleLoss(aPLayerInfo,bet,valueChange);
					}
					break;
				}
				case BetType::Color:
				{
					bet = GameUtilities::HandleBetting(aPLayerInfo);
					system("cls");

					bool playerGuess{ false };

					DisplayPlayerBets(aPLayerInfo, playerChoosenBetType, playerGuess, bet);
					DisplayGameBoard(gameBoard);

					std::cout << "\n    Which color du you think it will land on?"
						"\n    [R]ed or [B]lack: ";

					playerGuess = IOHandler::TwoCharacterOptionInput('R', 'B');

					system("cls");

					DisplayPlayerBets(aPLayerInfo, playerChoosenBetType, playerGuess, bet);
					DisplayGameBoard(gameBoard);

					std::cout << "\nNow it is time for the ball to be rolled onto the board...\n";

					IOHandler::PauseThenClearScreen();

					if (winningNumber > 0, playerGuess == CalculateIfNumberIsRed(winningNumber))
					{

						std::cout << "You won with your guess on " << (playerGuess ? "red" : "black") << "!!!\n";

						DisplayPlayerBets(aPLayerInfo, playerChoosenBetType, playerGuess, bet, true, winningNumber);
						DisplayGameBoard(gameBoard, true, winningNumber);
						IOHandler::HandleAllInWin(aPLayerInfo);
						HandleWinnings(aPLayerInfo, aConditions.colorWinMultiplier, bet, totalWinAmount, valueChange);
					}
					else
					{
						DisplayPlayerBets(aPLayerInfo, playerChoosenBetType, playerGuess, bet, true, winningNumber);
						DisplayGameBoard(gameBoard, true, winningNumber);
						std::cout << "\nYou lost with your guess...\n";
						HandleLoss(aPLayerInfo, bet, valueChange);
					}
					break;
				}
				case BetType::OddOrEven:
				{
					bet = GameUtilities::HandleBetting(aPLayerInfo);
					system("cls");

					bool playerGuess{false};
					system("cls");

					DisplayPlayerBets(aPLayerInfo, playerChoosenBetType, playerGuess, bet);
					DisplayGameBoard(gameBoard);

					std::cout << "\n	What do you think the ball will land on?\n	 [E]ven or [O]dd number?: ";

					playerGuess = IOHandler::TwoCharacterOptionInput('E', 'O');

					system("cls");
					DisplayPlayerBets(aPLayerInfo, playerChoosenBetType, playerGuess, bet);
					DisplayGameBoard(gameBoard);
					std::cout << "The ball is about to be rolled...\n";
					IOHandler::PauseThenClearScreen();

					if (winningNumber > 0 && playerGuess == GameUtilities::CheckIfEven(winningNumber))
					{
						DisplayPlayerBets(aPLayerInfo, playerChoosenBetType, playerGuess, bet, true, winningNumber);
						DisplayGameBoard(gameBoard, true, winningNumber);
						std::cout << "You won with a guess for " << (playerGuess ? "Even" : "Odd") << " since the ball stopped on " << winningNumber << "\n";
						IOHandler::HandleAllInWin(aPLayerInfo);
						HandleWinnings(aPLayerInfo, aConditions.oddEvenWinMultiplier, bet, totalWinAmount, valueChange);
					}
					else
					{
						DisplayPlayerBets(aPLayerInfo, playerChoosenBetType, playerGuess, bet, true, winningNumber);
						DisplayGameBoard(gameBoard, true, winningNumber);

						std::cout << "You lost since the ball landed on the number " << winningNumber << " which is a " << (GameUtilities::CheckIfEven(winningNumber) ? "even" : "odd") << " number\n";
						HandleLoss(aPLayerInfo, bet, valueChange);
					}

					system("cls");

					break;
				}
				case BetType::Column:
				{
					bet = GameUtilities::HandleBetting(aPLayerInfo);
					system("cls");

					int columns{ 3 };
					int playerGuess{0};
					bool guessing{ true };
					while (guessing)
					{
						DisplayPlayerBets(aPLayerInfo, playerChoosenBetType, playerGuess, bet);
						DisplayGameBoard(gameBoard);
						std::cout << "\nWhich column do you think the ball will land on?\nInput: ";
						std::cin >> playerGuess;
						if (IOHandler::ValidateInput() && playerGuess > 0 && playerGuess <= columns)
						{
							guessing = false;
						}
						else
						{
							std::cout << "\nInvalid input... You can see the column numbers to the right of the game board...\n";
							IOHandler::PauseThenClearScreen();
						}
					}
					system("cls");

					DisplayPlayerBets(aPLayerInfo, playerChoosenBetType, playerGuess, bet);
					DisplayGameBoard(gameBoard);

					std::cout << "\nThe ball is now being rolled...\n";
					IOHandler::PauseThenClearScreen();

					if (winningNumber > 0 && playerGuess == CalculateColumn(winningNumber))
					{
						DisplayPlayerBets(aPLayerInfo, playerChoosenBetType, playerGuess, bet, true, winningNumber);
						DisplayGameBoard(gameBoard, true, winningNumber);

						std::cout << "You guessed right with column " << playerGuess << "\n";
						IOHandler::HandleAllInWin(aPLayerInfo);
						HandleWinnings(aPLayerInfo, aConditions.columnwinMultiplier, bet, totalWinAmount, valueChange);
					}
					else
					{
						DisplayPlayerBets(aPLayerInfo, playerChoosenBetType, playerGuess, bet, true, winningNumber);
						DisplayGameBoard(gameBoard, true, winningNumber);
						std::cout << "You were wrong with column " << playerGuess << " the ball landed on column " << CalculateColumn(winningNumber) << "\n";
						HandleLoss(aPLayerInfo, bet, valueChange);
					}

					break;
				}
				case BetType::Leave:
				{
					system("cls");
					playing = false;
					break;
				}
			}
			if(!aPLayerInfo.HasMoney())
			{
				return;
			}
			if(totalWinAmount > aGeneralRules.maxWinAmountPerTable)
			{
				std::cout << "\nYou've won too much, you can't play at this table anymore!!!\n";
				IOHandler::PauseThenClearScreen();
				return;
			}
			aPLayerInfo.DisplayLastFiveGameStatistics();
			IOHandler::PauseThenClearScreen();
		}
	}
}
