#pragma once
#include "player.hpp"
namespace coup{

	class Spy : public Player{
	public:
		Spy(Game &g, string n);
		int peekCoins(Player& p);
		void prevent_arrest(Player& p);
	};
}