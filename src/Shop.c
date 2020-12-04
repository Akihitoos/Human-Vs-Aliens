#include "Shop.h"

Shop* init_shop_human(){
    Shop* shop = (Shop*)malloc(sizeof(Shop));
    if (shop == NULL){
        fprintf(stderr,"Malloc error");
        return NULL;
    }
    shop->id = (int*)malloc(sizeof(int)*4);
    shop->tab_cost = (int*)malloc(sizeof(int)*4);
    for (int i = 0;i < 4;i++){
        shop->id[i] = i+1;
    }
    shop->tab_cost[0] = 150;
    shop->tab_cost[1] = 200;
    shop->tab_cost[2] = 400;
    shop->tab_cost[3] = 250;

    return shop;
}


Shop* init_shop_alien(){
    Shop* shop = (Shop*)malloc(sizeof(Shop));
    if (shop == NULL){
        fprintf(stderr,"Malloc error");
        return NULL;
    }
    shop->id = (int*)malloc(sizeof(int)*3);
    shop->tab_cost = (int*)malloc(sizeof(int)*3);
    for(int i = 0; i < 3; i++){
        shop->id[i] = -i-1;
    }
    shop->tab_cost[0] = 150;
    shop->tab_cost[1] = 200;
    shop->tab_cost[2] = 400;

    return shop;
    
}

void free(Shop **shop){
    free(*shop);
    *shop = NULL;
}

void shop_navigate(Shop *shop){
    // +1 -1

}