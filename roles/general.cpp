#include "general.hpp"
using namespace coup;

General::General(Game &g, string n): Player(g,n){}

void General::unCoup(Player &p)
{
	p.unCouped();
	coins -= 5;
}
