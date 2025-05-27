#pragma once

#include "player.hpp"

namespace coup{

	class Governor : public Player{
	public:
		Governor(Game &g, string n);
		
		void tax() override;

		void undo_tax(Player& p);

		void unTaxed(){
			Player::unTaxed();
			coins--;
		}
	};
}