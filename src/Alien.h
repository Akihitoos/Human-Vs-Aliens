#ifndef ALIEN
#define ALIEN

#include <stdio.h>
#include <stdlib.h>

typedef struct Alien Alien;

Alien* create_distance();
Alien* create_melee();
Alien* create_tank();
void move(Alien *alien);
void upon_death(Alien *alien);
#endif