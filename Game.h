#ifndef GAME
#define GAME

#include "Libraries.h"
#include "Mob.h"
#include "Item.h"
#include "Player.h"

class Game{

    public:

        Game();
        ~Game();
        Player& getPlayer();
        void setPlayer(Player player);
        void makeMobs();
        void newPlayer(std::string newName, std::string newPassword);
        Mob getMob();
        bool happens(double odds);
        double zeroToOne();
        int getInt(std::string word);
        int randInt(int outOF);

    private:

        std::vector<Mob*> mobs;
        Player player;
        int floor;
};

#endif
