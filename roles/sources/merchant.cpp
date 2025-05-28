
#include "merchant.hpp"

using namespace coup;

Merchant::Merchant(Game &game, string name): Player(game,name) {}

void Merchant::beforeAll(string func)
{
	Player::beforeAll(func);
	if(coins>=3)
		coins++;
}
void Merchant::arrested(Player& p){
	coins -= 2;
	p.coins --;
}
