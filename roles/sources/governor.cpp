//tchykzr@gmail.com
#include "governor.hpp"
using namespace coup;

Governor::Governor(Game &g, string n): Player(g,n) {}

void Governor::tax()
{
	Player::tax();
	coins++;
}

	void coup::Governor::undo(Player &p) {
			p.unTaxed();
		
	}
