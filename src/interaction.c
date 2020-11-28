#include "interaction.h"
#include "Entity.h"



// function which initialize tab human


Entity ***initTab_Human(){
    Entity *** p =NULL; 
    int column = 0;
    int row =5;
    p=(Entity***)calloc(row,sizeof(Entity**));
    if(p!=NULL){
        return p;
    }
    else{
        fprintf(stderr,"Allocation error in initTab_Human");
    }
}

// function which initialize tab alien 

Entity ***initTab_Alien(){

    Entity *** p =NULL;
    int column = 0;
    int row =5;
    p=(Entity ***)calloc(row, sizeof(Entity**));
    if(p!=NULL){
        return p;
    }
    else{
        fprintf(stderr, "Allocation error in initTab_Alien");
    }
}



// Function choose your type of human or Alien for debug console

Entity * choose_your_type(){
    int ch1, ch2, posX, lane;
    printf("ALIEN OU HUMAIN ?(1 ou 0)");
    scanf("%d", &ch1);
    switch (ch1)
    {
    case 1:
        printf("entre une lane");
        scanf("%d", &lane);
        Entity *a = NULL;
        printf("que voulez ajoutez comme Alien");
        printf("1 alien distance");
        printf("2 alien melee");
        printf("3 alien tank");
        scanf("%d", &ch2);
        switch (ch2)
            {
            case 1:
                a = create_alien_distance(lane);
                return a;
                break;
            case 2:
                a = create_alien_melee(lane);
                return a;
                break;
            case 3:
                a = create_alien_tank(lane);
                return a;
                break;
            }
    case 0:

        Entity *h = NULL;
        printf("quelle type voulez vous ajoutez comme Humain");
        printf("1 humain distance");
        printf("2 humain melee");
        printf("3 humain tank");
        printf("4 humain tank");
        scanf("%d", &ch2);
        printf("entre une posX et une lane");
        scanf("%d", &posX);
        scanf("%d", &lane);
        switch (ch2)
            {
            case 1:
                h = create_human_ranged(posX, lane);
                return h;
                break;
            case 2:
                h = create_human_melee(posX, lane);
                return h;
                break;
            case 3:
                h = create_human_tank(posX, lane);
                return h;
                break;
            case 4:
                h = create_human_factory(posX, lane);
                return h;
                break;
            }       
    default:
        fprintf(stderr, "ERROR in add_entity");
        break;
    }
}

void add_entity()
{
    Entity * p = NULL;
    p=choose_your_type();
    // if((*p).id <1){
        
    // }

}

int main (){
    Entity *p = NULL;
    p=choose_your_type();
    free(p);
    return 0;
}