#pragma once
#include "spy.hpp"

int coup::Spy::peekCoins(Player p) {
	return p.getCoins();
}

void coup::Spy::prevent_arrest(Player p) {
	p.no_arrest();
}
