#include <iostream>

#include "Player.h"

namespace Player
{

	PlayerInformation::PlayerInformation(int aMoney)
		: myMoney(aMoney)
	{
	}


	/// <summary>
	/// Handles adding of money statistics to the <c>lastFiveGamesStatistics array</c> in the <c>PlayerInformation struct</c>. Where 0 equals no play
	/// </summary>
	/// <param name="aPlayerInfo">Information about the player passed in with the <c>PlayerInformation</c> struct as a reference </param>
	/// <param name="aMoney">The amount of money won or lost. If lost enter negative amount instead of positive</param>
	void PlayerInformation::AddStatisticsToLastFiveGames(const int aMoney)
	{

		constexpr int arraysLastIndex{ 4 };
		constexpr int  integerToReplace{ 0 };

		//If aGameStatistics last placement isn't 0 then you can change the values
		if (myLastFiveGamesStatistics[arraysLastIndex] != integerToReplace)
		{
			for (int i = 0; i <= arraysLastIndex; ++i)
			{
				if (i != 0)
				{
					int previousIndex{ i - 1 };
					myLastFiveGamesStatistics[previousIndex] = myLastFiveGamesStatistics[i];
				}

				if (i == 4)
				{
					myLastFiveGamesStatistics[i] = aMoney;
					return;
				}
			}
		}

		for (int& gameStatistic : myLastFiveGamesStatistics)
		{
			if (gameStatistic == integerToReplace)
			{
				gameStatistic = aMoney;
				return;
			}
		}

	}

	void PlayerInformation::DisplayLastFiveGameStatistics() const
	{
		system("cls");


		constexpr int noValue{ 0 };
		if (myLastFiveGamesStatistics[0] == noValue)
		{
			std::cout << "\nNo games played yet.\n";
			return;
		}

		std::cout << "\n\nGeneral Game statistics----"
			<< "\n--------------------------\n";

		for (int i = 4; i >= 0; i--)
		{
			if (myLastFiveGamesStatistics[i] != noValue)
			{
				std::cout << "Game " << i + 1 << ":\n"
					<< "    Win: " << (myLastFiveGamesStatistics[i] > 0
						? "[X]\n    Gain: "
						: "[ ]\n    Loss: ")
					<< myLastFiveGamesStatistics[i] << "$\n"
					<< "\n--------------------------\n";
			}
		}
		std::cout << "Overall money: " << myMoney << "$\n"
			<< "\n--------------------------\n";
	}


	/// <summary>
	///  Checks if player have money in their account by passing the PlayerInformation object reference
	/// </summary>
	/// <returns>True if there is money. False if there is no money</returns>
	bool PlayerInformation::HasMoney() const
	{
		constexpr int noMoney{ 0 };
		return myMoney > noMoney;
	}

	int PlayerInformation::GetMoney() const
	{
		return myMoney;
	}

	/// <summary>
	/// Will increment money.
	/// It will add if a positive number is passed and subtract if a negative number is passed.
	/// </summary>
	/// <param name="aIncrement">the amount to increment money.</param>
	void PlayerInformation::IncrementallyChangeMoney(int aIncrement)
	{
		myMoney += aIncrement;
	}

	void PlayerInformation::SetAllIn(bool aIsAllIn)
	{
		myAllIn = aIsAllIn;
	}

	bool PlayerInformation::GetAllIn() const
	{
		return myAllIn;
	}

	void PlayerInformation::DisplayMoney() const
	{
		std::cout << "\n-------------------------\n"
			<< "Money: " << myMoney << "$"
			<< "\n-------------------------\n\n";
	}

}
