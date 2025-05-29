//tchykzr@gmail.com
#pragma once

#include "player.hpp"

namespace coup {

	class General : public Player{
	public:
		General(Game &g, string n);
		void undo(Player& p) override;

		~General() {}
	};
}