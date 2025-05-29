//tchykzr@gmail.com
#include "general.hpp"
using namespace coup;

General::General(Game &g, string n): Player(g,n){}

void General::undo(Player &p)
{
	if(coins < 5)
		throw runtime_error("General doesn't have enough coins for uncoup.");
	if(!game.un_coup(p.name()))
		throw runtime_error("No one have done coup against this player, can't uncoup.");
	coins -= 5;
}
