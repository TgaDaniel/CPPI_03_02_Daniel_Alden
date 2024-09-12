#include "GuessTheSquareGame.h"

#include <iostream>

#include "GameUtilities.h"
#include "IOHandler.h"
#include "RandomHandler.h"

namespace GuessTheSquare
{

	void DisplaySquares(bool aSquareArray[], int aArraySize, int aDisplaySquare)
	{
		std::cout << "\n";
		for (int i = 0; i < aArraySize; i++)
		{
			if (i == aDisplaySquare)
			{
				std::cout << "[" << (aSquareArray[i] ? "*" : " ") << "] ";
			}
			else
			{
				std::cout << "[X] ";
			}
		}
		std::cout << "\n";
	}


	void DisplaySquares(GameUtilities::GameConditions aConditions)
	{
		std::cout << "\n";

		for (int i = 1; i <= aConditions.maxRandomValue; i++)
		{
			std::cout << "[" << i << "] ";
		}

		std::cout << "\n";
	}

	void GuessTheSquareGame(bool aSquareArray[], int aSquareArraySize, const GameUtilities::GameConditions aConditions, GameUtilities::PlayerInformation& aPlayerInfo, const GameUtilities::GeneralCasinoRules aGeneralRules)
	{
		static int totalWinAmount{ 0 };
		static int valueChangeAmount{ 0 };


		if (totalWinAmount >= aGeneralRules.maxWinAmountPerTable)
		{
			std::cout << "\nYou are not allowed at this table anymore after winning so much. Leave!\n";
			IOHandler::PauseThenClearScreen();
			return;
		}

		system("cls");

		std::cout << "\nWelcome to Guess the square table!\n";

		if (valueChangeAmount <= -aGeneralRules.reactionAmount)
		{
			std::cout << "\nBetter luck this time, i'm sure you'll win.\n";
		}
		else if (valueChangeAmount >= aGeneralRules.reactionAmount)
		{
			std::cout << "\nThe big winner is back huh? Share some of that luck will ya?\n";
		}
		else
		{
			std::cout << "\nThis will be fun!\n";
		}

		std::cout << "\nWant the game explained?(y/n):";

		if (IOHandler::TwoCharacterOptionInput('y', 'n'))
		{
			system("cls");
			std::cout << "The game is simple, you get to guess in which box of the " << aSquareArraySize << " we have here a star is hidden in.\nYou get one try and if you don't find the star you lose"
				<< "\nIf you get it your bet is given back multiplied by " << aConditions.winMultiplier << ".\n";
		}

		std::cout << "\nWant to play? (y/n):";

		int bet{ 0 };

		while (IOHandler::TwoCharacterOptionInput('y', 'n'))
		{
			for (int i = 0; i < aSquareArraySize; i++)
			{
				aSquareArray[i] = false;
			}

			system("cls");

			bet = GameUtilities::HandleBetting(aPlayerInfo);

			DisplaySquares(aConditions);


			bool choosing{ true };

			while (choosing)
			{

				int indexWithStarIn{ RandomHandler::RandomNumberInRange(aConditions.minRandomValue, aConditions.maxRandomValue) - 1 };
				aSquareArray[indexWithStarIn] = true;
				std::cout << "In which box do you think the star will be?\nInput: ";

				int playerInput;
				std::cin >> playerInput;

				if (IOHandler::ValidateInput() && playerInput > 0 && playerInput <= aSquareArraySize )
				{
					choosing = false;
					system("cls");

					int indexGuess = playerInput - 1;

					if (indexGuess == indexWithStarIn)
					{
						aPlayerInfo.money += bet * aConditions.winMultiplier;

						GameUtilities::AddStatisticsToLastFiveGamesArray(aPlayerInfo, (bet * aConditions.winMultiplier));

						totalWinAmount += (bet * aConditions.winMultiplier) - bet;
						valueChangeAmount += (bet * aConditions.winMultiplier) - bet;

						DisplaySquares(aSquareArray, aSquareArraySize, indexGuess);

						std::cout << "\nYou guessed right! which means you win " << bet * aConditions.winMultiplier << "$\n";
						if (totalWinAmount >= aGeneralRules.maxWinAmountPerTable)
						{
							std::cout << "\nYou've won to much at this table and a guard escorts you from it\n";
							if (aPlayerInfo.allIn)
							{
								std::cout << "\n\nThe casino owner scoffs and look away.\nPeople applaud while you are being paid out\n";
							}

							if (totalWinAmount >= aGeneralRules.maxWinAmountPerTable)
							{
								std::cout << "\nYou've won to much at this table and a guard escorts you from it\n";
								IOHandler::PauseThenClearScreen();
								return;
							}

							IOHandler::PauseThenClearScreen();
							return;
						}
						IOHandler::PauseThenClearScreen();
					}
					else
					{
						GameUtilities::AddStatisticsToLastFiveGamesArray(aPlayerInfo, -bet);
						valueChangeAmount -= bet;
						DisplaySquares(aSquareArray, aSquareArraySize, indexGuess);
						std::cout << "\nIt's empty...\n";
						IOHandler::PauseThenClearScreen();

						DisplaySquares(aSquareArray, aSquareArraySize, indexWithStarIn);
						std::cout << "\nThe right value is in box " << indexWithStarIn + 1 << " and you lost " << bet << "$\n";
						IOHandler::PauseThenClearScreen();
					}
				}
				else
				{
					std::cout << "Invalid input...";
					IOHandler::PauseThenClearScreen();
				}
			}

			if (!GameUtilities::CheckPlayerHasMoney(aPlayerInfo))
			{
				return;
			}
			aPlayerInfo.allIn = false;

			GameUtilities::DisplayLastFiveGameStatistics(aPlayerInfo);
			std::cout << "\nPlay again?(y/n):";
		}
	}
}
