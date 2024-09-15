#include "CasinoHandler.h"
#include "GameUtilities.h"
#include "RandomHandler.h"

int main()
{
	RandomHandler randomHandler{};
	Player::PlayerInformation player{ 1000 };
	GameUtilities::GeneralCasinoRules rules = { 500,100 };

	Casino::CasinoHandler casino{player,rules,randomHandler};

	casino.Start();

	return 0;
}
