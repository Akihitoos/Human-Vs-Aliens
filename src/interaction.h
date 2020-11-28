#include <stdio.h>
#include <stdlib.h>


// function which init Table Human
Entity *** initTab_Human ();

// function which init Table Alien
Entity *** initTab_Alien ();

// function which add a Entity structure in Alien_Tab or Human_Table
void add_entity ();



// function which manage interaction between Alien and Human

void search (Entity * Tab_Human, Entity * Tab_Alien);
void attack (Entity * human, Entity * alien);
