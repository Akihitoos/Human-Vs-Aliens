#include <interaction.h>
#include <Entity.h>

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

void add_entity()
{
    int ch1, ch2;
    printf("ALIEN OU HUMAIN ?(1 ou 0)");
    switch (ch1)
    {
    case 1:
        Entity * a = NULL;
        printf("que voulez ajoutez comme Alien");
        printf("1 alien distance");
        prinf("2 alien melee");
        printf("3 alien tank");
        switch (ch2){
            case 1:
                
                break;
            case 2:

                break;
            case 3  :

                break;
            }
            break;
    case 0:
        Entity * h = NULL;
        printf("que voulez ajoutez comme Humain");
        printf("1 alien distance");
        prinf("2 alien melee");
        printf("3 alien tank");
        printf("4 alien tank");
        switch (ch2)
        {
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        }
        break;
    default:
        fprintf(stderr,"ERROR in add_entity");
        break;
    }
}