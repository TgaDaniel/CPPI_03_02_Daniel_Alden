#include <iostream>

#include "CasinoHandler.h"

#include "GuessTheNumberGame.h"
#include "IOHandler.h"


namespace Casino
{

	CasinoHandler::CasinoHandler(Player::PlayerInformation& aPlayer, const GameUtilities::GeneralCasinoRules aRules)
		: myPLayer(aPlayer), myRules(aRules)
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
				<< "Guess the number table [" << static_cast<int>(Tables::NumberGuessingTable) << "]\n"
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
					case Tables::NumberGuessingTable:
					{
						break;
					}
					case Tables::OddOrEvenTable:
					{
						OddEvenGame::OddOrEvenGame({ 1,6,2 }, player, rules);
						break;
					}
					case Tables::RockPaperScissors:
					{
						RockPaperScissors::Play({ 1,3,3 }, rules, player);
						break;
					}
					case Tables::GuessTheSquare:
					{
						bool squareArray[5] = { false };
						GuessTheSquare::Play(squareArray, 5, { 1,5,3 }, player, rules);
						break;
					}
					case Tables::Roulette:
					{
						Roulette::Play({ 5,2,2,3 }, rules, player);
						break;
					}
					case Tables::ShowGameStats:
					{
						GameUtilities::DisplayLastFiveGameStatistics(player);
						IOHandler::PauseThenClearScreen();
						break;
					}
					case Tables::LeaveCasino:
					{
						playing = false;
						GameUtilities::DisplayLastFiveGameStatistics(player);
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
			if (!GameUtilities::CheckPlayerHasMoney(player))
			{
				if (player.allIn)
				{
					std::cout << "\n\nThe casino owner laughs and motions the guards before losing interest in you and continuing to look around the casinos for other people in misfortune";
					IOHandler::PauseThenClearScreen();
				}
				std::cout << "\n\nWith no money left the casino see no more use for you and throw you out forcibly.\n"
					<< "You came here with hopes and dreams that are all crushed now with no more money in your pockets.\n";
				GameUtilities::DisplayMoney(player.money);
				playing = false;
				system("pause");
			}
		}
	}

}