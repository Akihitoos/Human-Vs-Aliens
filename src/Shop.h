#ifndef SHOP_H
#define SHOP_H

#include "interaction.h"

//For a same index, we consider an unique entity
typedef struct Shop
{
    int cursor_shop;
    int cursor_lane;
    int cursor_position;
    int *id;
    int *tab_cost;
}Shop;

//Initializes human and alien shop
Shop* init_shop_human();
Shop* init_shop_alien();

// Free a shop memory
void free_shop(Shop **shop);

//Cursor moves function
void shop_navigate(Shop *shop, int move);

//returns True if the selected entity can be bought
bool can_buy(Shop* shop, Player* player);

void randomize_choice_ai(Shop* alien);

void AIHandler(Shop *alienShop, Player *alienPlayer, Entity **alienArray);

// [Debug] displays the cursors
void afficher_curseurs(Shop* shop);

#endif