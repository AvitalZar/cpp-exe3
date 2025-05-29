//tchykzr@gmail.com
#include "baron.hpp"
namespace coup{

	Baron::Baron(Game &g, string n): Player(g,n) {}

	void Baron::invest()
	{
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