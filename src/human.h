#ifndef HUMAN_H
#define HUMAN_H

#include <stdio.h>
#include <stdlib.h>

// Struct defining a Human entity
typedef struct Human Human;

Human *create_ranged(int positionX, int lane);
Human *create_tank(int positionX, int lane);
Human *create_melee(int positionX, int lane);
Human *create_factory(int positionX, int lane);
void free_human(Human *human);

#endif