#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "game.hpp"

#include "roles/player.hpp"
#include "roles/governor.hpp"
#include "roles/spy.hpp"
#include "roles/baron.hpp"
#include "roles/general.hpp"
#include "roles/judge.hpp"
#include "roles/merchant.hpp"

#include <string>
#include <vector>
#include <iostream>

using namespace coup;
using namespace std;


TEST_CASE("Game Basic Functionality") {
    Game game;

    SUBCASE("Initial state") {
        CHECK_THROWS_AS(game.turn(), std::runtime_error);
        CHECK(game.players().empty());
        CHECK_THROWS_AS(game.winner(), std::runtime_error);
        CHECK(game.turnum == 0);
    }

	Player p1(game, "Alice");
    SUBCASE("One player") {
        CHECK(game.players().size() == 1);
        CHECK(game.players().at(0) == "Alice");
        CHECK(game.turn() == "Alice");
        CHECK_THROWS_AS(game.winner(), std::runtime_error);
    }

	Player p2(game, "Bob");
    SUBCASE("Two players") {
        CHECK(game.players().size() == 2);
        CHECK(game.players().at(0) == "Alice");
        CHECK(game.players().at(1) == "Bob");
        CHECK(game.turn() == "Alice");
        game.move_turn();
        CHECK(game.turn() == "Bob");
        game.move_turn();
        CHECK(game.turn() == "Alice");
    }

	SUBCASE("More players") {
		Player p3(game, "Bob2");
		Player p4(game, "Alice2");
        Player p5(game, "Alice3");
        Player p6(game, "Bob3");
        Player p7(game, "Bob4");
        CHECK(game.players().size() == 7);
        CHECK(game.turn() == "Alice");

		Game g2;
		Player p9(g2,"Oddyseus");
		CHECK(game.players().size() == 7);
		CHECK_NOTHROW(Player px(g2, "Bob"));
	}


}


TEST_CASE("Player Basic Actions") {
    Game game;
    Player p1(game, "P1");
    Player p2(game, "P2");

    SUBCASE("Initial coins") {
        CHECK(p1.getCoins() == 0);
        CHECK(p2.getCoins() == 0);
    }

    SUBCASE("Gather action") {
        CHECK(game.turn() == "P1");
        p1.gather();
        CHECK(p1.getCoins() == 1);
        CHECK(game.turn() == "P2");

        CHECK_THROWS_AS(p1.gather(), std::runtime_error);

        p2.gather();
        CHECK(p2.getCoins() == 1);
        CHECK(game.turn() == "P1");
    }

    SUBCASE("Tax action") {
        CHECK(game.turn() == "P1");
        p1.tax();
        CHECK(p1.getCoins() == 2);
    }
    
    SUBCASE("Bribe action") {
        p1.coins = 4;
        CHECK(game.turn() == "P1");
        p1.bribe();
        CHECK(p1.getCoins() == 0);
        CHECK(game.turn() == "P2");
		p2.gather();
		p1.gather();
		CHECK(game.turn() == "P1");

        p1.coins = 3;
        CHECK_THROWS_AS(p1.bribe(), runtime_error);
        CHECK(p1.getCoins() == 3);
        CHECK(game.turn() == "P1");
    }

    SUBCASE("Coup action") {
		Player p3(game, "P3");
        p1.coins = 7;
        CHECK(game.turn() == "P1");
        p1.coup(p3);
        CHECK(p1.getCoins() == 0);

		CHECK(game.players().size() == 2);
		for (string name : game.toCoup) {
        	cout << "- " << name << endl;
    	}
		CHECK(game.turn() == "P2");
		cout << "1" << endl;
		p2.gather();
		cout << "2" << endl;
		CHECK(game.turn() == "P1");
		p2.coins += 7;
		p1.gather();
		p2.coup(p1);
		CHECK(game.turn() == "P2");
		CHECK(game.winner() == "P2");
		


        Game game2;
        Player pA(game2, "PA");
        Player pB(game2, "PB");
        pA.coins = 6;
        CHECK_THROWS_AS(pA.coup(pB), std::runtime_error);
        CHECK(pA.getCoins() == 6);
    }
    
    
    SUBCASE("10+ coins rule - Must Coup") {
        p1.coins = 10;
        CHECK(game.turn() == "P1");

        CHECK_THROWS_AS(p1.gather(), std::runtime_error);
        CHECK_THROWS_AS(p1.tax(), std::runtime_error);
        CHECK_THROWS_AS(p1.bribe(), std::runtime_error);
        
        CHECK_NOTHROW(p1.coup(p2));
        CHECK(p1.getCoins() == 3); // 10 - 7 = 3
        CHECK(game.turn() == "P1"); 
    }
}



TEST_CASE("arrest & sanction") {
    Game game;
    Player p1(game, "P1");
    Player p2(game, "P2");
    Player p3(game, "P3");

    SUBCASE("Arrest action") {

		try{
			p1.arrest(p2);
		} catch (const std::exception &e){
			std::cerr << e.what() << '\n';
		}
		CHECK_THROWS(p1.arrest(p2));
		CHECK(p1.getCoins() == 0);
        CHECK(game.turn() == "P1");
        
        p1.gather(); // P1 turn, P1 coins = 1. Turn -> P2
        p2.gather(); // P2 turn, P2 coins = 1. Turn -> P3

        p3.arrest(p1);
        CHECK(p3.getCoins() == 1);
        CHECK(p1.getCoins() == 0);

        p1.gather();
		p2.gather();
		CHECK(game.turn() == "P3");
		try{
			p3.arrest(p1);
		} catch (const std::exception &e){
			std::cerr << e.what() << '\n';
		}
		CHECK_THROWS(p3.arrest(p1));
		p3.arrest(p2);
		p1.gather();
		p2.gather();
		CHECK_NOTHROW(p3.arrest(p1));
    }
    
    SUBCASE("Sanction action") {
        p1.coins = 4;
        p1.sanction(p2);
        CHECK(p1.getCoins() == 1);
        CHECK(p2.get_isSancted());
        CHECK(game.turn() == "P2");

        CHECK_THROWS_AS(p2.gather(), std::runtime_error);
        CHECK_THROWS_AS(p2.tax(), std::runtime_error);
        CHECK(p2.get_isSancted()); 
        
        p2.arrest(p1); //revenge!!
        CHECK(!p2.get_isSancted());
        p3.gather();
		p1.gather();
		CHECK_NOTHROW(p2.gather());
    }

}


TEST_CASE("Spy Role") {
    Game game;
    Spy spy(game, "Spy");
    Player p2(game, "P2");
    Player p3(game, "P3");

    SUBCASE("Spy tax (is normal Player tax)") {
        spy.tax();
        CHECK(spy.getCoins() == 2);
        CHECK(game.turn() == "P2");
    }

    SUBCASE("peek coins") {
        p2.coins = 5;
        CHECK(spy.peekCoins(p2) == 5);
        CHECK(game.turn() == "Spy");
    }

    SUBCASE("prevent arrest") {
        spy.prevent_arrest(p2);
        CHECK(spy.getCoins() == 0);
        CHECK(game.turn() == "Spy");
		spy.tax();

        p3.coins = 1;
		try{
			p2.arrest(p3);
		} catch (const std::exception &e){
			std::cerr << e.what() << '\n';
		}
        CHECK_THROWS_AS(p2.arrest(p3), std::runtime_error);
        
        p2.gather(); // P2 does something else
        CHECK(p2.getCoins() == 1);
        CHECK(game.turn() == "P3");

        p3.gather(); // P3 turn. P3 coins = 2. Turn Spy.
        spy.gather(); // Spy turn. Spy coins = 1. Turn P2.

        CHECK_NOTHROW(p2.arrest(p3));
        CHECK(p2.getCoins() == 1 + 1);
        CHECK(p3.getCoins() == 2 - 1);
    }
}

TEST_CASE("Baron Role") {
    Game game;
    Baron baron(game, "Baron");
    Spy p2(game, "P2");

    SUBCASE("Baron invest action") {
        baron.coins = 2;
        CHECK_THROWS_AS(baron.invest(), std::runtime_error);
        
        baron.coins = 3;
        baron.invest();
        CHECK(baron.getCoins() == 6);
        CHECK(game.turn() == "P2");
    }

    SUBCASE("Baron being sanctioned (reaction to sanction)") {
        baron.gather(); // Baron coins = 1. Turn P2.
        
        p2.coins = 4;
        p2.sanction(baron);
        CHECK(baron.get_isSancted());
        CHECK(baron.getCoins() == 1 + 1);
        CHECK(game.turn() == "Baron");
        
        CHECK_THROWS_AS(baron.gather(), std::runtime_error);
		baron.arrest(p2);
        CHECK(baron.get_isSancted() == false);
    }

    SUBCASE("Baron 10+ coins rule with invest") {
        baron.coins = 10;
        CHECK_THROWS_AS(baron.invest(), std::runtime_error);
    }
}

TEST_CASE("General Role") {
    Game game;
    General general(game, "Gen1");
    Spy p2(game, "P2");
    Baron p3(game, "P3");

    SUBCASE("General unCoup (as reaction)") {
        general.coins = 3;
        
        general.gather(); // Gen coins = 4. Turn P2.
		p2.coins = 7;
		p2.coup(p3);
		CHECK_THROWS(general.unCoup(p3));
		cout<<game.players().size()<<endl;
		for (string name : game.toCoup) {
			cout << "- " << name << endl;
		}
		general.coins = 5;
		general.unCoup(p3);
		for (string name : game.toCoup) {
			cout << "- " << name << endl;
		}
		CHECK(general.coins == 0);
		general.gather();
		p2.gather();
		CHECK_NOTHROW(p3.gather());
		CHECK_THROWS(general.unCoup(p3));

    }

	SUBCASE("General unCoup himself") {
		Player p4(game, "P4");
		CHECK(game.players().size() == 4);
		general.tax();
		general.coins = 5;
		p2.coins = 7;
		p2.coup(general);
		CHECK(game.players().size() == 3);
		p3.gather();
		general.unCoup(general);
		CHECK(game.players().size() == 4);
		p4.gather();
		CHECK_NOTHROW(general.tax());
	}
}

TEST_CASE("Judge Role") {
    Game game;
    Judge judge(game, "Judge");
    Player p2(game, "P2");
    Player p3(game, "P3");

    SUBCASE("Judge un_bribe (as reaction)") {
		CHECK_THROWS(judge.un_bribe(p2));
        judge.gather(); // Judge coins = 1. Turn P2.
        p2.coins = 4;
        p2.bribe();     // P2 bribes. P2 coins = 0. P2 gets another turn. Turn P2.

        CHECK_NOTHROW(judge.un_bribe(p2)); // Judge unbribes P2

		p3.gather();
		judge.gather();
        CHECK(game.turn() == "P2");
        
        p2.gather(); // P2 takes an action.
        CHECK(p2.getCoins() == 1);
        CHECK(game.turn() == "P3"); // Turn moved, un_bribe worked.
    }

    SUBCASE("Judge being sanctioned (reaction to sanction)") {
        judge.gather(); // Judge coins = 1. Turn P2.
        
		p2.coins = 3;
		CHECK_THROWS(p2.sanction(judge));
        p2.coins = 4;
        p2.sanction(judge);
        CHECK(judge.get_isSancted());
        CHECK(p2.getCoins() == 0);
		p3.gather();
        CHECK(game.turn() == "Judge");
        
        CHECK_THROWS_AS(judge.gather(), std::runtime_error);
    }
}

TEST_CASE("Merchant Role") {
    Game game;
    Merchant merchant(game, "Mrch");
    Player p2(game, "P2");

    SUBCASE("Merchant bonus coin") {
        merchant.coins = 2;
        merchant.gather();
        CHECK(merchant.getCoins() == 3);
        CHECK(game.turn() == "P2");

        p2.gather();
        merchant.gather();
        CHECK(merchant.getCoins() == 5);
        CHECK(game.turn() == "P2");

        p2.gather();

		merchant.tax();
        CHECK(merchant.getCoins() == 8);
    }
    
    SUBCASE("Merchant 10+ coins rule interaction with bonus") {
        merchant.coins = 9;
        CHECK_NOTHROW(merchant.gather());
        CHECK(merchant.getCoins() == 11);

        p2.gather(); // P2 turn. Turn Mrch.
        CHECK_THROWS_AS(merchant.gather(), std::runtime_error);
		CHECK(merchant.getCoins() == 11);
        CHECK_NOTHROW(merchant.coup(p2)); // P2 removed
        CHECK(merchant.getCoins() == 5); //11 + 1(bonus) -7(coup)
        CHECK(game.turn() == "Mrch");
    }

    SUBCASE("arrest") {
		merchant.tax();
        p2.gather(); // P2 coins = 1. Turn Mrch.
        
        merchant.gather(); // Mrch coins = 3
        
		CHECK(p2.getCoins() == 1);
        p2.arrest(merchant);
        CHECK(p2.getCoins() == 1);
        CHECK(merchant.getCoins() == 3 - 2);
        CHECK(game.turn() == "Mrch");
    }
}

TEST_CASE("Governor Role") {
    Game game;
    Governor gov(game, "Gov");
    Player p2(game, "P2");

    SUBCASE("Governor tax") {
        CHECK(game.turn() == "Gov");
        gov.tax();
        CHECK(gov.getCoins() == 3);
        CHECK(game.turn() == "P2");
    }
	SUBCASE("Governor sanction") {
		p2.coins = 3;
		gov.gather();
		p2.sanction(gov);
		CHECK_THROWS(gov.gather());
		CHECK_THROWS(gov.tax());
		CHECK(gov.getCoins() == 1);
	}

    SUBCASE("Governor undo_tax (as reaction)") {
        gov.gather(); // Gov turn. Gov coins = 1. Turn P2.
        p2.tax();     // P2 turn. P2 coins = 2. P2 lastAct = "tax". Turn Gov.

        CHECK_NOTHROW(gov.undo_tax(p2));
        CHECK(p2.getCoins() == 0);
        CHECK(game.turn() == "Gov");
    }
    
}