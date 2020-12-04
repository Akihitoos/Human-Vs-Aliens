#ifndef SHOP_H
#define SHOP_H

#include <stdio.h>
#include <stdlib.h>
#include "interaction.h"
#include "Entity.h"
#include "Player.h"

typedef struct Shop
{
    int cursor;
    int *id;
    int *tab_cost;
}Shop;

//Initializes human and alien shop
Shop* init_shop_human();
Shop* init_shop_alien();

// Free a shop memory
void free(Shop **shop);


#endif