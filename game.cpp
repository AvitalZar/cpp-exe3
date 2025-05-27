#include "game.hpp"
using namespace coup;

string Game::turn(){
	if(play_ord.size() == 0)
		throw runtime_error("There's no game and no turn.");
	cout<<"It's "<<play_ord.at(turnum)<<" turn."<<endl;
	return play_ord.at(turnum);
}

string Game::winner(){
	if(play_ord.size() != 1){
		throw runtime_error ("This game didn't end yet.");
	}
	return play_ord.front();
}

void Game::coup(int p){
	if(toCoup[p]){
		toCoup.erase(toCoup.begin()+p);
		play_ord.erase(play_ord.begin()+p);
		if(turnum >= play_ord.size()){
			turnum = 0;
		}
	}
	else
		toCoup[p] = true;
}

void coup::Game::move_turn(){
	turnum++;
	if(turnum == play_ord.size())
		turnum = 0;
	
	if(toCoup[turnum]){
		coup(turnum);
	}
}

Game::~Game()
{
}