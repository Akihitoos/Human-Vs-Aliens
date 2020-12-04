#ifndef MOWER_H
#define MOWER_H

#include <stdio.h>
#include <stdlib.h>
#include "Entity.h"
#include <stdbool.h>
#include "interaction.h"
#include <time.h>

#define REFRESH_RATE 10

// Struct defining a boolean tab
typedef bool *Mower;

//Initialize a boolean tab fully True
Mower init_mower_tab();

//Returns 1 if mower activated, 0 if game ends. If return 1, free the corresponding lane, and disables the mower.
int activate_mower(Mower tab,int lane, Entity **entity_tab);

//Free the mower tab memory
void free_mower(Mower* tab);


#endif