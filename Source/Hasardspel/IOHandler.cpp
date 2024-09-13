#include <iostream>

#include "IOHandler.h"
#include "GameUtilities.h"

namespace IOHandler
{
	void FlushCinBuffer()
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	void PauseThenClearScreen()
	{
		system("pause");
		system("cls");
	}

	/// <summary>
	/// If cin input is invalid the buffer will be cleared and flushed.
	/// </summary>
	/// <returns>True if the input was valid otherwise False</returns>
	bool ValidateInput()
	{
		if (std::cin.fail())
		{
			FlushCinBuffer();
			return false;
		}
		return true;
	}

	void HandleAllInWin(Player::PlayerInformation& aPlayer)
	{
		if (aPlayer.GetAllIn())
		{
			std::cout << "\n\nThe casino owner scoffs and look away.\nPeople applaud while you are being paid out and you can hear people whisper your name in admiration\n"
			<< aPlayer.GetName() << " they whisper\n";
			aPlayer.SetAllIn(false);
		}
	}

	/// <summary>
	/// Let the user input <c>char</c> value equal to <c>aTrueChar</c>s or <c>aFalseChar</c>s parameter value.
	/// All other values are invalid and will prompt the user to re-enter a new value.
	/// </summary>
	/// <param name="aTrueChar">Char that will return true when input</param>
	/// <param name="aFalseChar">Char that will return false when input</param>
	/// <returns>True if the value in <c>aTrueChar</c> is input. False if the value in <c>aFalseChar</c> is input</returns>
	bool TwoCharacterOptionInput(char aTrueChar, char aFalseChar)
	{
		//converts aTrueChar and aFalseChar to lower case characters (chars) in case it is upper case.
		aTrueChar = static_cast<char>(tolower(aTrueChar));
		aFalseChar = static_cast<char>(tolower(aFalseChar));

		while (true)
		{
			char playerInput;
			std::cin >> playerInput;

			if (std::cin.peek() == '\n')
			{
				if (tolower(playerInput) == aFalseChar)
				{
					std::cout << "\n";
					return false;
				}
				else if (tolower(playerInput) == aTrueChar)
				{
					std::cout << "\n";
					return true;
				}
			}

			FlushCinBuffer();
			std::cout << "Invalid input entered, try again...\n"
				<< "(" << aTrueChar << "/" << aFalseChar << "): ";
		}
	}
	void ReactionText(const GameUtilities::GeneralCasinoRules& aGeneralRules, int aTableValueChange, const Player::PlayerInformation& aPlayer)
	{
		if (aTableValueChange <= -aGeneralRules.reactionAmount)
		{
			std::cout << "\n\nBetter luck this time " << aPlayer.GetName() << ", i'm sure you'll win.\n\n";
		}
		else if (aTableValueChange >= aGeneralRules.reactionAmount)
		{
			std::cout << "\n\nThe big winner " << aPlayer.GetName() << " is back huh? Share some of that luck will ya?\n\n";
		}
		else
		{
			std::cout << "\n\nThis will be fun " << aPlayer.GetName() <<"!\n\n";
		}
	}
}
