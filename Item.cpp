#include "Item.h"

Item::Item(){
    int nullStats[3] = {0, 0, 0};

    this->name = "Empty";
    this->type = material;
    this->stats = nullStats;
    this->quantity = 0;
    this->id = -1;
}

Item::Item(std::string name, int id){
    int nullStats[3] = {0, 0, 0};

    this->name = name;
    this->type = material;
    this->stats = nullStats;
    this->quantity = 0;
    this->id = id;

}

Item::Item(std::string name, itemty type, int *stats, int id){
    this->name = name;
    this->type = type;
    this->stats = stats;
    this->quantity = 0;
    this->id = id;
}

std::string Item::getName(){
    return this->name;
}

itemty Item::getType(){
    return this->type;
}

int Item::getID(){
    return this->id;
}

int Item::getQuantity(){
    return this->quantity;
}

void Item::incrementQuantity(int increment){
    this->quantity += increment;
}

void Item::decrementQuantity(int decrement){
    this->quantity -= decrement;
}
