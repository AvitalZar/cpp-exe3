#pragma once
#include "game.hpp"
using namespace std;

namespace coup {
	class Player {
	protected:
		Game &game;
		
	private:
		string p_name;
		string lastAct;

		Player *last_arrested = nullptr;

		//booleans
		
		bool isSancted = false;
		bool iscouped = false;
		bool canArrest = true;
		bool isArrested = false;
	
		int anotherTurn = 0; //0 - no +turn, 1 - +turn in next turn, 2 - +turn now.
	
	public:
		unsigned int coins;
		Player(Game &g, string n);
		string name() {return p_name;}
		void gather();
		virtual void tax();
		void bribe();
		void arrest(Player& other);
		void sanction(Player& other);
		void coup(Player& other);
		int getCoins() {return coins;}

	
		virtual void sanctioned(Player& p) {isSancted = true;}
		void no_arrest() {canArrest = false;}
		virtual void arrested(Player& p) {coins--;}

		virtual void beforeAll(string func);
		void afterAll(string func);

		bool get_isSancted(){return isSancted;}

		virtual void unTaxed();
		void unBribed();
	};
}