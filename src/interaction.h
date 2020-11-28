#ifndef INTERACTION_H
#define INTERACTION_H

#include <stdio.h>
#include <stdlib.h>
#include "Entity.h"

#define LANE 5

// function which initialize a simple array of entity
Entity **init_entity_array();

// function which add a Entity structure in Alien_Tab or Human_Table
void add_entity();

// Function returning an Entity depending on his id
Entity* create_entity_on_id(int id, int lane, int pos);

// Add an Entity to a Lane
void add_entity_to_lane(Entity *lane, Entity *new);

// create an Entity (depending on the id) and add it to a simple array of entity
void add_entity(Entity **simpleArray, int id, int lane, int pos);

// function which manage interaction between Alien and Human
Entity* alien_search_human (Entity * Alien, Entity * tab_human);
Entity* human_search_alien (Entity * human, Entity * tab_alien);
void attack (Entity *attacker, Entity *attacked);

#endif