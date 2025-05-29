//tchykzr@gmail.com
#include "roles/player.hpp"
using namespace coup;

int main(){
	Game g;

	Player p1(g,"yosi");
	Player p2(g,"dani");

	g.turn();


	try{
        std::cout<<g.winner()<<std::endl;
    } catch (const std::exception &e){
        std::cout << e.what() << '\n';
    }

	p1.tax();
	cout<<p1.getCoins()<<endl;

	try{
		p1.gather();
	} catch (const std::exception &e){
		std::cout<<e.what()<<endl;
	}

	g.turn();
	p2.gather();
	p1.tax();
	
	try{
		p2.bribe();
	} catch (const std::exception &e){
		std::cout<<e.what()<<endl;
	}
	p2.gather();

	g.turn();
	p1.sanction(p2);
	cout<<"Is dani under sanction?	"<<p2.get_isSancted()<<endl;
	
	try{
		p2.gather();
	} catch (const std::exception &e){
		std::cout<<e.what()<<endl;
	}
	cout<<"before arrest - yosi: "<<p1.getCoins()<<"  dani: "<<p2.getCoins()<<endl;

	g.turn();
	p2.arrest(p1);
	
	cout<<"after arrest - yosi: "<<p1.getCoins()<<"  dani: "<<p2.getCoins()<<endl;

	p1.gather();
	p2.tax();
	p1.gather();
	p2.tax();
	p1.tax();

	cout<<"yosi: "<<p1.getCoins()<<"  dani: "<<p2.getCoins()<<endl;
	p2.coup(p1);
	
	cout<<g.winner()<<" won."<<endl;;
	
}