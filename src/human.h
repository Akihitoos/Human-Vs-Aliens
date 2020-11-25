#ifndef HUMAN
#define HUMAN

#include <stdio.h>
#include <stdlib.h>

// Struct defining a Human entity
typedef struct{
    int hp;
    int damage;
    int cost;               
    int range;
    double revenus;
    double attack_speed;   // Numbers of attack per seconds
    int position;
    int lane;
} Human;

Human *create_ranged(int positionX, int lane);
Human *create_tank(int positionX, int lane);
Human *create_melee(int positionX, int lane);
Human *create_factory(int positionX, int lane);
void free_human(Human *human);

#endif