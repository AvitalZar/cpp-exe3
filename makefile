#tchykzr@gmail.com
CXX = g++ -g
CXXFLAGS = -std=c++2a -Wall -I. -Iroles

main: simpleGame.o player.o game.o
	$(CXX) $(CXXFLAGS) $^ -o $@
	./main

simpleGame.o: simpleGame.cpp game.hpp
	$(CXX) $(CXXFLAGS) -c $<

game.o: game.cpp game.hpp
	$(CXX) $(CXXFLAGS) -c $<


player.o: roles/player.cpp roles/player.hpp game.hpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o main