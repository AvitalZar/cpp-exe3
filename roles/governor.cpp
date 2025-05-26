#pragma once
#include "player.hpp"

namespace coup{

	class Governor : public Player{
	public:
		void tax() override {
			Player::tax();
			coins ++;
		}

		void undo_tax(Player& p){
			p.unTax();
		}

		void unTax(){
			Player::unTax();
			coins--;
		}
	};
}