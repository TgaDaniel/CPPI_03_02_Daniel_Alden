#include <iostream>
#include "RouletteGame.h"

#include "GameUtilities.h"
#include "IOHandler.h"
#include "RandomHandler.h"

namespace Roulette
{


	/// <summary>
	/// Calulates if number is at a red position on board
	/// </summary>
	/// <param name="aNumber">Number to find out if it is red</param>
	/// <returns>True if it is red</returns>
	bool RouletteTable::CalculateIfNumberIsRed(int aNumber)
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
	/// Adds the roulette game board values to a <c>myGameBoard</c>.
	/// </summary>
	void RouletteTable::InitializeRouletteBoard()
	{
		constexpr int step{ 3 };

		int cellNumber{ 0 };

		for (int columnIndex = 0; columnIndex < myBoardColumnSize; ++columnIndex)
		{

			cellNumber = step - columnIndex; //calculates the first value in the row

			for (int rowIndex = 0; rowIndex < myBoardRowSize; ++rowIndex)
			{
				bool isRed{ CalculateIfNumberIsRed(cellNumber) };
				myGameBoard[columnIndex][rowIndex] = { cellNumber, isRed };

				cellNumber += step;
			}
		}
	}

	void RouletteTable::DisplayGameBoard(bool aShowBallPosition, int aWinningNr)
	{

		std::cout << "\n--------------------------------------------------------------------------------------\n";

		for (int columnIndex = 0; columnIndex < myBoardColumnSize; columnIndex++)
		{
			if (aShowBallPosition && aWinningNr == 0)
			{
				std::cout << "\33[42m| \33[5mX\33[42m |\33[0m ";
			}
			else
			{
				std::cout << "\33[42m| 0 |\33[0m ";
			}

			for (int rowIndex = 0; rowIndex < myBoardRowSize; rowIndex++)
			{
				if (aWinningNr == myGameBoard[columnIndex][rowIndex].cellNumber && aShowBallPosition)
				{
					std::cout << (myGameBoard[columnIndex][rowIndex].isRed ? "\33[41m" : "\33[0m") << "| \33[5mX" << (myGameBoard[columnIndex][rowIndex].isRed ? "\33[41m" : "\33[0m") << " |\33[0m ";
				}
				else
				{
					std::cout << (myGameBoard[columnIndex][rowIndex].isRed ? "\33[41m" : "\33[0m") << "| " << myGameBoard[columnIndex][rowIndex].cellNumber << " |\33[0m ";
				}
			}
			int columnDisplayNumber{ columnIndex + 1 };
			std::cout << "||| Col " << columnDisplayNumber;
			std::cout << "\n--------------------------------------------------------------------------------------\n";
		}


	}

	BetType RouletteTable::ChooseBetType()
	{
		while (true)
		{
			DisplayGameBoard();

			constexpr int options{ 5 };

			std::cout << "\nWhat do you want to bet on?\n"
				<< " [" << static_cast<int>(BetType::Straight) << "] Straight (guess on exact number it will land on) | Win " << myConditions.straightWinMultiplier << "X your bet\n"
				<< " [" << static_cast<int>(BetType::Color) << "] Color (Guess the Color it will land on) | Win " << myConditions.colorWinMultiplier << "X your bet\n"
				<< " [" << static_cast<int>(BetType::OddOrEven) << "] Odd or even number | Win " << myConditions.oddEvenWinMultiplier << "X your money\n"
				<< " [" << static_cast<int>(BetType::Column) << "] Column (Guess the column it will land on) | Win " << myConditions.columnwinMultiplier << "X your bet\n"
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

	int RouletteTable::CalculateColumn(int aNumber)
	{
		int columns{ 3 };

		int modulusResultFirstColumn{ 0 };

		if ((aNumber % columns) == modulusResultFirstColumn) return 1;
		return aNumber % columns;
	}

	void RouletteTable::DisplayPlayerBets(BetType aBetType, int aGuess, bool aDisplayWinning, int aWinningNumber)
	{
		std::cout << "\n\n	Die Game Stats--------\n"
			<< "	-----------------------\n"
			<< "	Money: " << myPLayerInfo.GetMoney() << "$"
			<< "\n	-----------------------\n"
			<< "	Bet: " << myBet << "$"
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
					<< "	Ball: " << (aDisplayWinning ? (GameUtilities::CheckIfEven(aWinningNumber) ? "Even" : "Odd") : "Not rolled yet")
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

	void RouletteTable::HandleWinnings(int aWinMultiplier)
	{
		int winnings{ myBet * aWinMultiplier };

		myTotalWinAmount += winnings - myBet;
		myValueChange += winnings - myBet;

		myPLayerInfo.IncrementallyChangeMoney(winnings);
		myPLayerInfo.AddStatisticsToLastFiveGames(winnings);

		std::cout << "\nYou won " << winnings << "$\n";
		IOHandler::PauseThenClearScreen();
	}

	void RouletteTable::HandleLoss()
	{

		myValueChange -= myBet;

		myPLayerInfo.AddStatisticsToLastFiveGames(-myBet);

		std::cout << "\nYou lost " << myBet << "$\n";
		IOHandler::PauseThenClearScreen();

	}

	RouletteTable::RouletteTable(const RouletteConditions aConditions, Player::PlayerInformation& aPLayerInfo,
		const GameUtilities::GeneralCasinoRules aGeneralRules)
		: myBoardColumnSize(3), myBoardRowSize(12), myConditions(aConditions), myGeneralRules(aGeneralRules),
		myPLayerInfo(aPLayerInfo)
	{
		InitializeRouletteBoard();
		myValueChange = 0;
		myTotalWinAmount = 0;
		myBet = 0;
	}

	void RouletteTable::Play(RandomHandler& aRandomHandler)
	{
		if (myTotalWinAmount > myGeneralRules.maxWinAmountPerTable)
		{
			std::cout << "\nYou are not welcome at this table!\n";
			IOHandler::PauseThenClearScreen();
			return;
		}

		system("cls");

		std::cout << "\nWelcome to the Roulette table " << myPLayerInfo.GetName() << "!\n";

		IOHandler::ReactionText(myGeneralRules, myValueChange, myPLayerInfo);

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

			int winningNumber = aRandomHandler.RandomNumberInRange(0, (myBoardColumnSize * myBoardRowSize));

			system("cls");

			BetType playerChoosenBetType = ChooseBetType();

			switch (playerChoosenBetType)
			{
				case BetType::Straight:
				{

					myBet = GameUtilities::HandleBetting(myPLayerInfo);

					system("cls");
					int playerGuess{ 0 };


					bool guessing{ true };
					while (guessing)
					{

						DisplayPlayerBets(playerChoosenBetType, playerGuess);
						DisplayGameBoard();

						std::cout << "\nWhich number do you think the ball will land on?: ";
						std::cin >> playerGuess;
						if (IOHandler::ValidateInput() && playerGuess >= 0 && playerGuess <= myBoardRowSize * myBoardColumnSize)
						{
							guessing = false;
						}
						else
						{
							std::cout << "\nInvalid input, remember that the number you can guess range from 1 to " << (myBoardColumnSize * myBoardRowSize) << "\n";
							IOHandler::PauseThenClearScreen();
						}
					}

					system("cls");

					DisplayPlayerBets(playerChoosenBetType, playerGuess);
					DisplayGameBoard();

					std::cout << "\nNext the ball will be thrown out and rolled onto the board...\n";
					IOHandler::PauseThenClearScreen();

					if (playerGuess == winningNumber)
					{
						DisplayPlayerBets(playerChoosenBetType, playerGuess, true, winningNumber);
						DisplayGameBoard(true, winningNumber);
						std::cout << "\nYou won with your guess " << playerGuess << "!!!\n";
						IOHandler::HandleAllInWin(myPLayerInfo);
						HandleWinnings(myConditions.straightWinMultiplier);
					}
					else
					{
						DisplayPlayerBets(playerChoosenBetType, playerGuess, true, winningNumber);
						DisplayGameBoard(true, winningNumber);
						std::cout << "\nYou lost with your guess " << playerGuess << "!!!\n";
						HandleLoss();
					}
					break;
				}
				case BetType::Color:
				{
					myBet = GameUtilities::HandleBetting(myPLayerInfo);
					system("cls");

					bool playerGuess{ false };

					DisplayPlayerBets(playerChoosenBetType, playerGuess);
					DisplayGameBoard();

					std::cout << "\n    Which color du you think it will land on?"
						"\n    [R]ed or [B]lack: ";

					playerGuess = IOHandler::TwoCharacterOptionInput('R', 'B');

					system("cls");

					DisplayPlayerBets(playerChoosenBetType, playerGuess);
					DisplayGameBoard();

					std::cout << "\nNow it is time for the ball to be rolled onto the board...\n";

					IOHandler::PauseThenClearScreen();

					if (winningNumber > 0 && playerGuess == CalculateIfNumberIsRed(winningNumber))
					{

						std::cout << "You won with your guess on " << (playerGuess ? "red" : "black") << "!!!\n";

						DisplayPlayerBets(playerChoosenBetType, playerGuess, true, winningNumber);
						DisplayGameBoard(true, winningNumber);
						IOHandler::HandleAllInWin(myPLayerInfo);
						HandleWinnings(myConditions.colorWinMultiplier);
					}
					else
					{
						DisplayPlayerBets(playerChoosenBetType, playerGuess, true, winningNumber);
						DisplayGameBoard(true, winningNumber);
						std::cout << "\nYou lost with your guess...\n";
						HandleLoss();
					}
					break;
				}
				case BetType::OddOrEven:
				{
					myBet = GameUtilities::HandleBetting(myPLayerInfo);
					system("cls");

					bool playerGuess{ false };
					system("cls");

					DisplayPlayerBets(playerChoosenBetType, playerGuess);
					DisplayGameBoard();

					std::cout << "\n	What do you think the ball will land on?\n	 [E]ven or [O]dd number?: ";

					playerGuess = IOHandler::TwoCharacterOptionInput('E', 'O');

					system("cls");
					DisplayPlayerBets(playerChoosenBetType, playerGuess);
					DisplayGameBoard();
					std::cout << "The ball is about to be rolled...\n";
					IOHandler::PauseThenClearScreen();

					if (winningNumber > 0 && playerGuess == GameUtilities::CheckIfEven(winningNumber))
					{
						DisplayPlayerBets(playerChoosenBetType, playerGuess, true, winningNumber);
						DisplayGameBoard(true, winningNumber);
						std::cout << "You won with a guess for " << (playerGuess ? "Even" : "Odd") << " since the ball stopped on " << winningNumber << "\n";
						IOHandler::HandleAllInWin(myPLayerInfo);
						HandleWinnings(myConditions.oddEvenWinMultiplier);
					}
					else
					{
						DisplayPlayerBets(playerChoosenBetType, playerGuess, true, winningNumber);
						DisplayGameBoard(true, winningNumber);

						std::cout << "You lost since the ball landed on the number " << winningNumber << " which is a " << (GameUtilities::CheckIfEven(winningNumber) ? "even" : "odd") << " number\n";
						HandleLoss();
					}

					system("cls");

					break;
				}
				case BetType::Column:
				{
					myBet = GameUtilities::HandleBetting(myPLayerInfo);
					system("cls");

					int columns{ 3 };
					int playerGuess{ 0 };
					bool guessing{ true };
					while (guessing)
					{
						DisplayPlayerBets(playerChoosenBetType, playerGuess);
						DisplayGameBoard();
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

					DisplayPlayerBets(playerChoosenBetType, playerGuess);
					DisplayGameBoard();

					std::cout << "\nThe ball is now being rolled...\n";
					IOHandler::PauseThenClearScreen();

					if (winningNumber > 0 && playerGuess == CalculateColumn(winningNumber))
					{
						DisplayPlayerBets(playerChoosenBetType, playerGuess, true, winningNumber);
						DisplayGameBoard(true, winningNumber);

						std::cout << "You guessed right with column " << playerGuess << "\n";
						IOHandler::HandleAllInWin(myPLayerInfo);
						HandleWinnings(myConditions.columnwinMultiplier);
					}
					else
					{
						DisplayPlayerBets(playerChoosenBetType, playerGuess, true, winningNumber);
						DisplayGameBoard(true, winningNumber);
						std::cout << "You were wrong with column " << playerGuess << " the ball landed on column " << CalculateColumn(winningNumber) << "\n";
						HandleLoss();
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
			if (!myPLayerInfo.HasMoney())
			{
				return;
			}
			if (myTotalWinAmount > myGeneralRules.maxWinAmountPerTable)
			{
				std::cout << "\nYou've won too much, you can't play at this table anymore!!!\n";
				IOHandler::PauseThenClearScreen();
				return;
			}
			myPLayerInfo.DisplayLastFiveGameStatistics();
			IOHandler::PauseThenClearScreen();
		}
	}
}
