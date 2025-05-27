#include "governor.hpp"
using namespace coup;

Governor::Governor(Game &g, string n): Player(g,n) {}

void Governor::tax()
{
	Player::tax();
	coins++;
}

	void coup::Governor::undo_tax(Player &p) {
			p.unTaxed();
		
	}
