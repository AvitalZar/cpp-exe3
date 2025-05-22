#include "player.hpp"
using namespace coup;

Player::Player(Game *g, string n){
	game = g;
	name = n;
	p_num = game->players().size();

	game->players().push_back(n);
	game->toCoup.push_back(false);
	coins = 0;
}

void Player::gather() {
	beforeAll("gather");
	coins ++;
}

void Player::tax() {
	beforeAll("tax");
	coins += 2;
}

void Player::bribe() {
	if(coins<4){
		throw runtime_error("player doesn't have enough coins for bribing.");
	}
	beforeAll("bribe");
	anotherTurn = true;
	coins -= 4;
}

void Player::arrest(Player& other){
	if(other.coins<1){
		throw runtime_error("You sholdn't arrest player with 0 coins.");
	}
	beforeAll("arrest");
	coins++;
	other.coins--;
}

void Player::sanction(Player& other) {
	if(coins<3){
		throw runtime_error("player doesn't have enough coins for sanction.");
	}
	beforeAll("sanction");
	coins -= 3;
	other.sanctioned();
}

void Player::coup(Player& other) {
	if(coins<7){
		throw runtime_error("player doesn't have enough coins for couping.");
	}
	beforeAll("coup");
	coins -= 7;
	other.couped();
}

void Player::beforeAll(string func) {
	cout<<"check coup..."<<endl;
	if(game->toCoup[game->turnum]){
		if(p_num == game->turnum)
			throw runtime_error("Couped players can't play.");
		cout<<"couping."<<endl;
		game->coup(game->turnum);
		cout<<game->players()[game->turnum]<<" was couped.";
		
	}
	cout<<"check turns..."<<endl;
	if(game->turnum != p_num){
		throw runtime_error(string("Not ").append(name).append(" turn."));
	}

	if(coins >= 10 && !func.compare("coup")){
		throw runtime_error("Player with at list 10 coins must perform coup.");
	}
	cout<<"check sanction..."<<endl;
	if(isSancted){
		if(func== string("gather")||func== string("tax")){
			throw runtime_error (string("Sanction is activated can't ").append(func));
		}
		isSancted = false;
	}
	cout<<"check arrest..."<<endl;
	if(!canArrest){
		if(func == string("arrest"))
			throw runtime_error("Player is prevented from arresting.");
		canArrest = true;
	}

	cout<<"move turn"<<endl;
	if(!anotherTurn){
		game->move_turn();
		anotherTurn = false;
	}
	cout<<"perform "<<func<<" by "<<name<<endl<<endl;
	
}

