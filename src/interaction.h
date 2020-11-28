#include <stdio.h>
#include <stdlib.h>
#include "Entity.h"

// function which init Table Human
Entity ** initTab_Human ();

// function which init Table Alien
Entity ** initTab_Alien ();

// function which add a Entity structure in Alien_Tab or Human_Table
void add_entity ();


// function which permite to choose your type and put in position for console_debug
Entity* choose_your_type(int team, int id, int lane, int pos);

// Function which add an element in the chained list Alien
Entity ***add_in_Alien(Entity *alien, Entity ** Tab_Alien);

// Function which add an element in the chained list Human
Entity ***add_in_Human(Entity *alien, Entity ** Tab_Human);

// function which manage interaction between Alien and Human

void search (Entity * Tab_Human, Entity * Tab_Alien);
void attack (Entity * human, Entity * alien);
