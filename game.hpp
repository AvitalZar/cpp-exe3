//tchykzr@gmail.com
#ifndef GAME_HPP
#define GAME_HPP


#include <iostream>
#include <vector>
#include <exception>
#include <algorithm>
using namespace std;

namespace coup{
	class Game{

		private:
			vector<string> play_ord;
			bool is_game_started = false;
		
		public:
			unsigned int turnum;
			vector<string> toCoup;


			Game() {turnum = 0;}
			string turn();
			vector<string> players();
			string winner();
			void coup(string active, string passive);
			bool un_coup(string p);
			void add_player(string p);
			void move_turn();
			bool isturn(string p) {return play_ord[turnum] == p;}
			~Game();
	};

	
	int find(const vector<string>& v, const string& s);
}

#endif //GAME_HPP