#pragma once
#include "game.hpp"
using namespace std;

namespace coup {
	class Player {
	private:
		Game &game;
		string name;
		string lastAct;

		Player *last_arrested;

		//booleans
		bool anotherTurn = false;
		bool isSancted = false;
		bool iscouped = false;
		bool canArrest = true;
		bool isArrested = false;
	

	
	public:
		unsigned int coins;
		Player(Game &g, string n);
		void gather();
		virtual void tax();
		void bribe();
		void arrest(Player& other);
		void sanction(Player& other);
		void coup(Player& other);
		int getCoins() {return coins;}

	
		virtual void sanctioned(Player& p) {isSancted = true;}
		virtual void couped() {game.coup(name);}
		void no_arrest() {canArrest = false;}
		virtual void arrested(Player& p) {coins--;}

		virtual void beforeAll(string func);
		void afterAll(string func);

		bool get_isSancted(){return isSancted;}

		virtual void unTaxed();
		void unCouped();
		void unBribed();
	};
}