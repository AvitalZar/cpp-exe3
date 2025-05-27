
#include "roles/player.hpp"
#include "roles/governor.hpp"
#include "roles/spy.hpp"
#include "roles/baron.hpp"
#include "roles/general.hpp"
#include "roles/judge.hpp"
#include "roles/merchant.hpp"
#include "game.hpp"

#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;
using namespace coup;

int main() {
	cout << "starting demo!" << endl;
    Game game_1;
	cout << "Game constructed." << endl;

    Governor governor(game_1, "Moshe");
	cout << "number of players: (should be 1)  " << game_1.players().size() << endl;
    Spy spy(game_1, "Yossi");
    Baron baron(game_1, "Meirav");
    General general(game_1, "Reut");
    Judge judge(game_1, "Gilad");

    vector<string> players = game_1.players();
    
    // Expected output:
    // Moshe
    // Yossi
    // Meirav
    // Reut
    // Gilad
    for(string name : players){
        cout << name << endl;
    }

	cout << "printing turn" << endl;
    // Expected output: Moshe
    cout << game_1.turn() << endl;

    governor.gather();
    spy.gather();
    baron.gather();
    general.gather();
    judge.gather();

    // Expected exception - Not spy's turn
    try{
        spy.gather();
    } catch (const std::exception &e){
        std::cerr << e.what() << '\n';
    }

    governor.gather();
    spy.tax();

    // Expected exception - Judge cannot undo tax
    try{
        judge.un_bribe(governor);
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    cout << governor.getCoins() << endl; // Expected: 2
    cout << spy.getCoins() << endl; // Expected: 3

    governor.undo_tax(spy); // Governor undo tax
    cout << spy.getCoins() << endl; // Expected: 1

    baron.tax();
    general.gather();
    judge.gather(); 

    governor.tax();
    spy.gather();
    baron.invest(); // Baron traded its 3 coins and got 6 
    general.gather();
    judge.gather();
    
    cout << baron.getCoins() << endl; // Expected: 6

    governor.tax();
    spy.gather();
    baron.gather();
    general.gather();
    judge.gather();

    governor.tax();
    spy.gather();
    cout << baron.getCoins() << endl; // Expected: 7
    baron.coup(governor); // Coup against governor
    general.gather();
    judge.gather();
    
    players = game_1.players();
    // Since no one blocked the Baron, the expected output is:
    // Yossi
    // Meirav
    // Reut
    // Gilad
    for (string name : players) {
        cout << name << endl;
    }

}
