#ifndef CANNON_H
#define CANNON_H

#include <stdbool.h>
#include "interaction.h"

// Struct defining a boolean tab
typedef bool *Cannon;

//Initialize a boolean tab fully True
Cannon init_cannon_tab();

//Returns 1 if cannon activated, 2 if game ends. If return 1, free the corresponding lane, and disables the cannon.
int activate_cannon(Cannon tab, int lane, Entity **entity_tab);

//Free the cannon tab memory
void free_cannon(Cannon *tab);

#endif