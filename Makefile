CXX=clang++
CXXFLAGS=-g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS=-g3

play: main.o Game.o Player.o Item.o Mob.o Drop.o ItemBank.o
	$(CXX) $(CXXFLAGS) -o play main.o Game.o Player.o Item.o Mob.o Drop.o ItemBank.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Game.o: Game.cpp Game.h
	$(CXX) $(CXXFLAGS) -c Game.cpp

Player.o: Player.cpp Player.h
	$(CXX) $(CXXFLAGS) -c Player.cpp

Item.o: Item.cpp Item.h
	$(CXX) $(CXXFLAGS) -c Item.cpp

Mob.o: Mob.cpp Mob.h
	$(CXX) $(CXXFLAGS) -c Mob.cpp

Drop.o: Drop.cpp Drop.h
	$(CXX) $(CXXFLAGS) -c Drop.cpp

ItemBank.o: ItemBank.cpp ItemBank.h
	$(CXX) $(CXXFLAGS) -c ItemBank.cpp

clean:
	rm *.o play
	clear

wipeUsers:
	rm *.txt
	clear

reset: clean wipeUsers