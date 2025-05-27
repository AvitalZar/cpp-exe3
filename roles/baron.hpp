#pragma once
#include "player.hpp"

namespace coup {

	class Baron : public Player{
		public:
			Baron(Game &g, string n);
			void invest();
			void sanctioned(Player& p) override;
	};
}