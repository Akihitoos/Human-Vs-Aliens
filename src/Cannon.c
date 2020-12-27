#include "cannon.h"


//Returns a pointer to the cannon tab.
Cannon init_cannon_tab()
{
    Cannon tab = (Cannon)malloc(sizeof(Cannon)*LANE);
    for (int i =0;i<LANE;i++){
        *(tab+i) = true;
    }
    return tab;
}

//Returns 1 if cannon activated, 2 if game ends. If return 1, free the corresponding lane, and disables the cannon.
int activate_cannon(Cannon tab,int lane, Entity **entity_tab){
    if (tab[lane]){
        tab[lane] = false;
        free_tab_content_recursive(entity_tab[lane]);
        entity_tab[lane] = NULL;
        return 1;
    }
    else
    {
        printf("GAME ENDED !\n");
        return 2;
    }
}

void free_cannon(Cannon *tab){
    free(*tab);
    *tab = NULL;
}