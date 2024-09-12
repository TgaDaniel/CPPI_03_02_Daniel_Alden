#include <iostream>

#include "RockPaperScissorsGame.h"

#include "GameUtilities.h"
#include "IOHandler.h"
#include "RandomHandler.h"

namespace RockPaperScissors
{
	enum class RockPaperScissors
	{
		Rock = 1,
		Paper,
		Scissors
	};

	void DisplayRockPaperScissorsGameStatBoard(const RockPaperScissors aPlayerHand,
		const RockPaperScissors aOpponentHand,
		int aBet, const Player::PlayerInformation& aPLayerInformation,
		bool aHiddenOpponent = false)
	{
		std::cout
			<< "	-----------------------\n"
			<< "	Player hand: " << (aPlayerHand == RockPaperScissors::Rock
				? "ROCK"
				: (aPlayerHand == RockPaperScissors::Paper
					? "PAPER"
					: "SCISSORS"))
			<< "\n	-----------------------\n"
			<< "	OPPONENT HAND 1: " << (aHiddenOpponent
				? "Not revealed"
				: (aOpponentHand == RockPaperScissors::Rock
					? "ROCK"
					: (aOpponentHand == RockPaperScissors::Paper
						? "PAPER"
						: "SCISSORS")))
			<< "\n	-----------------------\n"
			<< "	Money: " << aPLayerInformation.GetMoney() << "$"
			<< "\n	-----------------------\n"
			<< "	Bet: " << aBet << "$"
			<< "\n	-----------------------\n";
	}

	void RockPaperScissorsGame(const GameUtilities::GameConditions aConditions, const GameUtilities::GeneralCasinoRules aGeneralRules, Player::PlayerInformation& aPlayerInformation)
	{
		static int totalWinAmount;
		static int totalValueChange;

		if (totalWinAmount >= aGeneralRules.maxWinAmountPerTable)
		{
			std::cout << "\nYou can't play at this table anymore punk!\n";
			IOHandler::PauseThenClearScreen();
			return;
		}

		system("cls");

		std::cout << "\nWelcome to the Rock Paper Scissors table!\n";

		if (totalValueChange <= -aGeneralRules.reactionAmount)
		{
			std::cout << "\nBetter luck this time, i'm sure you'll win.\n";
		}
		else if (totalValueChange >= aGeneralRules.reactionAmount)
		{
			std::cout << "\nThe big winner is back huh? Share some of that luck will ya?\n";
		}
		else
		{
			std::cout << "\nThis will be fun!\n";
		}
		std::cout << "\nWant to hear the rules?(y/n): ";

		if (IOHandler::TwoCharacterOptionInput('y', 'n'))
		{
			std::cout << "It's simple, you choose either rock, paper or scissors and the house also choose one.\n"
				<< "If your choice beat ours you WIN!\n"
				<< "But if you choose the same or yours don't bet mine you LOSE!\n"
				<< "You win " << aConditions.winMultiplier << " times what you bet!\n\n";
		}

		std::cout << "Want to play?(y/n): ";

		while (IOHandler::TwoCharacterOptionInput('y', 'n'))
		{
			system("cls");
			int amountBet{ GameUtilities::HandleBetting(aPlayerInformation) };
			bool selectingHand{ true };

			while (selectingHand)
			{

				system("cls");

				RockPaperScissors opponentHand = static_cast<RockPaperScissors>(RandomHandler::RandomNumberInRange(1, 3));
				bool playerHasWinningHand{ false };


				std::cout << "\nRock[" << static_cast<int>(RockPaperScissors::Rock) << "]\n"
					<< "Paper[" << static_cast<int>(RockPaperScissors::Paper) << "]\n"
					<< "Scissors[" << static_cast<int>(RockPaperScissors::Scissors) << "]\n\n"
					<< "Choose: ";

				int playerInput{ 0 };
				std::cin >> playerInput;

				if (IOHandler::ValidateInput() && playerInput >= aConditions.minRandomValue && playerInput <= aConditions.maxRandomValue)
				{
					selectingHand = false;
					system("cls");

					RockPaperScissors playerHand = static_cast<RockPaperScissors>(playerInput);

					DisplayRockPaperScissorsGameStatBoard(playerHand, opponentHand, amountBet, aPlayerInformation, true);
					std::cout << "Opponent slowly reveals their hand...\n";
					IOHandler::PauseThenClearScreen();

					DisplayRockPaperScissorsGameStatBoard(playerHand, opponentHand, amountBet, aPlayerInformation);

					if (playerHand == opponentHand)
					{
						std::cout << "\nThe opponent and you have the same hand and the house wins by default\n";
					}
					else
					{
						switch (playerHand)
						{
						case RockPaperScissors::Rock:
						{
							if (opponentHand == RockPaperScissors::Paper)
							{
								std::cout << "Rock loses to Paper\n";
							}
							else
							{
								std::cout << "Rock wins over Scissors!\n";
								playerHasWinningHand = true;
							}
							break;
						}
						case RockPaperScissors::Paper:
						{
							if (opponentHand == RockPaperScissors::Scissors)
							{
								std::cout << "Paper loses to Scissors\n";
							}
							else
							{
								std::cout << "Paper wins over Rock!\n";
								playerHasWinningHand = true;
							}
							break;
						}
						case RockPaperScissors::Scissors:
						{
							if (opponentHand == RockPaperScissors::Rock)
							{
								std::cout << "Scissors loses to Rock\n";
							}
							else
							{
								std::cout << "Scissors win over Paper!\n";
								playerHasWinningHand = true;
							}
							break;
						}
						}
					}
					IOHandler::PauseThenClearScreen();
					DisplayRockPaperScissorsGameStatBoard(playerHand, opponentHand, amountBet, aPlayerInformation);
					if (playerHasWinningHand)
					{
						aPlayerInformation.IncrementallyChangeMoney(amountBet * aConditions.winMultiplier);
						totalWinAmount += (amountBet * aConditions.winMultiplier) - amountBet;
						totalValueChange += (amountBet * aConditions.winMultiplier) - amountBet;
						aPlayerInformation.AddStatisticsToLastFiveGames( amountBet * aConditions.winMultiplier);

						std::cout << "Which means you WON!\n"
							<< "You win " << amountBet * aConditions.winMultiplier << "$\n";

						IOHandler::HandleAllInWin(aPlayerInformation);

						if (totalWinAmount >= aGeneralRules.maxWinAmountPerTable)
						{
							std::cout << "\nYou've won to much at this table and a guard escorts you from it\n";
							IOHandler::PauseThenClearScreen();
							return;
						}
					}
					else
					{

						totalValueChange -= (amountBet * aConditions.winMultiplier) - amountBet;
						aPlayerInformation.AddStatisticsToLastFiveGames( -amountBet);

						std::cout << "Which means you LOSE!\n"
							<< "You lose " << amountBet << "$\n";
					}

					IOHandler::PauseThenClearScreen();
					aPlayerInformation.DisplayLastFiveGameStatistics();
					IOHandler::HandleAllInWin(aPlayerInformation);
					aPlayerInformation.DisplayMoney();
					std::cout << "\nPlay again?(y/n): ";
				}
				else
				{
					system("cls");
					std::cout << "\nInvalid input...\n";
					IOHandler::PauseThenClearScreen();
				}
				if (!aPlayerInformation.HasMoney())
				{
					return;
				}
			}
		}
		std::cout << "\nSee you soon\n";
		IOHandler::PauseThenClearScreen();
	}

}
