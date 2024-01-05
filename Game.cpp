#include "Game.h"

Game::Game(){
    floor = 1;
    srand(time(NULL));
    this->makeMobs();
}

Game::~Game(){}

void Game::makeMobs(){

    Mob lunchLady("Lunch Lady", 8, 2, 20, peon);
    Mob cashier("Cashier", 12, 0, 15, brute);
    Mob chef("Chef", 6, 4, 30, tank);

    lunchLady.addDrop("Fries", 4, 0.50);
    cashier.addDrop("Fries", 4, 0.50);
    chef.addDrop("Fries", 4, 0.50);

    Mob *floorOne = new Mob[3];
    floorOne[peon] = lunchLady;
    floorOne[brute] = cashier;
    floorOne[tank] = chef;

    mobs.push_back(floorOne);
}

Player& Game::getPlayer(){
    return this->player;
}

void Game::setPlayer(Player player){
    this->player = player;
}

void Game::newPlayer(std::string newName, std::string newPassword){
    this->player.newPlayer(newName, newPassword);
}

Mob Game::getMob(){
    return mobs.at(floor - 1)[randInt(3)];
}

bool Game::happens(double odds){
    return (odds >= zeroToOne());
}
int Game::randInt(int outOf){
    return (rand() % outOf);
}
double Game::zeroToOne(){
    return (rand() / double(RAND_MAX));
}

int Game::getInt(std::string word){
    bool negative = false;
    int num = 0;
    if(word[0] == '-'){
        negative = true;
        word.substr(1, word.length() - 2);
    }
    for(unsigned int i = 0; i < word.length(); i++){
        num *= 10;
        num += (word[i] - 48);
    }
    if(negative){
        num *= -1;
    }
    return num;
}
