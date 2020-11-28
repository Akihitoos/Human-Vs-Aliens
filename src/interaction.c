#include "interaction.h"


// function which initialize tab human


Entity ***initTab_Human(){
    Entity ***p =NULL; 
    int column = 0;
    int row =5;
    p=(Entity***)malloc(row*sizeof(Entity**));
    if(p!=NULL){
        return p;
    }
    else{
        fprintf(stderr,"Allocation error in initTab_Human");
    }
}

// function which initialize tab alien 

Entity ***initTab_Alien(){

    Entity ***p =NULL;
    int column = 0;
    int row =5;
    p=(Entity ***)malloc(row*sizeof(Entity**));
    if(p!=NULL){
        return p;
    }
    else{
        fprintf(stderr, "Allocation error in initTab_Alien");
    }
}



// Function choose your type of human or Alien for debug console

Entity* choose_your_type(int team, int id, int lane, int pos){
    switch (team)
    {
    case 1:     //Alien
        Entity *temp = NULL;
        switch (id)
            {
            case 1:
                temp = create_alien_distance(lane);
                return temp;
                break;
            case 2:
                temp = create_alien_melee(lane);
                return temp;
                break;
            case 3:
                temp = create_alien_tank(lane);
                return temp;
                break;
            }
    case 0:

        Entity *temp = NULL;
        switch (id)
            {
            case 1:
                temp = create_human_ranged(pos, lane);
                return temp;
                break;
            case 2:
                temp = create_human_melee(pos, lane);
                return temp;
                break;
            case 3:
                temp = create_human_tank(pos, lane);
                return temp;
                break;
            case 4:
                temp = create_human_factory(pos, lane);
                return temp;
                break;
            }       
    default:
        fprintf(stderr, "ERROR in add_entity");
        break;
    }
}

void add_entity(int team, int id, int lane, int pos)
{
    Entity *p = NULL;
    p = choose_your_type(team, id, lane, pos);
}

int main (){
    Entity *p = NULL;
    //p=choose_your_type();
    free(p);
    return 0;
}