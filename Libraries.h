#ifndef LIBRARIES
#define LIBRARIES

#include <istream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <time.h>
#include "hashmap.h"
#include "triplet.h"

typedef enum {attack = 0, defense, maxhealth, currhealth, xp, level, gold, numstats} statty;
typedef enum {null = -1, weapon, armor, accesory, consumable, material, numitemtys} itemty;
typedef enum {neutral = 0, lifesteal, poison, fire, shieldbreak, numeffects} effectty;
typedef enum {peon = 0, brute, tank, nummobtys} mobty;

#endif
