#pragma once
#include "spy.hpp"

int coup::Spy::peekCoins(Player& p) {
	return p.getCoins();
}

void coup::Spy::prevent_arrest(Player& p) {
	beforeAll("prevent arrest");
	p.no_arrest();
	afterAll("prevent arrest");
}
