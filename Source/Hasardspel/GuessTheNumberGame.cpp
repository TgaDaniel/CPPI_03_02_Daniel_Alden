#include <iostream>

#include "GuessTheNumberGame.h"
#include "IOHandler.h"
#include "RandomHandler.h"

namespace GuessTheNumber
{
	void DisplayGuessNumberGameStatBoard(const int aGuess, const int aFirstDie, const int aSecondDie, const int aBet, const GameUtilities::PlayerInformation& aPlayerInfo)
	{
		std::cout << "\n\n	Die Game Stats--------\n"
			<< "	-----------------------\n"
			<< "	Player guess: " << aGuess
			<< "\n	-----------------------\n"
			<< "	Money: " << aPlayerInfo.money << "$"
			<< "\n	-----------------------\n"
			<< "	Bet: " << aBet << "$"
			<< "\n	-----------------------\n"
			<< "	Die 1: " << aFirstDie
			<< "\n	-----------------------\n"
			<< "	Die 2: " << aSecondDie
			<< "\n	-----------------------\n"
			<< "	Winning result: " << aFirstDie << " + " << aSecondDie << " = " << aFirstDie + aSecondDie
			<< "\n	-----------------------\n\n";
	}

	void GuessTheNumberGame(const GameUtilities::GameConditions& aConditions, GameUtilities::PlayerInformation& aPlayerInfo, const GameUtilities::GeneralCasinoRules aGeneralRules)
	{

		static int totalWinAmountGuessingGame{ 0 };
		static int totalValueChangeGuessingGame{ 0 };


		if (totalWinAmountGuessingGame >= aGeneralRules.maxWinAmountPerTable)
		{
			std::cout << "\nYou are not allowed at this table anymore after winning so much. Leave!\n";
			IOHandler::PauseThenClearScreen();
			return;
		}

		system("cls");

		std::cout << "\nWelcome to the number guessing game!!! \n";

		if (totalValueChangeGuessingGame <= -aGeneralRules.reactionAmount)
		{
			std::cout << "\nBetter luck this time, i'm sure you'll win.\n";
		}
		else if (totalValueChangeGuessingGame >= aGeneralRules.reactionAmount)
		{
			std::cout << "\nThe big winner is back huh? Share some of that luck will ya?\n";
		}
		else
		{
			std::cout << "\nThis will be fun!\n";
		}
		std::cout << "\nWant the game explained to you? (y/n): ";

		if (IOHandler::TwoCharacterOptionInput('y', 'n'))
		{
			std::cout << "Two " << aConditions.maxRandomValue << " sided die will be thrown and YOU will get to guess what the added value of the die are!!!\n"
				<< "Guess right and you WIN!!! Guess wrong and you LOSE!!!\n\n"
				<< "Your money will be multiplied by " << aConditions.winMultiplier << " if you win\n";
		}

		std::cout << "Want to sit down and play?(y/n): ";

		//returns player from function if 'n' is input
		if (!IOHandler::TwoCharacterOptionInput('y', 'n'))
		{
			std::cout << "\nOkay, come back when you feel braver.\n";
			system("pause");
			return;
		}

		do
		{

			system("cls");

			int betAmount{ 0 };

			int numberOfDice{ 2 };
			int firstDie{ 0 };
			int secondDie{ 0 };
			int guess{ 0 };

			bool guessing{ true };

			while (guessing)
			{

				betAmount = GameUtilities::HandleBetting(aPlayerInfo);

				DisplayGuessNumberGameStatBoard(guess, firstDie, secondDie, betAmount,aPlayerInfo);
				std::cout << "\nGuess the number you think the two dice will land on: ";
				std::cin >> guess;

				if (IOHandler::ValidateInput() && guess >= aConditions.minRandomValue * numberOfDice && guess <= aConditions.maxRandomValue * numberOfDice)
				{
					guessing = false;
					std::cout << "\nYou have guessed!\n"
						<< "When you are ready to throw the first die \n";

					IOHandler::PauseThenClearScreen();

					firstDie = RandomHandler::RandomNumberInRange(aConditions.minRandomValue, aConditions.maxRandomValue);

					DisplayGuessNumberGameStatBoard(guess, firstDie, secondDie, betAmount, aPlayerInfo);
					std::cout << "\nFirst die: " << firstDie << "\n\nWhen you are ready throw the second die \n\n";
					IOHandler::PauseThenClearScreen();

					secondDie = RandomHandler::RandomNumberInRange(aConditions.minRandomValue, aConditions.minRandomValue);

					DisplayGuessNumberGameStatBoard(guess, firstDie, secondDie, betAmount, aPlayerInfo);
					std::cout << "\nSecond die: " << secondDie << "!\n";

					int winningNr{ firstDie + secondDie };
					if (guess == winningNr)
					{
						std::cout << "\nWhich means you WIN!!!\n you guessed the right number!\n";
						if (aPlayerInfo.allIn)
						{
							std::cout << "\n\nThe casino owner scoffs and look away.\nPeople applaud while you are being paid out\n";
						}
						aPlayerInfo.money += betAmount * aConditions.winMultiplier;
						GameUtilities::AddStatisticsToLastFiveGamesArray(aPlayerInfo, (betAmount * aConditions.winMultiplier));

						totalValueChangeGuessingGame += (betAmount * aConditions.winMultiplier) - betAmount;

						totalWinAmountGuessingGame += (betAmount * aConditions.winMultiplier) - betAmount;
						if (totalWinAmountGuessingGame >= aGeneralRules.maxWinAmountPerTable)
						{
							std::cout << "\nYou've won to much at this table and a guard escorts you from it\n";
							IOHandler::PauseThenClearScreen();
							return;
						}
					}
					else
					{
						std::cout << "\nWhich mean you lost with a number " << (guess < winningNr ? "too low..." : "too high...") << " since the added value of both die is: "
							<< winningNr << "\nBetter luck next time!\n";
						totalValueChangeGuessingGame -= (betAmount * aConditions.winMultiplier) - betAmount;
						GameUtilities::AddStatisticsToLastFiveGamesArray(aPlayerInfo, -betAmount);
					}
				}
				else
				{
					system("cls");
					std::cout << "\nInvalid input...\n" << "Note: Two " << aConditions.maxRandomValue << " sided die can't have a value less then "
						<< aConditions.minRandomValue * numberOfDice << " or more then " << aConditions.maxRandomValue * numberOfDice << "\n";
					IOHandler::PauseThenClearScreen();
				}
			}

			if (!GameUtilities::CheckPlayerHasMoney(aPlayerInfo))
			{
				return;
			}
			IOHandler::PauseThenClearScreen();
			aPlayerInfo.allIn = false;
			
			GameUtilities::DisplayLastFiveGameStatistics(aPlayerInfo);

			DisplayGuessNumberGameStatBoard(guess, firstDie, secondDie, betAmount, aPlayerInfo);

			std::cout << "\nPlay again? (y/n):";
		} while (IOHandler::TwoCharacterOptionInput('y', 'n'));
		std::cout << "\nCome back soon!\n";
	}

}
