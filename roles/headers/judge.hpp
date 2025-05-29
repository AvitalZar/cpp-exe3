//tchykzr@gmail.com
#pragma once
#include "player.hpp"
namespace coup{

	class Judge : public Player{
	public:
		Judge(Game &game, string name);
		void undo(Player& p) override;
		void sanctioned(Player& p);
		~Judge() {}
	};
}