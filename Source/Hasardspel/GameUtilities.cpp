#include <iostream>

#include "GameUtilities.h"
#include "IOHandler.h"

namespace GameUtilities
{
	void DisplayMoney(const int aPlayerMoney)
	{
		std::cout << "\n-------------------------\n"
			<< "Money: " << aPlayerMoney << "$"
			<< "\n-------------------------\n\n";
	}

	int HandleBetting(PlayerInformation& aPlayerInfo)
	{
		while (true)
		{

			DisplayMoney(aPlayerInfo.money);
			std::cout << "\nHow much do you want to bet?: ";

			int betAmount{ 0 };
			std::cin >> betAmount;
			if (IOHandler::ValidateInput() && betAmount > 0 && betAmount <= aPlayerInfo.money)
			{
				if (betAmount == aPlayerInfo.money)
				{
					aPlayerInfo.allIn = true;
					system("cls");
					std::cout << "\n\n*The casino quiets down and everyone looks at you. You feel the tension and weight of this decision*\n*Whatever the outcome, this decision will be life changing, either for good or bad*\n"
						<< "\n\n!!!You have just gone all in!!!\n\n";
					IOHandler::PauseThenClearScreen();
					std::cout << "\n\nThe owner of the casino looks down on you from on top of his comically villainous throne and a large evil grin spread along his face\n'The house always wins' He thinks\n";
					IOHandler::PauseThenClearScreen();
				}
				aPlayerInfo.money -= betAmount;
				std::cout << "\nYou now have " << aPlayerInfo.money << "$\nGood Luck\n";
				IOHandler::FlushCinBuffer();
				return betAmount;
			}
			system("cls");
			std::cout << "\nInvalid amount.\n";
			IOHandler::PauseThenClearScreen();
		}

	}

	/// <summary>
	///  Checks if player have money in their account by passing the PlayerInformation object reference
	/// </summary>
	/// <returns>True if there is money. False if there is no money</returns>
	bool CheckPlayerHasMoney(const PlayerInformation& aPLayerInfo)
	{
		constexpr int noMoney{ 0 };
		return aPLayerInfo.money > noMoney;
	}

	/// <summary>
	/// Handles adding of money statistics to the <c>lastFiveGamesStatistics array</c> in the <c>PlayerInformation struct</c>. Where 0 equals no play
	/// </summary>
	/// <param name="aPlayerInfo">Information about the player passed in with the <c>PlayerInformation</c> struct as a reference </param>
	/// <param name="aMoney">The amount of money won or lost. If lost enter negative amount instead of positive</param>
	void AddStatisticsToLastFiveGamesArray(PlayerInformation& aPlayerInfo, const int aMoney)
	{

		constexpr int arraysLastIndex{ 4 };
		constexpr int  integerToReplace{ 0 };

		//If aGameStatistics last placement isn't 0 then you can change the values
		if (aPlayerInfo.lastFiveGamesStatistics[arraysLastIndex] != integerToReplace)
		{
			for (int i = 0; i <= arraysLastIndex; ++i)
			{
				if (i != 0)
				{
					int previousIndex{ i - 1 };
					aPlayerInfo.lastFiveGamesStatistics[previousIndex] = aPlayerInfo.lastFiveGamesStatistics[i];
				}

				if (i == 4)
				{
					aPlayerInfo.lastFiveGamesStatistics[i] = aMoney;
					return;
				}
			}
		}

		for (int& gameStatistic : aPlayerInfo.lastFiveGamesStatistics)
		{
			if (gameStatistic == integerToReplace)
			{
				gameStatistic = aMoney;
				return;
			}
		}

	}

	void DisplayLastFiveGameStatistics(const PlayerInformation& aPlayerInfo)
	{
		system("cls");


		constexpr int noValue{ 0 };
		if (aPlayerInfo.lastFiveGamesStatistics[0] == noValue)
		{
			std::cout << "\nNo games played yet.\n";
			return;
		}

		std::cout << "\n\nGeneral Game statistics----"
			<< "\n--------------------------\n";

		for (int i = 4; i >= 0; i--)
		{
			if (aPlayerInfo.lastFiveGamesStatistics[i] != noValue)
			{
				std::cout << "Game " << i + 1 << ":\n"
					<< "    Win: " << (aPlayerInfo.lastFiveGamesStatistics[i] > 0
						? "[X]\n    Gain: "
						: "[ ]\n    Loss: ")
					<< aPlayerInfo.lastFiveGamesStatistics[i] << "$\n"
					<< "\n--------------------------\n";
			}
		}
		std::cout << "Overall money: " << aPlayerInfo.money << "$\n"
			<< "\n--------------------------\n";
	}

	/// <summary>
	/// Checks if the passed argument is valid
	/// </summary>
	/// <param name="aValue">Value to check if even</param>
	/// <returns>True if even</returns>
	bool CheckIfEven(int aValue)
	{
		return (aValue % 2) == 0;
	}
}
