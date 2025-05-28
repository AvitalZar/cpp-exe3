#pragma once
#include "player.hpp"
namespace coup{

	class Judge : public Player{
	public:
		Judge(Game &game, string name);
		void un_bribe(Player& p);
		void sanctioned(Player& p);
	};
}