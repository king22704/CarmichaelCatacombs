#include "Drop.h"

Drop::Drop(){}

Drop::Drop(std::string name, int amount, double dropRate){
    this->name = name;
    this->amount = amount;
    this->dropRate = dropRate;
}

std::string Drop::getName(){
    return this->name;
}

int Drop::getAmount(){
    return this->amount;
}

double Drop::getRate(){
    return this->dropRate;
}

void Drop::setDrop(std::string name, int amount, double dropRate){
    this->name = name;
    this->amount = amount;
    this->dropRate = dropRate;
}
