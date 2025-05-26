#pragma once
#include "player.hpp"
namespace coup{

	class Merchant : public Player{
	public:
		void beforeAll(string func) override;
		void arrested(Player& p) override;
	};

	void Merchant::beforeAll(string func) {
		Player::beforeAll(func);
		if(coins>=3)
			coins++;
	}
	void Merchant::arrested(Player& p){
		coins -= 2;
		p.coins --;
	}
}