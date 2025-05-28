#pragma once

#include "player.hpp"

namespace coup {

	class General : public Player{
	public:
		General(Game &g, string n);
		void unCoup(Player& p);
	};
}