#include "spy.hpp"

coup::Spy::Spy(Game &g, string n): Player(g,n) {}

int coup::Spy::peekCoins(Player &p)
{
	return p.getCoins();
}

void coup::Spy::prevent_arrest(Player& p) {
	p.no_arrest();
}
