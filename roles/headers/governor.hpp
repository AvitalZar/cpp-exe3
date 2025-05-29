//tchykzr@gmail.com
#pragma once

#include "player.hpp"

namespace coup{

	class Governor : public Player{
	public:
		Governor(Game &g, string n);
		
		void tax() override;

		void undo(Player& p) override;

		void unTaxed(){
			Player::unTaxed();
			coins--;
		}

		~Governor() {}
	};
}