#pragma once
#include "player.hpp"
namespace coup{

	class General : public Player{
	private:
	public:
		void unCoup(Player& p);
	};

	void General::unCoup(Player& p){
		p.unCoup();
		coins -= 5;
	}

	
}