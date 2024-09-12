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

	private:
		int myMoney = 500;
		int myLastFiveGamesStatistics[5] = { 0 };
		bool myAllIn = false;
	};

}

