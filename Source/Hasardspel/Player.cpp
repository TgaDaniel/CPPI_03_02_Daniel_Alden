#include <iostream>

#include "Player.h"

#include "IOHandler.h"

namespace Player
{

	PlayerInformation::PlayerInformation(int aMoney)
		: myMoney(aMoney)
	{
		SetPlayerName();
	}


	/// <summary>
	/// Handles adding of money statistics to the <c>lastFiveGamesStatistics array</c> in the <c>PlayerInformation struct</c>. Where 0 equals no play
	/// </summary>
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

		std::cout << "\n\n" <<  myName << "'s Game statistics----"
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

	const char* PlayerInformation::GetName() const
	{
		return myName;
	}

	/// <summary>
	/// Validates no numbers are in <c>myName</c>
	/// </summary>
	/// <returns><c>True</c> if there are no numbers and <c>False</c> if there is </returns>
	bool PlayerInformation::ValidateNoNumbersInName(char aStringArray[], int aArraySize)
	{
		constexpr int numbersInBaseTen{ 10 };

		constexpr char firstValueInBaseTen = '0';

		for (int arrayIndex = 0; arrayIndex < aArraySize; arrayIndex++)
		{
			for (int adder = 0; adder <= numbersInBaseTen; adder++)
			{
				if (aStringArray[arrayIndex] == (firstValueInBaseTen + adder)) return false;
			}
		}
		return true;
	}

	void PlayerInformation::SetPlayerName()
	{
		constexpr int nameArraySize{ 17 };
		constexpr int validationSize{ 18 };

		while (true)
		{
			char validationArray[validationSize];

			std::cout << "\nEnter a name between 2 and 16 characters long, with no numeric characters in it\n"
				"Input: ";


			std::cin.get(validationArray, validationSize);

			if (ValidateNoNumbersInName(validationArray, nameArraySize))
			{
				for (int i = 0; i < nameArraySize; i++)
				{
					myName[i] = validationArray[i];
					if (validationArray[i] == '\0' && i > 1)
					{
						return;
					};
				}
			}

			system("cls");
			std::cout << "\nInvalid input...\n";
			IOHandler::PauseThenClearScreen();
			IOHandler::FlushCinBuffer();
		}
	}

	void PlayerInformation::DisplayMoney() const
	{
		std::cout << "\n-------------------------\n"
			<< myName << " Money: " << myMoney << "$"
			<< "\n-------------------------\n\n";
	}

}
