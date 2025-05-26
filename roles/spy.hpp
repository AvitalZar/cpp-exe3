#pragma once
#include "player.hpp"
namespace coup{

	class Spy : public Player{
	public:
		int peekCoins(Player& p);
		void prevent_arrest(Player& p);
	};
}