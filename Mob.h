#ifndef MOB
#define MOB

#include "Libraries.h"
#include "Drop.h"

class Mob{

    public:
        Mob();
        Mob(std::string name, int att, int def, int hp, mobty type);
        Mob(std::string name, int att, int def, int hp, mobty type, std::pair<std::string, int> effect);
        std::string getName();
        int* getStats();
        mobty getType();
        void takeHit(int damage);
        void addDrop(std::string itemName, int amount, double odds);
        std::vector<Drop> getDrops();

    private:
        std::string name;
        int stats[4];
        mobty type;
        std::pair<std::string, int> effect;
        std::vector<Drop> drops;

};

#endif
