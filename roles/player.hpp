//tchykzr@gmail.com
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
		Player(const Player& other);
		string name() {return p_name;}
		void gather();
		virtual void tax();
		void bribe();
		void arrest(Player& other);
		void sanction(Player& other);
		void coup(Player& other);
		int getCoins() {return coins;}

		virtual void undo(Player &other);
		virtual int peekCoins(Player &other) {throw runtime_error("Only spy can peek.");};
		virtual void prevent_arrest(Player &other) {throw runtime_error("Only spy can prevent arrest.");};
		virtual void invest() {throw runtime_error("Only barons can invest.");}

	
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