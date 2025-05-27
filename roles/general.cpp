#include "general.hpp"
using namespace coup;

General::General(Game &g, string n): Player(g,n){}

void General::unCoup(Player &p)
{
	if(coins < 5)
		throw runtime_error("General doesn't have enough coins for uncoup.");
	p.unCouped();
	coins -= 5;
}
