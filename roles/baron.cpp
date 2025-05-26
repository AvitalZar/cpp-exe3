#pragma once
#include "player.hpp"
namespace coup{

	class Baron : public Player{
	public:
		void invest();
		void sanctioned(Player& p) override;
	};

	void Baron::invest(){
		beforeAll("invest");
		if(coins<3){
			throw runtime_error("Baron can't invest less than 3 coins.");
		}
		coins += 3;
		afterAll("invest");
	}

	void Baron::sanctioned(Player& p){
		Player::sanctioned(p);
		coins ++;
	}
}