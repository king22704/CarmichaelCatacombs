#ifndef PLAYER
#define PLAYER

#include "Libraries.h"
#include "ItemBank.h"
#include "Mob.h"

class Player{

    public:

        Player();
        ~Player();
        void newPlayer(std::string newName, std::string newPassword);
        void getItem(std::string itemName, int amount);
        void loseItem(std::string itemName, int amount);        
        void displayInventory();
        void craft(std::string itemName);
        void saveData();
        void saveUsername();
        void readSave();
        void equip(std::string itemName);
        void unequip();

        bool isSaved();
        bool correctPassword();
        bool hasItem(std::string itemName);

        std::string getName();
        int* getStats();
        void takeHit(int damage);

        void getDrops(Mob opponent);
        bool happens(double odds);
        double zeroToOne();
        int randInt(int outOF);

        void die(Mob &opponent);
        void revive();

    private:

        void saveStats(std::ofstream &saveFile);
        void saveEquiped(std::ofstream &saveFile);
        void saveItems(std::ofstream &saveFile);

        void readStats(std::ifstream &saveFile);
        void readEquiped(std::ifstream &saveFile);
        void readItems(std::ifstream &saveFile);

        int getItemCount(std::string itemName);


        std::string name, password;
        int stats[7];
        Item *equiped[3];

        //use enumerated item types to access inventories of said item type
        std::vector<Item*> *inventory = new std::vector<Item*>[5]; 
        ItemBank items;

};

#endif
