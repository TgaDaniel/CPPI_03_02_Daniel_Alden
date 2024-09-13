#include <iostream>

#include "RockPaperScissorsGame.h"
#include "GameUtilities.h"
#include "IOHandler.h"
#include "RandomHandler.h"

namespace RockPaperScissors
{

	void RockPaperScissorsTable::DisplayRockPaperScissorsGameStatBoard(bool aHiddenOpponent)
	{
		std::cout
			<< "	-----------------------\n"
			<< "	" << myPLayerInfo.GetName() << " hand: " << (myPlayerHand == SelectHand::Rock
				? "ROCK"
				: (myPlayerHand == SelectHand::Paper
					? "PAPER"
					: "SCISSORS"))
			<< "\n	-----------------------\n"
			<< "	OPPONENT HAND 1: " << (aHiddenOpponent
				? "Not revealed"
				: (myPlayerHand == SelectHand::Rock
					? "ROCK"
					: (myPlayerHand == SelectHand::Paper
						? "PAPER"
						: "SCISSORS")))
			<< "\n	-----------------------\n"
			<< "	Money: " << myPLayerInfo.GetMoney() << "$"
			<< "\n	-----------------------\n"
			<< "	Bet: " << myBet << "$"
			<< "\n	-----------------------\n";
	}

	RockPaperScissorsTable::RockPaperScissorsTable(int aWinMultiplier,
		Player::PlayerInformation aPlayerInfo, GameUtilities::GeneralCasinoRules aRules)
		: myConditions({ 1,3,aWinMultiplier }), myPLayerInfo(aPlayerInfo), myGeneralRules(aRules)
	{
		myBet = 0;
		myPlayerHand = SelectHand::Rock;
		myTotalValueChange = 0;
		myTotalWinAmount = 0;

	}

	void RockPaperScissorsTable::Play(RandomHandler& aRandomHandler)
	{
		if (myTotalWinAmount >= myGeneralRules.maxWinAmountPerTable)
		{
			std::cout << "\nYou can't play at this table anymore punk!\n";
			IOHandler::PauseThenClearScreen();
			return;
		}

		system("cls");

		std::cout << "\nWelcome to the Rock Paper Scissors table!\n";

		IOHandler::ReactionText(myGeneralRules, myTotalValueChange, myPLayerInfo);

		std::cout << "\nWant to hear the rules?(y/n): ";

		if (IOHandler::TwoCharacterOptionInput('y', 'n'))
		{
			std::cout << "It's simple, you choose either rock, paper or scissors and the house also choose one.\n"
				<< "If your choice beat ours you WIN!\n"
				<< "But if you choose the same or yours don't bet mine you LOSE!\n"
				<< "You win " << myConditions.winMultiplier << " times what you bet!\n\n";
		}

		std::cout << "Want to play?(y/n): ";

		while (IOHandler::TwoCharacterOptionInput('y', 'n'))
		{
			system("cls");
			myBet = GameUtilities::HandleBetting(myPLayerInfo);
			bool selectingHand{ true };

			while (selectingHand)
			{

				system("cls");

				SelectHand opponentHand = static_cast<SelectHand>(aRandomHandler.RandomNumberInRange(1, 3));
				bool playerHasWinningHand{ false };


				std::cout << "\nRock[" << static_cast<int>(SelectHand::Rock) << "]\n"
					<< "Paper[" << static_cast<int>(SelectHand::Paper) << "]\n"
					<< "Scissors[" << static_cast<int>(SelectHand::Scissors) << "]\n\n"
					<< "Choose: ";

				int playerInput{ 0 };
				std::cin >> playerInput;

				if (IOHandler::ValidateInput() && playerInput >= myConditions.minRandomValue && playerInput <= myConditions.maxRandomValue)
				{
					selectingHand = false;
					system("cls");

					myPlayerHand = static_cast<SelectHand>(playerInput);

					DisplayRockPaperScissorsGameStatBoard(true);
					std::cout << "Opponent slowly reveals their hand...\n";
					IOHandler::PauseThenClearScreen();

					DisplayRockPaperScissorsGameStatBoard();

					if (myPlayerHand == opponentHand)
					{
						std::cout << "\nThe opponent and you have the same hand and the house wins by default\n";
					}
					else
					{
						switch (myPlayerHand)
						{
							case SelectHand::Rock:
							{
								if (opponentHand == SelectHand::Paper)
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
							case SelectHand::Paper:
							{
								if (opponentHand == SelectHand::Scissors)
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
							case SelectHand::Scissors:
							{
								if (opponentHand == SelectHand::Rock)
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
					DisplayRockPaperScissorsGameStatBoard();
					if (playerHasWinningHand)
					{
						myPLayerInfo.IncrementallyChangeMoney(myBet * myConditions.winMultiplier);
						myTotalWinAmount += (myBet * myConditions.winMultiplier) - myBet;
						myTotalValueChange += (myBet * myConditions.winMultiplier) - myBet;
						myPLayerInfo.AddStatisticsToLastFiveGames(myBet * myConditions.winMultiplier);

						std::cout << "Which means you WON!\n"
							<< "You win " << myBet * myConditions.winMultiplier << "$\n";

						IOHandler::HandleAllInWin(myPLayerInfo);

						if (myTotalWinAmount >= myGeneralRules.maxWinAmountPerTable)
						{
							std::cout << "\nYou've won to much at this table and a guard escorts you from it\n";
							IOHandler::PauseThenClearScreen();
							return;
						}
					}
					else
					{

						myTotalValueChange -= (myBet * myConditions.winMultiplier) - myBet;
						myPLayerInfo.AddStatisticsToLastFiveGames(-myBet);

						std::cout << "Which means you LOSE!\n"
							<< "You lose " << myBet << "$\n";
					}

					IOHandler::PauseThenClearScreen();
					myPLayerInfo.DisplayLastFiveGameStatistics();
					IOHandler::HandleAllInWin(myPLayerInfo);
					myPLayerInfo.DisplayMoney();
					std::cout << "\nPlay again?(y/n): ";
				}
				else
				{
					system("cls");
					std::cout << "\nInvalid input...\n";
					IOHandler::PauseThenClearScreen();
				}
				if (!myPLayerInfo.HasMoney())
				{
					return;
				}
			}
		}
		std::cout << "\nSee you soon\n";
		IOHandler::PauseThenClearScreen();
	}

}
