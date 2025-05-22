#ifndef GAME_HPP
#define GMAE_HPP


#include <iostream>
#include <vector>
#include <exception>
#include <algorithm>
using namespace std;

namespace coup{
	class Game{

		private:
			vector<string> play_ord;
		
		public:
			int turnum;
			vector<bool> toCoup;


			Game(){turnum = 0;}
			string turn();
			vector<string>& players(){return play_ord;}
			string winner();
			void coup(int p);

			void move_turn();
			~Game();
	};
}

#endif //GAME_HPP