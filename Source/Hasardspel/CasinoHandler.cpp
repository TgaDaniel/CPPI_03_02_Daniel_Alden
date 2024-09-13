#include <iostream>

#include "CasinoHandler.h"

#include "GuessTheNumberGame.h"
#include "IOHandler.h"
#include "RandomHandler.h"


namespace Casino
{

	CasinoHandler::CasinoHandler(Player::PlayerInformation& aPlayer, const GameUtilities::GeneralCasinoRules aRules, RandomHandler& aRandomHandler)
		:
		myPLayer(aPlayer), myRules(aRules),
		myRandomHandler(aRandomHandler),
		myGuessTheNumberLowStake(3, aPlayer, aRules, { 10,100 }),
		myGuessTheNumberHighStake(5, aPlayer, aRules, { 100,500 }),
		myOddEven(2, aPlayer, aRules),
		myGuessTheSquare(3, aPlayer, aRules),
		myRockPaperScissors(2, aPlayer, aRules),
		myRoulette({}, aPlayer, aRules)
	{
	}

	void CasinoHandler::Start()
	{
		bool playing{ true };
		while (playing)
		{
			system("cls");
			myPLayer.DisplayMoney();
			std::cout << "Which table do you want to sit at?\n\n"
				<< "Even or Odd table [" << static_cast<int>(Tables::OddOrEvenTable) << "]\n"
				<< "High Stake Guess the number table [" << static_cast<int>(Tables::HighStakeNumberGuessing) << "]\n"
				<< "Low Stake Guess the number table [" << static_cast<int>(Tables::LowStakeNumberGuessing) << "]\n"
				<< "Rock Paper Scissors table [" << static_cast<int>(Tables::RockPaperScissors) << "]\n"
				<< "Guess the square table [" << static_cast<int>(Tables::GuessTheSquare) << "]\n"
				<< "Roulette table [" << static_cast<int>(Tables::Roulette) << "]\n"
				<< "Show last 5 games statistics [" << static_cast<int>(Tables::ShowGameStats) << "]\n"
				<< "Leave casino [" << static_cast<int>(Tables::LeaveCasino) << "]\n";

			std::cout << "\nInput: ";

			int userInput;
			std::cin >> userInput;

			if (IOHandler::ValidateInput())
			{

				switch (static_cast<Tables>(userInput)) {
					case Tables::HighStakeNumberGuessing:
					{
						myGuessTheNumberLowStake.Play(myRandomHandler);
						break;
					}
					case Tables::LowStakeNumberGuessing:
					{
						myGuessTheNumberHighStake.Play(myRandomHandler);
						break;
					}
					case Tables::OddOrEvenTable:
					{
						myOddEven.Play(myRandomHandler);
						break;
					}
					case Tables::RockPaperScissors:
					{
						myRockPaperScissors.Play(myRandomHandler);
						break;
					}
					case Tables::GuessTheSquare:
					{
						myGuessTheSquare.Play(myRandomHandler);
						break;
					}
					case Tables::Roulette:
					{
						myRoulette.Play(myRandomHandler);
						break;
					}
					case Tables::ShowGameStats:
					{
						myPLayer.DisplayLastFiveGameStatistics();
						IOHandler::PauseThenClearScreen();
						break;
					}
					case Tables::LeaveCasino:
					{
						playing = false;
						myPLayer.DisplayLastFiveGameStatistics();
						std::cout << "\nCome back soon!\n";
						system("pause");
						break;
					}
					default:
					{
						std::cout << "\nInvalid input\n";
						system("pause");
						break;
					}
				}
			}
			else
			{
				std::cout << "\nInvalid input\n";
				system("pause");
			}
			if (!myPLayer.HasMoney())
			{
				if (myPLayer.GetAllIn())
				{
					std::cout << "\n\nThe casino owner laughs and motions the guards before losing interest in you and continuing to look around the casinos for other people in misfortune";
					IOHandler::PauseThenClearScreen();
				}
				std::cout << "\n\nWith no money left the casino see no more use for you and throw you out forcibly.\n"
					<< "You came here with hopes and dreams that are all crushed now with no more money in your pockets.\n";
				myPLayer.DisplayMoney();
				playing = false;
				system("pause");
			}
		}
	}
}
