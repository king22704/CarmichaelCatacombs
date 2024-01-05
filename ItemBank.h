#ifndef ITEMBANK
#define ITEMBANK

#include "Libraries.h"
#include "Item.h"

class ItemBank{
    public:

        ItemBank();
        Item* findItem(std::string itemName);
        bool hasItem(std::string itemName);
        void incrementQuantity(std::string itemName, int amount);
        void decrementQuantity(std::string itemName, int amount);
        void craft(std::string itemName, std::vector<Item*> *inventory);
        void getItem(std::string itemName, int amount, std::vector<Item*> *inventory);
        void loseItem(std::string itemName, int amount, std::vector<Item*> *inventory);

    private:

        void addToItems(Item *item);
        void makeItems();
        void makeRecipes();
        bool canCraft(std::string itemName);

        hashmap<std::string, Item*> items; 
        hashmap<std::string, std::vector<std::pair<Item*, int> > > craftingTree;

};

#endif
