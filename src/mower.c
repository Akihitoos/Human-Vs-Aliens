#include "mower.h"


//Returns a pointer to the mower tab.
Mower init_mower_tab()
{
    Mower tab = (Mower)malloc(sizeof(Mower)*LANE);
    for (int i =0;i<LANE;i++){
        *(tab+i) = true;
    }
    return tab;
}

//Returns 1 if mower activated, 0 if game ends. If return 1, free the corresponding lane, and disables the mower.
int activate_mower(Mower tab,int lane, Entity **entity_tab){
    if (tab[lane]){
        tab[lane] = false;
        free_tab_content_recursive(entity_tab[lane]);
        entity_tab[lane] = NULL;
        return 1;
    }
    else
    {
        //Game ended
        return 0;
    }
    
}