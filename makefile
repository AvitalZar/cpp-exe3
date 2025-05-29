#tchykzr@gmail.com
CXX = g++ -g
CXXFLAGS = -std=c++2a -Wall -fPIC -I. -Iroles -Iroles/headers -Iroles/sources -IGUI -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtGui
LDFLAGS = $(shell pkg-config --libs Qt5Widgets)
PHEADER_FILES = $(wildcard roles/headers/*) roles/player.hpp
POBJ_FILES = $(notdir $(PHEADER_FILES:.hpp=.o))

main: Demo.o $(POBJ_FILES) game.o
	$(CXX) $(CXXFLAGS) $^ -o $@
	./main

test: test.o game.o $(POBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@
	./test

run: run.cpp
	$(CXX) run.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
	./sfml-app
qt: cute.o main_win.o main_win.moc.o turn_win.o  turn_win.moc.o $(POBJ_FILES) game.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	./qt
	

cute.o: GUI/cute.cpp GUI/cute.hpp GUI/main_win.hpp game.hpp
	$(CXX) $(CXXFLAGS) -c $<
main_win.o: GUI/main_win.cpp GUI/main_win.hpp $(PHEADER_FILES) game.hpp
	$(CXX) $(CXXFLAGS) -c $<

main_win.moc.cpp: GUI/main_win.hpp
	moc GUI/main_win.hpp -o $@
main_win.moc.o: main_win.moc.cpp
	$(CXX) $(CXXFLAGS) -c main_win.moc.cpp
	
turn_win.o: GUI/turn_win.cpp GUI/turn_win.hpp $(PHEADER_FILES) game.hpp
	$(CXX) $(CXXFLAGS) -c $<

turn_win.moc.cpp: GUI/turn_win.hpp
	moc GUI/turn_win.hpp -o $@
turn_win.moc.o: turn_win.moc.cpp
	$(CXX) $(CXXFLAGS) -c turn_win.moc.cpp


simpleGame.o: simpleGame.cpp game.hpp
	$(CXX) $(CXXFLAGS) -c $<

Demo.o: Demo.cpp game.hpp $(PHEADER_FILES)
	$(CXX) $(CXXFLAGS) -c $<

game.o: game.cpp game.hpp
	$(CXX) $(CXXFLAGS) -c $<

test.o: test.cpp doctest.h
	$(CXX) $(CXXFLAGS) -c $<

player.o: roles/player.cpp roles/player.hpp game.hpp
	$(CXX) $(CXXFLAGS) -c $<



%.o: roles/sources/%.cpp roles/headers/%.hpp roles/player.hpp game.hpp
	$(CXX) $(CXXFLAGS) -c $<


valgrind: main
	valgrind --leak-check=full ./main

clean:
	rm -f *.o main test qt sfml-app