#include "game.hpp"
using namespace coup;

string Game::turn(){
	if(play_ord.size() == 0)
		throw runtime_error("There's no game and no turn.");
	cout<<"It's "<<play_ord.at(turnum)<<" turn."<<endl;
	return play_ord.at(turnum);
}

vector<string> coup::Game::players() {
	vector<string> ans;
	for(unsigned int i = 0; i < play_ord.size(); i++){
		if(!toCoup[i])
			ans.push_back(play_ord[i]);
	}
	return ans;
}

string Game::winner(){
	if(!is_game_started)
		throw runtime_error("This game didn't start yet.");
	if(play_ord.size() != 1){
		throw runtime_error ("This game didn't end yet.");
	}
	return play_ord.front();
}

void Game::coup(string p){
	int loc = find(play_ord,p);
	if(toCoup[loc]){
		toCoup.erase(toCoup.begin()+loc);
		play_ord.erase(play_ord.begin()+loc);
		if(turnum >= play_ord.size()){
			turnum = 0;
		}
	}
	else
		toCoup[loc] = true;
}

void coup::Game::add_player(string p) {
	if(find(play_ord,p) != -1){
		throw runtime_error("There's already player with that name in the game. Choose another name.");
	}
	play_ord.push_back(p);
	toCoup.push_back(false);
	if(play_ord.size() == 2)
		is_game_started = true;
}

void coup::Game::move_turn()
{
	turnum++;
	if(turnum == play_ord.size())
		turnum = 0;
	
	if(toCoup[turnum]){
		coup(play_ord[turnum]);
	}
}

Game::~Game()
{
}

int coup::find(const vector<string> &v, const string &s) {
	for (unsigned int i = 0; i < v.size(); ++i) {
		if (v[i] == s) {
			return i;
		}
	}
	return -1;

}
