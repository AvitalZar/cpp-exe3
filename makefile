#tchykzr@gmail.com
CXX = g++ -g
CXXFLAGS = -std=c++2a -Wall -I. -Iroles
PHEADER_FILES = $(wildcard roles/*.hpp)
POBJ_FILES = $(notdir $(PHEADER_FILES:.hpp=.o))

main: Demo.o $(POBJ_FILES) game.o
	$(CXX) $(CXXFLAGS) $^ -o $@
	./main

test: test.o game.o $(POBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@
	./test

simpleGame.o: simpleGame.cpp game.hpp
	$(CXX) $(CXXFLAGS) -c $<

Demo.o: Demo.cpp game.hpp $(PHEADER_FILES)
	$(CXX) $(CXXFLAGS) -c $<

game.o: game.cpp game.hpp
	$(CXX) $(CXXFLAGS) -c $<

test.o: test.cpp doctest.h
	$(CXX) $(CXXFLAGS) -c $<


%.o: roles/%.cpp roles/%.hpp roles/player.hpp game.hpp
	$(CXX) $(CXXFLAGS) -c $<



#player.o: roles/player.cpp roles/player.hpp game.hpp
#	$(CXX) $(CXXFLAGS) -c $<

valgrind: main
	valgrind --leak-check=full ./main

clean:
	rm -f *.o main test