#include "ItemBank.h"

ItemBank::ItemBank(){
    this->makeItems();
    this->makeRecipes();
}

void ItemBank::addToItems(Item *item){
    items[item->getName()] = item;
}

Item* ItemBank::findItem(std::string itemName){
    return items[itemName];
}

bool ItemBank::hasItem(std::string itemName){
    return (items[itemName]->getQuantity() > 0);
}

void ItemBank::incrementQuantity(std::string itemName, int amount){
    items[itemName]->incrementQuantity(amount);
}

void ItemBank::decrementQuantity(std::string itemName, int amount){
    items[itemName]->decrementQuantity(amount);
}

//states if a player can craft an item
bool ItemBank::canCraft(std::string itemName){
    for(std::pair<Item*, int> recipe : craftingTree[itemName]){
        if(recipe.first->getQuantity() < recipe.second){
            return false;
        }
    }

    return true;
}

//crafts an item if the player can afford it
void ItemBank::craft(std::string itemName, std::vector<Item*> *inventory){
    if(canCraft(itemName)){
        for(std::pair<Item*, int> recipe : craftingTree[itemName]){
            recipe.first->decrementQuantity(recipe.second);
        }

        this->getItem(itemName, 1, inventory);
        std::cout << "You have successfully crafted: " << itemName << "!" << std::endl;
    }
    else{
        std::cout << "You do not have the materials required to craft: " << itemName << "!" << std::endl;
    }
}

void ItemBank::getItem(std::string itemName, int amount, std::vector<Item*> *inventory){
    Item *item = items[itemName];
    if(!hasItem(itemName)){
        for(unsigned int i = 0; i < inventory[item->getType()].size(); i++){
            if(item->getID() < inventory[item->getType()].at(i)->getID()){
                inventory[item->getType()].insert(inventory[item->getType()].begin() + i, item);
                item->incrementQuantity(amount);
                break;
            }
        }

        if(!hasItem(itemName)){
            inventory[item->getType()].push_back(item);
            item->incrementQuantity(amount);
        }
    }
    else{
        item->incrementQuantity(amount);
    }
}

void ItemBank::loseItem(std::string itemName, int amount, std::vector<Item*> *inventory){
    Item *item = items[itemName];
    item->decrementQuantity(amount);

    if(!hasItem(itemName)){
        for(unsigned int i = 0; i < inventory[item->getType()].size(); i++){
            if(inventory[item->getType()].at(i) == item){
                inventory[item->getType()].erase(inventory[item->getType()].begin() + i);
                break;
            }
        }

    }
}

void ItemBank::makeRecipes(){
    std::pair<Item*, int> parPaperCost(items["Paper"], 5);

    std::vector<std::pair<Item*, int> >paperArmorRecipe;

    paperArmorRecipe.push_back(parPaperCost);

    craftingTree["Paper Armor"] = paperArmorRecipe;
}

void ItemBank::makeItems(){
    int nullStats[3] = {-1, -1, -1};
    int knifeStats[3] = {3, 1, 0};
    int spoonStats[3] = {2, 1, 0};
    int paperStats[3] = {0, 0, 0};
    int paperArmorStats[3] = {1, 3, 2};
    int friesStats[3] = {0, 0, 0};

    //Item itemName = new Item("name", type, stats, quantity, id);
    Item *empty = new Item("Empty", null, nullStats, -1);
    Item *knife = new Item("Knife", weapon, knifeStats, 0);
    Item *spoon = new Item("Spoon", weapon, spoonStats, 1);
    Item *paper = new Item("Paper", material, paperStats, 2);
    Item *paperArmor = new Item("Paper Armor", armor, paperArmorStats, 3);
    Item *fries = new Item("Fries", consumable, friesStats, 4);

    addToItems(empty);
    addToItems(knife);
    addToItems(spoon);
    addToItems(paper);
    addToItems(paperArmor);  
    addToItems(fries);
}
