#ifndef SHOP_H
#define SHOP_H

//For a same index, we consider an unique entity
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