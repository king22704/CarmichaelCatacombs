#ifndef DROP
#define DROP

#include "Libraries.h"

class Drop{

    public:
        Drop();
        Drop(std::string name, int amount, double dropRate);
        std::string getName();
        int getAmount();
        double getRate();
        void setDrop(std::string name, int amount, double dropRate);


    private:

        std::string name;
        int amount;
        double dropRate;

};

#endif
