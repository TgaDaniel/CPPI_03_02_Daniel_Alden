#include <iostream>

#include "GameUtilities.h"
#include "IOHandler.h"

namespace GameUtilities
{
	int HandleBetting(Player::PlayerInformation& aPlayerInfo, bool aUseBetParams, TableBetParameters aBetParams)
	{
		while (true)
		{
			//Sets maxBet to above player money
			if(!aUseBetParams)
			{
				aBetParams.maxBet = aPlayerInfo.GetMoney();
			}

			aPlayerInfo.DisplayMoney();
			std::cout << "\nHow much do you want to bet?: ";

			int betAmount{ 0 };
			std::cin >> betAmount;
			if (IOHandler::ValidateInput() && betAmount >= aBetParams.minBet && betAmount <= aBetParams.maxBet && betAmount <= aPlayerInfo.GetMoney())
			{
				if (betAmount == aPlayerInfo.GetMoney())
				{
					aPlayerInfo.SetAllIn(true);
					system("cls");
					std::cout << "\n\n*The casino quiets down and everyone looks at you. You feel the tension and weight of this decision*\n*Whatever the outcome, this decision will be life changing, either for good or bad*\n"
						<< "\n\n" << aPlayerInfo.GetName() << " have just gone all in!!!\n\n";
					IOHandler::PauseThenClearScreen();
					std::cout << "\n\nThe owner of the casino looks down on you from on top of his comically villainous throne and a large evil grin spread along his face\n'The house always wins' He thinks\n";
					IOHandler::PauseThenClearScreen();
				}
				aPlayerInfo.IncrementallyChangeMoney(-betAmount);
				std::cout << "\nYou now have " << aPlayerInfo.GetMoney() << "$\nGood Luck\n";
				IOHandler::FlushCinBuffer();
				return betAmount;
			}
			system("cls");
			std::cout << "\nInvalid amount.\n";
			IOHandler::PauseThenClearScreen();
		}

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
