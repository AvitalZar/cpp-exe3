#pragma once
#include "player.hpp"
namespace coup{

	class Judge : public Player{
	public:
		void un_bribe(Player& p);
		void sanctioned(Player& p);
	};
	
	void Judge::un_bribe(Player& p) {
		p.unBribe();
	}

	void Judge::sanctioned(Player& p) {
		Player::sanctioned(p);
		p.coins--;
	}
}