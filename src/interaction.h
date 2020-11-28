#ifndef INTERACTION_H
#define INTERACTION_H

#include <stdio.h>
#include <stdlib.h>
#include "Entity.h"

#define LANE 5

// function which initialize a double array of entity
Entity ***init_entity_double_array();

// function which add a Entity structure in Alien_Tab or Human_Table
void add_entity();

// Function returning an Entity depending on his id
Entity* create_entity_on_id(int id, int lane, int pos);

// Add an Entity to a Lane
Entity ***add_entity_to_lane(Entity **lane, Entity *new);

// create an Entity (depending on the id) and add it to a double array of entity
void add_entity(Entity ***doubleArray, int id, int lane, int pos);

// function which manage interaction between Alien and Human
void search (Entity * Tab_Human, Entity * Tab_Alien);
void attack (Entity * human, Entity * alien);

#endif