#include "Player.h"

Player::Player(){
    stats[attack] = 10;
    stats[defense] = 0;
    stats[maxhealth] = 100;
    stats[currhealth] = 100;
    stats[xp] = 0;
    stats[level] = 1;
    stats[gold] = 0;

    unequip();
}

Player::~Player(){}

//for when a player gets an item
void Player::getItem(std::string itemName, int amount){
    items.getItem(itemName, amount, inventory);
}

//for when a player loses an item
void Player::loseItem(std::string itemName, int amount){
    items.loseItem(itemName, amount, inventory);
}

//displays the player's items
void Player::displayInventory(){
    for(int i = 0; i < 5; i++){
        for(unsigned int j = 0; j < inventory[i].size(); j++){
            Item *item = inventory[i].at(j);
            std::cout << item->getName() << ": " << item->getQuantity() << std::endl;
        }
    }
}

//gives the amount of an item a player has
int Player::getItemCount(std::string itemName){
    return items.findItem(itemName)->getQuantity();
}

//crafts an item if the player can afford it
void Player::craft(std::string itemName){
    items.craft(itemName, inventory);
}

//saves player data
void Player::saveData(){
    std::ofstream saveFile;
    std::string filename = "SaveStates/" + this->name + ".txt";

    saveFile.open(filename);

    saveFile << this->password << " ";
    saveStats(saveFile);
    saveEquiped(saveFile);
    saveItems(saveFile);

    saveFile.close();
}

void Player::saveUsername(){
    std::ifstream usernames;
    std::ofstream saveFile;
    std::string names;
    usernames.open("users.txt");

    std::vector<std::string> users;

    while(usernames >> names){
        if(names == this->name){
            return;
        }
        users.push_back(names);
    }

    usernames.close();

    users.push_back(this->name);

    saveFile.open("users.txt");

    for(std::string person : users){
        saveFile << person;
        saveFile << " ";
    }

    saveFile.close();
}

bool Player::isSaved(){
    std::ifstream names;
    std::string username;

    names.open("users.txt");

    while(names >> username){
        if(username == this->name){
            return true;
        }
    }

    return false;
}

void Player::readSave(){
    std::ifstream saveFile;
    std::string filename = "SaveStates/" + this->name + ".txt";
    std::string pass;
    saveFile.open(filename);

    saveFile >> pass;
    readStats(saveFile);
    readEquiped(saveFile);
    readItems(saveFile);

    saveFile.close();
}

void Player::newPlayer(std::string newName, std::string newPassword){
    this->name = newName;
    this->password = newPassword;
}

void Player::readStats(std::ifstream &saveFile){
    for(int i = 0; i < numstats; i++){
        saveFile >> stats[i];
    }
}

void Player::readEquiped(std::ifstream &saveFile){
    std::string itemName;

    for(int i = 0; i < 3; i++){
        saveFile >> itemName;
        equiped[i] = items.findItem(itemName);
    }
}

void Player::readItems(std::ifstream &saveFile){
    std::string itemName;
    int numItems;
    
    while(saveFile >> itemName){
        saveFile >> numItems;

        this->getItem(itemName, numItems);
    }
}

void Player::saveStats(std::ofstream &saveFile){
    for(int i = 0; i < numstats; i++){
        saveFile << stats[i] << " ";
    }
}

void Player::saveEquiped(std::ofstream &saveFile){
    saveFile << equiped[weapon]->getName() << " ";
    saveFile << equiped[armor]->getName() << " ";
    saveFile << equiped[accesory]->getName() << " ";
}

void Player::saveItems(std::ofstream &saveFile){
    for(int i = 0; i < 5; i++){
        for(Item *item : inventory[i]){
            saveFile << item->getName() << " ";
            saveFile << item->getQuantity() << " ";
        }
    }
}

void Player::equip(std::string itemName){
    Item *item = items.findItem(itemName);

    if(item->getType() == null){
        equiped[weapon] = item;
        equiped[armor] = item;
        equiped[accesory] = item;
    }
    else{
        equiped[item->getType()] = item;
    }
}

void Player::unequip(){
    this->equip("Empty");
}

bool Player::correctPassword(){
    std::string realPassword;
    std::string filename = "SaveStates/" + this->name + ".txt";
    std::ifstream saveFile;
    saveFile.open(filename);

    saveFile >> realPassword;

    saveFile.close();
    return (this->password == realPassword);
}

std::string Player::getName(){
    return this->name;
}

int* Player::getStats(){
    return this->stats;
}

void Player::takeHit(int damage){
    this->stats[currhealth] -= damage;
    
    if(stats[currhealth] < 0){
        stats[currhealth] = 0;
    }
}

void Player::getDrops(Mob opponent){
    for(Drop drop : opponent.getDrops()){
        if(happens(drop.getRate())){
            std::cout << "* You have gotten " << drop.getAmount() << " " << drop.getName() << "! *" << std::endl;
            std::cout << std::endl;

            getItem(drop.getName(), drop.getAmount());
        }
    }
}

bool Player::hasItem(std::string itemName){
    return items.hasItem(itemName);
}

bool Player::happens(double odds){
    return (odds >= zeroToOne());
}
int Player::randInt(int outOf){
    return (rand() % outOf);
}
double Player::zeroToOne(){
    return (rand() / double(RAND_MAX));
}

void Player::die(Mob &opponent){
    std::cout << "* You have been slain by " << opponent.getName();

    if(stats[level] > 1){
        std::cout << " and have lost a level";
        stats[level]--;
    }

    std::cout << "! *" << std::endl;

    stats[xp] = 0;
}

void Player::revive(){
    stats[currhealth] = stats[maxhealth];
}
