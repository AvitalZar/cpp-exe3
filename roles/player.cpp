//tchykzr@gmail.com
#include "player.hpp"
using namespace coup;

Player::Player(Game &g, string n): game(g){
	p_name = n;
	

	game.add_player(name());
	coins = 0;
	cout << endl << "made a new player named " << name() << endl;
}

coup::Player::Player(const Player &other): game(other.game) {
	p_name = other.p_name;
	coins = 0;
	cout << endl << "made a new player named " << name() << endl;
}

void Player::gather() {
	beforeAll("gather");
	coins ++;
	afterAll("gather");

}

void Player::tax() {
	beforeAll("tax");
	coins += 2;
	afterAll("tax");
}

void Player::bribe() {
	if(coins<4){
		throw runtime_error("player doesn't have enough coins for bribing.");
	}
	beforeAll("bribe");
	anotherTurn = 1;
	coins -= 4;
	afterAll("bribe");
}

void Player::arrest(Player& other){
	beforeAll("arrest");
	if(other.coins<1){
		throw runtime_error("You shouldn't arrest player with 0 coins.");
	}
	if(&other == last_arrested){
		throw runtime_error("You shouldn't arrest player twice in a row.");
	}
	cout << name() << " arrest " << other.name() << endl;
	coins++;
	other.arrested(*this);
	last_arrested = &other;
	afterAll("arrest");
}

void Player::sanction(Player& other) {
	if(coins<3){
		throw runtime_error("player doesn't have enough coins for sanction.");
	}
	beforeAll("sanction");
	other.sanctioned(*this);
	coins -= 3;
	afterAll("sanction");
}

void Player::coup(Player& other) {
	if(coins<7){
		throw runtime_error("player doesn't have enough coins for couping.");
	}
	beforeAll("coup");
	coins -= 7;
	game.coup(name(), other.name());
	afterAll("coup");
}

void coup::Player::undo(Player &other) {
	throw runtime_error("Regular players can't undo actions.");
}

void Player::beforeAll(string func) {
	
	//cout<<"check turns..."<<endl;
	if(!game.isturn(name())){
		throw runtime_error("Not " + name() + " turn.");
	}

	if(coins >= 10 && func != "coup"){
		throw runtime_error("Player with at list 10 coins must perform coup.");
	}
	//cout<<"check sanction..."<<endl;
	if(isSancted){
		if(func== string("gather")||func== string("tax")){
			throw runtime_error (string("Sanction is activated can't ")+(func));
		}
		isSancted = false;
	}
	//cout<<"check arrest..."<<endl;
	if(!canArrest){
		if(func == string("arrest"))
			throw runtime_error("Player is prevented from arresting.");
		canArrest = true;
	}


	
}

void Player::afterAll(string func) {

	lastAct = func;
	cout<<"perform "<<func<<" by "<<name()<<endl<<endl;

	//cout<<"move turn"<<endl;
	if(anotherTurn != 2){
		game.move_turn();
		if(anotherTurn == 1) anotherTurn ++;
	} else anotherTurn = 0;
}

void coup::Player::unTaxed() {
	if(lastAct != string("tax")){
		throw runtime_error(name()+"'s last act wasn't tax!");
	}
	coins -= 2;
}


void coup::Player::unBribed(){
	cout << "trying to undo " << name() <<"'s bribing" << endl;
	if(lastAct != string("bribe")){
		throw runtime_error(name()+"'s last act wasn't bribe.");
	}
	anotherTurn = false;
}
