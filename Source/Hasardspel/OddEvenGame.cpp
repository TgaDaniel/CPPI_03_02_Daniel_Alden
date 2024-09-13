#include <iostream>

#include "GameUtilities.h"
#include "IOHandler.h"
#include "RandomHandler.h"
#include "OddEvenGame.h"

namespace OddEvenGame
{

	void OddEvenTable::DisplayOddOrEvenGameStatBoard(const bool aGuess, const int aFirstDie, const int aSecondDie)
	{
		const bool isEven = GameUtilities::CheckIfEven(aSecondDie);

		const bool houseDefaultWin{GameUtilities::CheckIfEven(aFirstDie) != GameUtilities::CheckIfEven(aSecondDie) && aSecondDie > 0 };

		std::cout << "\n\n	Die Game Stats--------\n"
			<< "	-----------------------\n"
			<< "	Player guess: " << (aGuess ? "Even" : "Odd")
			<< "\n	-----------------------\n"
			<< "	Money: " << myPLayerInfo.GetMoney() << "$"
			<< "\n	-----------------------\n"
			<< "	Bet: " << myBet << "$"
			<< "\n	-----------------------\n"
			<< "	Die 1: " << (aFirstDie <= 0 ? "Not rolled yet" : GameUtilities::CheckIfEven(aFirstDie) ? "Even" : "Odd")
			<< "\n	-----------------------\n"
			<< "	Die 2: " << (aSecondDie <= 0 ? "Not rolled yet" : GameUtilities::CheckIfEven(aSecondDie) ? "Even" : "Odd")
			<< "\n	-----------------------\n"
			<< "	Winning result: " << (aSecondDie > 0 ? houseDefaultWin ? "The house wins..." : isEven ? "Even" : "Odd" : "Not decided yet")
			<< "\n	-----------------------\n\n";
	}

	OddEvenTable::OddEvenTable(int aWinMultiplier,
		Player::PlayerInformation& aPLayerInfo, const GameUtilities::GeneralCasinoRules aGeneralRules)
	:myConditions({1,6, aWinMultiplier}), myPLayerInfo(aPLayerInfo), myGeneralRules(aGeneralRules)
	{
		myTotalValueChangeOddOrEven = 0;
		myTotalWinAmountOddOrEven = 0;
		myBet = 0;
	}

	void OddEvenTable::Play(RandomHandler& aRandomHandler)
	{

		if (myTotalWinAmountOddOrEven >= myGeneralRules.maxWinAmountPerTable)
		{
			std::cout << "\nYou're not allowed to play at this table anymore!\n";
			IOHandler::PauseThenClearScreen();
			return;
		}

		system("cls");
		std::cout << "Welcome to the Even or Odd guessing game!!!\n";

		if (myTotalValueChangeOddOrEven <= -myGeneralRules.reactionAmount)
		{
			std::cout << "\nBetter luck this time, i'm sure you'll win.\n\n";
		}
		else if (myTotalValueChangeOddOrEven >= myGeneralRules.reactionAmount)
		{
			std::cout << "\nThe big winner is back huh? Share some of that luck will ya?\n\n";
		}
		else
		{
			std::cout << "\nThis will be fun!\n";
		}

		std::cout << "Want the game explained to you?(y/n):";

		if (IOHandler::TwoCharacterOptionInput('y', 'n'))
		{
			std::cout << "\nThe game is simple, you will guess if both die will show either even or odd numbers after thrown."
				"\nIf the numbers on one die is even and odd on the other you lose automatically.\n"
				"Your money will be multiplied by " << myConditions.winMultiplier << " if you win\n";
		}

		std::cout << "\nWant to sit down and play?(y/n): ";

		while (IOHandler::TwoCharacterOptionInput('y', 'n'))
		{
			int firstDie{ 0 };
			int secondDie{ 0 };

			bool guess{ false };

			system("cls");

			myBet = GameUtilities::HandleBetting(myPLayerInfo);

			std::cout << "\nDo you think the dice will land on an [E]ven or [O]dd number?: ";
			guess = IOHandler::TwoCharacterOptionInput('E', 'O');
			system("cls");
			DisplayOddOrEvenGameStatBoard(guess, firstDie, secondDie);

			std::cout << "\nWhen you are ready to throw the first die\n";
			IOHandler::PauseThenClearScreen();

			firstDie = aRandomHandler.RandomNumberInRange(myConditions.minRandomValue, myConditions.maxRandomValue);

			DisplayOddOrEvenGameStatBoard(guess, firstDie, secondDie);
			std::cout << "\nThe fist die landed on " << firstDie;

			std::cout << "\n\nThrow the second die\n";

			IOHandler::PauseThenClearScreen();

			secondDie = aRandomHandler.RandomNumberInRange(myConditions.minRandomValue, myConditions.maxRandomValue);

			DisplayOddOrEvenGameStatBoard(guess, firstDie, secondDie);
			std::cout << "\nThe second die landed on " << secondDie << "\n";

			if (GameUtilities::CheckIfEven(firstDie) == GameUtilities::CheckIfEven(secondDie))
			{
				if (guess == GameUtilities::CheckIfEven(firstDie))
				{
					std::cout << "\nYou guessed right! The dice are " << (guess ? "Even" : "Odd") << "!!!\n";
					IOHandler::HandleAllInWin(myPLayerInfo);

					myPLayerInfo.AddStatisticsToLastFiveGames( (myBet * myConditions.winMultiplier));

					myTotalValueChangeOddOrEven += (myBet * myConditions.winMultiplier) - myBet;

					myTotalWinAmountOddOrEven += (myBet * myConditions.winMultiplier) - myBet;
					myPLayerInfo.IncrementallyChangeMoney(myBet * myConditions.winMultiplier);

					if (myTotalWinAmountOddOrEven >= myGeneralRules.maxWinAmountPerTable)
					{
						std::cout << "\nSince you've won to much at this table a guard escorts you from the table\n";
						IOHandler::PauseThenClearScreen();
						return;
					}
				}
				else
				{
					std::cout << "\nYour guess was wrong and the dice were " << (!guess ? "Even" : "Odd") << "!!!\n";
					myPLayerInfo.AddStatisticsToLastFiveGames( -myBet);
					myTotalValueChangeOddOrEven -= myBet;
				}
			}
			else
			{
				std::cout << "\nSince the numbers on the dice are both even and uneven the house wins and you lose.\n\nBetter luck next time\n";
				myPLayerInfo.AddStatisticsToLastFiveGames( -myBet);
				myTotalValueChangeOddOrEven -= myBet;
			}

			if (!myPLayerInfo.HasMoney())
			{
				return;
			}
			myPLayerInfo.SetAllIn(false);

			IOHandler::PauseThenClearScreen();

			myPLayerInfo.DisplayLastFiveGameStatistics();

			DisplayOddOrEvenGameStatBoard(guess, firstDie, secondDie);

			std::cout << "\nPlay again?(y/n):";
		}
	}
}
