#ifndef ITEM
#define ITEM

#include <string>
#include <vector>
#include <utility>
#include "Libraries.h"

class Item{

    public:

        Item();
        Item(std::string name, int id);
        Item(std::string name, itemty type, int* stats, int id);

        std::string getName();
        itemty getType();
        int getID();
        int getQuantity();

        void incrementQuantity(int increment);
        void decrementQuantity(int decrement);

    private:

        std::string name;
        itemty type;
        int *stats;
        int quantity, id;

};

#endif
