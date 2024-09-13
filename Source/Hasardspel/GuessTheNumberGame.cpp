#include <iostream>

#include "GuessTheNumberGame.h"
#include "IOHandler.h"
#include "RandomHandler.h"

namespace GuessTheNumber
{
	void GuessTheNumberTable::DisplayGuessNumberGameStatBoard() const
	{
		std::cout << "\n\n	Die Game Stats--------\n"
			<< "	-----------------------\n"
			<< "	Player guess: " << myGuess
			<< "\n	-----------------------\n"
			<< "	Money: " << myPlayerInfo.GetMoney() << "$"
			<< "\n	-----------------------\n"
			<< "	Bet: " << myBet << "$"
			<< "\n	-----------------------\n"
			<< "	Die 1: " << myFirstDie
			<< "\n	-----------------------\n"
			<< "	Die 2: " << mySecondDie
			<< "\n	-----------------------\n"
			<< "	Winning result: " << myFirstDie << " + " << mySecondDie << " = " << myFirstDie + mySecondDie
			<< "\n	-----------------------\n\n";
	}

	GuessTheNumberTable::GuessTheNumberTable( int aWinMultiplier, Player::PlayerInformation& aPlayerInformation, GameUtilities::GeneralCasinoRules aRules)
	: myConditions({1,6,aWinMultiplier}), myPlayerInfo(aPlayerInformation),myGeneralRules(aRules)
	{
		myBet = 0;
		myFirstDie = 0;
		mySecondDie = 0;
		myGuess = 0;
		myTotalValueChange = 0;
		myTotalWinAmount = 0;
	}

	void GuessTheNumberTable::Play(RandomHandler& aRandomHandler)
	{
		if (myTotalWinAmount >= myGeneralRules.maxWinAmountPerTable)
		{
			std::cout << "\nYou are not allowed at this table anymore after winning so much. Leave!\n";
			IOHandler::PauseThenClearScreen();
			return;
		}

		system("cls");

		std::cout << "\nWelcome to the number guessing game!!! \n";

		IOHandler::ReactionText(myGeneralRules, myTotalValueChange);

		std::cout << "\nWant the game explained to you? (y/n): ";

		if (IOHandler::TwoCharacterOptionInput('y', 'n'))
		{
			std::cout << "Two " << myConditions.maxRandomValue << " sided die will be thrown and YOU will get to guess what the added value of the die are!!!\n"
				<< "Guess right and you WIN!!! Guess wrong and you LOSE!!!\n\n"
				<< "Your money will be multiplied by " << myConditions.winMultiplier << " if you win\n";
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

			int numberOfDice{ 2 };
			myFirstDie = 0;
			mySecondDie = 0;
			myGuess = 0;
			bool guessing{ true };

			while (guessing)
			{

				myBet = GameUtilities::HandleBetting(myPlayerInfo);

				DisplayGuessNumberGameStatBoard();
				std::cout << "\nGuess the number you think the two dice will land on: ";
				std::cin >> myGuess;

				if (IOHandler::ValidateInput() && myGuess >= myConditions.minRandomValue * numberOfDice && myGuess <= myConditions.maxRandomValue * numberOfDice)
				{
					guessing = false;
					std::cout << "\nYou have guessed!\n"
						<< "When you are ready to throw the first die \n";

					IOHandler::PauseThenClearScreen();

					myFirstDie = aRandomHandler.RandomNumberInRange(myConditions.minRandomValue, myConditions.maxRandomValue);

					DisplayGuessNumberGameStatBoard();
					std::cout << "\nFirst die: " << myFirstDie << "\n\nWhen you are ready throw the second die \n\n";
					IOHandler::PauseThenClearScreen();

					mySecondDie = aRandomHandler.RandomNumberInRange(myConditions.minRandomValue, myConditions.minRandomValue);

					DisplayGuessNumberGameStatBoard();
					std::cout << "\nSecond die: " << mySecondDie << "!\n";

					int winningNr{ myFirstDie + mySecondDie };
					if (myGuess == winningNr)
					{
						std::cout << "\nWhich means you WIN!!!\n you guessed the right number!\n";
						IOHandler::HandleAllInWin(myPlayerInfo);
						myPlayerInfo.IncrementallyChangeMoney(myBet * myConditions.winMultiplier);
						myPlayerInfo.AddStatisticsToLastFiveGames(  (myBet * myConditions.winMultiplier));

						myTotalValueChange += (myBet * myConditions.winMultiplier) - myBet;

						myTotalWinAmount += (myBet * myConditions.winMultiplier) - myBet;
						if (myTotalWinAmount >= myGeneralRules.maxWinAmountPerTable)
						{
							std::cout << "\nYou've won to much at this table and a guard escorts you from it\n";
							IOHandler::PauseThenClearScreen();
							return;
						}
					}
					else
					{
						std::cout << "\nWhich mean you lost with a number " << (myGuess < winningNr ? "too low..." : "too high...") << " since the added value of both die is: "
							<< winningNr << "\nBetter luck next time!\n";
						myTotalValueChange -= (myBet * myConditions.winMultiplier) - myBet;
						myPlayerInfo.AddStatisticsToLastFiveGames( -myBet);
					}
				}
				else
				{
					system("cls");
					std::cout << "\nInvalid input...\n" << "Note: Two " << myConditions.maxRandomValue << " sided die can't have a value less then "
						<< myConditions.minRandomValue * numberOfDice << " or more then " << myConditions.maxRandomValue * numberOfDice << "\n";
					IOHandler::PauseThenClearScreen();
				}
			}

			if (!myPlayerInfo.HasMoney())
			{
				return;
			}
			IOHandler::PauseThenClearScreen();
			
			myPlayerInfo.DisplayLastFiveGameStatistics();

			DisplayGuessNumberGameStatBoard();

			std::cout << "\nPlay again? (y/n):";
		} while (IOHandler::TwoCharacterOptionInput('y', 'n'));
		std::cout << "\nCome back soon!\n";
	}

}
