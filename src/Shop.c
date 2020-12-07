#include "Shop.h"

Shop* init_shop_human(){
    Shop* shop = (Shop*)malloc(sizeof(Shop));
    if (shop == NULL){
        fprintf(stderr,"Malloc error");
        return NULL;
    }
    shop->id = (int*)malloc(sizeof(int)*4);
    shop->tab_cost = (int*)malloc(sizeof(int)*4);
    if ((shop->id == NULL) || (shop->tab_cost == NULL)){
        fprintf(stderr,"Malloc error");
    }
    for (int i = 0;i < 4;i++){
        shop->id[i] = i+1;
    }
    shop->tab_cost[0] = 150;
    shop->tab_cost[1] = 200;
    shop->tab_cost[2] = 400;
    shop->tab_cost[3] = 250;
    shop->cursor_shop = 1;
    shop->cursor_lane = 0;
    shop->cursor_position = 0;

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
    if ((shop->id == NULL) || (shop->tab_cost == NULL)){
        fprintf(stderr,"Malloc error");
    }
    for(int i = 0; i < 3; i++){
        shop->id[i] = -i-1;
    }
    shop->tab_cost[0] = 150;
    shop->tab_cost[1] = 200;
    shop->tab_cost[2] = 400;
    shop->cursor_shop = -1;
    shop->cursor_lane = 0;
    shop->cursor_position = 1000;

    return shop;
    
}

void free_shop(Shop **shop){
    free(*shop);
    *shop = NULL;
}

/**
 * Navigates in the shop, using 3 cursors : One selects the ID, the 2nd determines the lane, and the 3rd the position
 * 1/-1 : moves cursop shop (Q D or left right)     2/-2 : moves lane cursor (Z S or up down)     3/-3 : moves position cursor (A E (human only))
 **/
void shop_navigate(Shop *shop, int move){
    if(shop->id[0] > 0){
        switch (move)
        {
        case 1:
            shop->cursor_shop += 1;
            if(shop->cursor_shop > 4){
                shop->cursor_shop = 1;
            }
            break;
        case -1:
            shop->cursor_shop -= 1;
            if(shop->cursor_shop < 1){
                shop->cursor_shop = 4;
            }
            break;
        case 2:
            shop->cursor_lane += 1;
            shop->cursor_lane %= 5;
            break;
        case -2:
            shop->cursor_lane -=1;
            if (shop->cursor_lane <0){
                shop->cursor_lane = 4;
            }
            break;
        case 3:
            shop->cursor_position += 100;
            if (shop->cursor_position > 1000){
                shop->cursor_position = 0;
            }
            break;
        case -3:
            shop->cursor_position -= 100;
            if (shop->cursor_position < 0){
                shop->cursor_position = 1000;
            }
            break;
        default:
            break;
        }
    }
    else if(shop->id[0] < 0){
        switch (move)
        {
        case 1:
            shop->cursor_shop -= 1;
            if (shop->cursor_shop < -3){
                shop->cursor_shop = -1;
            }
            break;
        case -1:
            shop->cursor_shop += 1;
            if (shop->cursor_shop > -1){
                shop->cursor_shop = -3;
            }
            break;
        case 2:
            shop->cursor_lane += 1;
            shop->cursor_lane %= 5;
            break;
        case -2:
            shop->cursor_lane -=1;
            if (shop->cursor_lane <0){
                shop->cursor_lane = 4;
                break;
            }
        default:
            break;
        }
    }
}

bool can_buy(Shop* shop, Player* player){
    if (shop->id[0] != 0){
        return (player->golds >= shop->tab_cost[shop->cursor_shop]);
    }
    return false;
}

void afficher_curseurs(Shop* shop){
    printf("shop : %d\t pos : %d\tlane : %d\n",shop->cursor_shop,shop->cursor_position,shop->cursor_lane);
}

