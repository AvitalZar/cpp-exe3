#pragma once
#include "player.hpp"
namespace coup{

	class Merchant : public Player{
	public:
		Merchant(Game &game, string name);
		void beforeAll(string func) override;
		void arrested(Player& p) override;
	};
}