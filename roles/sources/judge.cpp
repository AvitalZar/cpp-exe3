//tchykzr@gmail.com
#include "judge.hpp"

using namespace coup;

Judge::Judge(Game &game, string name): Player(game,name) {}

void Judge::undo(Player &p)
{
	p.unBribed();
}

void Judge::sanctioned(Player& p) {
	if(p.coins < 4)
		throw runtime_error("Player doesn't have enough coins for sanction on a judge.");
	Player::sanctioned(p);
	p.coins--;
}
