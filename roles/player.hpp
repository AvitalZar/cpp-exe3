#include "game.hpp"
using namespace std;

namespace coup {
	class Player {
	private:
		Game *game;
		string name;
		int coins;
		string lastAct;
		int p_num;

		//booleans
		bool anotherTurn = false;
		bool isSancted = false;
		bool iscouped = false;
		bool canArrest = true;
	
	public:
		Player(Game *g, string n);
		void gather();
		void tax();
		void bribe();
		void arrest(Player& other);
		void sanction(Player& other);
		void coup(Player& other);

		void sanctioned() {isSancted = true;}
		void couped() {game->coup(p_num);}
		void no_arrest() {canArrest = false;}

		void beforeAll(string func);

		int getCoins(){return coins;}
		bool get_isSancted(){return isSancted;}


	};
}