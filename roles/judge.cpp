#include "judge.hpp"

using namespace coup;

Judge::Judge(Game &game, string name): Player(game,name) {}

void Judge::un_bribe(Player &p)
{
	p.unBribed();
}

void Judge::sanctioned(Player& p) {
	Player::sanctioned(p);
	p.coins--;
}
