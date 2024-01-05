#include "Mob.h"

Mob::Mob(){}

Mob::Mob(std::string name, int att, int def, int hp, mobty type){
    this->name = name;

    stats[attack] = att;
    stats[defense] = def;
    stats[maxhealth] = hp;
    stats[currhealth] = hp;

    this->type = type;
}

Mob::Mob(std::string name, int att, int def, int hp, mobty type, std::pair<std::string, int> effect){
    this->name = name;

    stats[attack] = att;
    stats[defense] = def;
    stats[maxhealth] = hp;
    stats[currhealth] = hp;

    this->type = type;
    this->effect = effect;
}

std::string Mob::getName(){
    return this->name;
}

int* Mob::getStats(){
    return this->stats;
}

mobty Mob::getType(){
    return this->type;
}

void Mob::takeHit(int damage){
    this->stats[currhealth] -= damage;
    
    if(stats[currhealth] < 0){
        stats[currhealth] = 0;
    }
}

void Mob::addDrop(std::string itemName, int amount, double odds){
    Drop mobDrop = Drop(itemName, amount, odds);
    drops.push_back(mobDrop);
}

std::vector<Drop> Mob::getDrops(){
    return this->drops;
}
