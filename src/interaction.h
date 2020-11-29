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

// Delete an entity on the lane (using it's pointer)
void delete_entity_on_lane(Entity **simpleArray,int lane, Entity *todelete);

// Free an entire lane, by passing the first element
void free_tab_content_recursive(Entity *entity);

// Free the two array dealing with the Entity on the board (for the end game)
void free_array(Entity **Human, Entity **Alien);

// Function wich return the entity closest to the ALien in it's range
Entity* alien_search_human (Entity * Alien, Entity * tab_human);

// Function wich return the entity closest to the Human in it's range
Entity* human_search_alien (Entity * human, Entity * tab_alien);

//Inflict damage of the attacker to the attacked
void attack (Entity *attacker, Entity *attacked);

// Make the entity move depending on his movement_speed
void move(Entity *alien);

#endif