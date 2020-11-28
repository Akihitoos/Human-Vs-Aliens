#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <stdlib.h>

// Struct defining an Entity
typedef struct Entity Entity;

Entity *create_human_ranged(int positionX, int lane);
Entity *create_human_tank(int positionX, int lane);
Entity *create_human_melee(int positionX, int lane);
Entity *create_human_factory(int positionX, int lane);

Entity* create_alien_distance(int lane);
Entity* create_alien_melee(int lane);
Entity* create_alien_tank(int lane);

void move(Entity *alien);
void free_entity(Entity *entity);

#endif