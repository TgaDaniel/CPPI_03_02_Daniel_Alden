#pragma once
namespace Player
{
	class PlayerInformation
	{
	public:
		PlayerInformation(int aMoney);

		void AddStatisticsToLastFiveGames(const int aMoney);
		void DisplayLastFiveGameStatistics() const;

		void DisplayMoney() const;
		bool HasMoney() const;
		int GetMoney() const;
		void IncrementallyChangeMoney(int aIncrement);

		void SetAllIn(bool aIsAllIn);
		bool GetAllIn() const;
		const char* GetName() const;
		bool ValidateNoNumbersInName(char aStringArray[], int aArraySize);

	private:
		int myMoney;
		int myLastFiveGamesStatistics[5] = { 0 };
		bool myAllIn = false;
		char myName[17];

		void SetPlayerName();
	};

}

