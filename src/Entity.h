#ifndef ENTITY_H

#include <stdlib.h>
#include <stdio.h>

// Struct defining an Entity
typedef struct Entity Entity;

typedef struct Entity
{
    int id;  // Positive : human | Negative : Alien
    int hp;
    int damage;
    int range;
    int movement_speed;
    int income;
    int position;
    int lane;
    Entity *next;
}Entity;

Entity *create_human_ranged(int positionX, int lane);
Entity *create_human_tank(int positionX, int lane);
Entity *create_human_melee(int positionX, int lane);
Entity *create_human_factory(int positionX, int lane);

Entity* create_alien_range(int lane);
Entity* create_alien_melee(int lane);
Entity* create_alien_tank(int lane);

#endif