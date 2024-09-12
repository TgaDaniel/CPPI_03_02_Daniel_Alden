#pragma once
namespace GameUtilities
{
	struct PlayerInformation
	{
		int money = 500;
		int lastFiveGamesStatistics[5] = {0};
		bool allIn = false;

	};

	struct GeneralCasinoRules
	{
		int maxWinAmountPerTable = 300;
		int reactionAmount = 100;
	};


	struct GameConditions
	{
		int minRandomValue;
		int maxRandomValue;
		int winMultiplier;
	};

	void DisplayLastFiveGameStatistics(const PlayerInformation& aPlayerInfo);

	void AddStatisticsToLastFiveGamesArray(PlayerInformation& aPlayerInfo, int aMoney);

	void DisplayMoney(const int aPlayerMoney);

	int HandleBetting(PlayerInformation& aPlayerInfo);

	bool CheckPlayerHasMoney(const PlayerInformation& aPLayerInfo);

	bool CheckIfEven(int aValue);

}