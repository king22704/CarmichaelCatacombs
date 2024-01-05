#ifndef HFNAME
#define HFNAME

#include <ctime>
#include <string>

namespace hf{
    bool happens(double odds){
        srand(time(NULL));
        return ((odds / 100) >= (rand() / double(RAND_MAX)));
    }

    int randInt(int outOf){
        srand(time(NULL));
        return (rand() % outOf);
    }

    double zeroToOne(){
        srand(time(NULL));
        return (rand() / double(RAND_MAX));
    }

    int getInt(std::string word){
        bool negative = false;
        int num = 0;

        if(word[0] == '-'){
            negative = true;
            word.substr(1, word.length() - 2);
        }

        for(unsigned int i = 0; i < word.length(); i++){
            num *= 10;
            num += (word[i] - 48);
        }

        if(negative){
            num *= -1;
        }

        return num;
    }
}

#endif
