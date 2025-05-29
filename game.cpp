//tchykzr@gmail.com
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
		if(find(toCoup,play_ord[i]) == -1)
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

void Game::coup(string active, string passive){
	cout << active << " is trying to coup " << passive << endl;
	if(find(play_ord, passive) == -1)
		throw runtime_error("Can't coup: This player is not in the game.");
	int loc = find(play_ord,active);
	
	if(toCoup[loc] == ""){
		toCoup[loc] = passive;
	} else if(toCoup[loc] == passive){
		int pass_loc = find(play_ord, passive);
		play_ord.erase(play_ord.begin()+pass_loc);
		toCoup.erase(toCoup.begin() + pass_loc);
		if(turnum >= play_ord.size()){
			turnum = 0;
		}
		toCoup[loc] = "";
	}
	else
		throw runtime_error("Something wrong. This player was about to coup another player.");
		
}

bool coup::Game::un_coup(string p) {
	bool ans = false;
	for(unsigned int i = 0; i < toCoup.size(); i++){
		if(toCoup[i] == p){
			toCoup[i] = "";
			ans = true;
		}
	}
	return ans;
}

void coup::Game::add_player(string p) {
	if(find(play_ord,p) != -1){
		throw runtime_error("There's already player with that name in the game. Choose another name.");
	}
	play_ord.push_back(p);
	toCoup.push_back("");
	if(play_ord.size() == 2)
		is_game_started = true;
}

void coup::Game::move_turn()
{
	cout << "move turn" << endl;
	turnum = (turnum + 1)%play_ord.size();
	
	if(toCoup[turnum] != ""){
		cout << "End a round, coup." << endl;
		coup(play_ord[turnum], toCoup[turnum]);
	}
	if(find(toCoup, play_ord[turnum]) != -1){
		cout << "This player couped, move turn." << endl;
		move_turn();
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
