#include "GuessTheSquareGame.h"

#include <iostream>

#include "CasinoHandler.h"
#include "GameUtilities.h"
#include "IOHandler.h"
#include "RandomHandler.h"

namespace GuessTheSquare
{

	void GuessTheSquareTable::DisplaySquares(int aDisplaySquare) const
	{
		std::cout << "\n";

		for (int i = 0; i < mySquares.size(); i++)
		{
			if (i == aDisplaySquare)
			{
				std::cout << "[" << (mySquares[i] ? "*" : " ") << "] ";
			}
			else
			{
				std::cout << "[X] ";
			}
		}
		std::cout << "\n";
	}


	void GuessTheSquareTable::DisplaySquares() const
	{
		std::cout << "\n";

		for (int i = 1; i <= myConditions.maxRandomValue; i++)
		{
			std::cout << "[" << i << "] ";
		}

		std::cout << "\n";
	}

	GuessTheSquareTable::GuessTheSquareTable(int aWinMultiplier, Player::PlayerInformation& aPlayerInfo,
		const GameUtilities::GeneralCasinoRules aGeneralRules)
		: myConditions({ 1, 5, aWinMultiplier }), myPLayerInfo(aPlayerInfo),
		myGeneralRules(aGeneralRules)

	{
		mySquares = { false };
		myTotalWinAmount = 0;
		myTotalValueChange = 0;
	}

	void GuessTheSquareTable::Play(RandomHandler& aRandomHandler)
	{
		static int totalWinAmount{ 0 };
		static int valueChangeAmount{ 0 };


		if (totalWinAmount >= myGeneralRules.maxWinAmountPerTable)
		{
			std::cout << "\nYou are not allowed at this table anymore after winning so much. Leave!\n";
			IOHandler::PauseThenClearScreen();
			return;
		}

		system("cls");

		std::cout << "\nWelcome to Guess the square table!\n";

		IOHandler::ReactionText(myGeneralRules, valueChangeAmount, myPLayerInfo);

		std::cout << "\nWant the game explained?(y/n):";

		if (IOHandler::TwoCharacterOptionInput('y', 'n'))
		{
			system("cls");
			std::cout << "The game is simple, you get to guess in which box of the " << mySquares.size() << " we have here a star is hidden in.\nYou get one try and if you don't find the star you lose"
				<< "\nIf you get it your bet is given back multiplied by " << myConditions.winMultiplier << ".\n";
		}

		std::cout << "\nWant to play? (y/n):";

		int bet{ 0 };

		while (IOHandler::TwoCharacterOptionInput('y', 'n'))
		{
			for (int i = 0; i < mySquares.size(); i++)
			{
				mySquares[i] = false;
			}

			system("cls");

			bet = GameUtilities::HandleBetting(myPLayerInfo);



			bool choosing{ true };

			while (choosing)
			{

				int indexWithStarIn{ aRandomHandler.RandomNumberInRange(myConditions.minRandomValue, myConditions.maxRandomValue) - 1 };
				mySquares[indexWithStarIn] = true;
				DisplaySquares();
				std::cout << "In which box do you think the star will be?\nInput: ";

				int playerInput;
				std::cin >> playerInput;

				if (IOHandler::ValidateInput() && playerInput > 0 && playerInput < mySquares.size())
				{
					choosing = false;
					system("cls");

					int indexGuess = playerInput - 1;

					if (indexGuess == indexWithStarIn)
					{
						myPLayerInfo.IncrementallyChangeMoney(bet * myConditions.winMultiplier);

						myPLayerInfo.AddStatisticsToLastFiveGames((bet * myConditions.winMultiplier));

						totalWinAmount += (bet * myConditions.winMultiplier) - bet;
						valueChangeAmount += (bet * myConditions.winMultiplier) - bet;

						DisplaySquares(indexGuess);

						std::cout << "\nYou guessed right! which means you win " << bet * myConditions.winMultiplier << "$\n";
						if (totalWinAmount >= myGeneralRules.maxWinAmountPerTable)
						{
							std::cout << "\nYou've won to much at this table and a guard escorts you from it\n";
							IOHandler::HandleAllInWin(myPLayerInfo);

							if (totalWinAmount >= myGeneralRules.maxWinAmountPerTable)
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
						myPLayerInfo.AddStatisticsToLastFiveGames(-bet);
						valueChangeAmount -= bet;
						DisplaySquares(indexGuess);
						std::cout << "\nIt's empty...\n";
						IOHandler::PauseThenClearScreen();

						DisplaySquares(indexWithStarIn);
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

			if (!myPLayerInfo.HasMoney())
			{
				return;
			}
			myPLayerInfo.SetAllIn(false);

			myPLayerInfo.DisplayLastFiveGameStatistics();
			std::cout << "\nPlay again?(y/n):";
		}
	}

}
