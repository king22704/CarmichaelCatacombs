#ifndef TRIPLET
#define TRIPLET

template <typename one, typename two, typename three>
class triplet{

    public:
        triplet(){}

        one first;
        two second;
        three third;

        triplet(one first, two second, three third){
            this->first = first;
            this->second = second;
            this->third = third;
        }     
};

#endif
