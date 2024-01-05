#include <string>
#include <iostream>
#include <fstream>
#include "Game.h"

template <typename entity>
void displayStats(entity &fighter);

template <typename entity>
bool isAlive(entity &fighter);

void makePlayer(Game &game);
void query(Game &game);
void newLine();
void toLowerCase(std::string &word);
void newRun(Game &game);
void oldRun(Game &game);
void getInput(std::string &destination);
void hunt(Game &game);
bool fighting(Player &player, Mob &opponent);
void exchange(Player &player, Mob &opponent);
void test();

int main(){
    newLine();
    std::cout << "* Welcome to the Carmichael Catacombs! *" << std::endl;

    Game game;

    makePlayer(game);
    query(game);

    return 0;
}

void makePlayer(Game &game){
    std::string input;
    while(input != "yes" && input != "no"){
        std::cout << "* Would you like to start a new run? *" << std::endl;
        std::cout << "[YES] [NO] [QUIT]" << std::endl;
        newLine();

        std::cout << "Choice: ";
        std::cin >> input;
        toLowerCase(input);
        newLine();

        if(input == "yes"){
            newRun(game);
        }
        else if(input == "no"){
            oldRun(game);
        }
        else if(input == "quit"){
            std::cout << "* Wise choice to leave while you can... *" << std::endl;
            exit(0);
        }
        else{
            std::cout << "* Please reply with [YES] or [NO] *" << std::endl;
        }
    }
}

void query(Game &game){
    bool quit = false;
    std::string action;

    while(!quit){
        game.getPlayer().saveData();

        std::cout << "* What action would you like to take? *" << std::endl;
        std::cout << "[HUNT] [SHOP] [BOSS] [MENU] [QUIT]" << std::endl;

        getInput(action);

        if(action == "hunt"){
            hunt(game);
        }
        else if(action == "shop"){

        }
        else if(action == "boss"){

        }
        else if(action == "menu"){

        }
        else if(action == "quit"){
            quit = true;
            std::cout << "* Your return is awaited by those lurking below... *" << std::endl;
        }
        else{
            std::cout << "* " << action << " is not a valid action! *" << std::endl;
        }
    }
}

void newLine(){
    std::cout << std::endl;
}

void toLowerCase(std::string &word){
    for(unsigned int i = 0; i < word.length(); i++){
        if(word[i] > 64 and word[i] < 91){
            word[i] += 32;
        }
    }
}

void oldRun(Game &game){
    std::string username, password;
    std::cout << "* What is your Username and Password? *" << std::endl;
    newLine();

    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;
    newLine();

    game.newPlayer(username, password);

    if(!game.getPlayer().isSaved()){
        std::cout << "* User " << username << " does not exist! *" << std::endl;
        makePlayer(game);
    }
    else if(!game.getPlayer().correctPassword()){
        std::cout << "* Incorrect Password! *" << std::endl;
        makePlayer(game);
    }
    else{
        std::cout << "* Welcome back " << username << "! *" << std::endl;
        game.getPlayer().readSave();
    }


}

void newRun(Game &game){
    std::string username, password;

    std::cout << "* What would you like your Username and Password to be? *" << std::endl;
    newLine();

    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;
    newLine();
    game.newPlayer(username, password);

    if(game.getPlayer().isSaved()){
        std::cout << "* The name " << username << " is already taken! *" << std::endl;
        makePlayer(game);
    }
    else{
        std::cout << "* I hope you're prepared for what you're about to encounter... *" << std::endl;
        game.getPlayer().saveUsername();
    }
}

void getInput(std::string &destination){
    newLine();

    std::cout << "Action: ";

    std::cin >> destination;
    toLowerCase(destination);

    newLine();
}

void hunt(Game &game){
    std::string action;
    Mob opponent = game.getMob();

    std::cout << "* You've encountered " << opponent.getName() << "! *" << std::endl;
    newLine();
    int availibleItems = 2;
    
    while(fighting(game.getPlayer(), opponent)){
        displayStats(opponent);
        displayStats(game.getPlayer());

        std::cout << "* What would you like to do? *" << std::endl;
        std::cout << "[FIGHT] [ITEM]" << std::endl;

        getInput(action);

        if(action == "fight"){
            exchange(game.getPlayer(), opponent);
        }
        else if(action == "item"){

        }
        else{
            std::cout << "* " << action << " is not a valid action! *" << std::endl;
            newLine();
        }
    }

    if(!isAlive(game.getPlayer())){
        game.getPlayer().revive();
    }    
}

template <typename entity>
void displayStats(entity &fighter){  
    std::cout << fighter.getName() << "'s stats" << std::endl;
    std::cout << "Attack: " << fighter.getStats()[attack] << std::endl;
    std::cout << "Defense: " << fighter.getStats()[defense] << std::endl;
    std::cout << "Health: (" << fighter.getStats()[currhealth] << ")/(" << fighter.getStats()[maxhealth] << ")" << std::endl;
    newLine();
}

bool fighting(Player &player, Mob &opponent){
    return ((player.getStats()[currhealth] > 0) && (opponent.getStats()[currhealth] > 0));
}

void exchange(Player &player, Mob &opponent){
    int damageTaken = opponent.getStats()[attack] - player.getStats()[defense];
    int damageDealt = player.getStats()[attack] - opponent.getStats()[defense];

    if(damageTaken < 0){
        damageTaken = 0;
    }

    if(damageDealt < 0){
        damageDealt = 0;
    }
    
    opponent.takeHit(damageDealt);

    if(!isAlive(opponent)){
        std::cout << "* You dealt " << damageDealt << " damage and have slain " << opponent.getName() << "! *" << std::endl;
        player.getDrops(opponent);
    }
    else{
        player.takeHit(damageTaken);
    }

    if(!isAlive(player)){
        player.die(opponent);
    }
}

template <typename entity>
bool isAlive(entity &fighter){
    return (fighter.getStats()[currhealth] > 0);
}

void test(){
    std::cerr << std::endl;
    std::cerr << "TESTING TESTING TESTING" << std::endl;
    std::cerr << "TESTING TESTING TESTING" << std::endl;
    std::cerr << "TESTING TESTING TESTING" << std::endl;
    std::cerr << std::endl;
}
