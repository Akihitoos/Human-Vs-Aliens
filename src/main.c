#include "update.h"

void delay() 
{
    //Define refresh rate
    clock_t milli_seconds = 1000 / REFRESH_RATE;
  
    //Define the start_time 
    clock_t start_time = clock(); 
  
    //waiting time to be gone
    while (clock() < start_time + milli_seconds); 
}

//test update
int main(int argc, char **argv)
{
    
    int tempsinit, step, game_ended;
    
    // initialization
    Mower mower_array = NULL;
    Entity **human_array = NULL;
    Entity **alien_array = NULL;
    mower_array = init_mower_tab();
    human_array = init_entity_array();
    alien_array = init_entity_array();

    // adding entity
    add_entity(alien_array,-1,0,0);
    add_entity(alien_array,-2,0,0);
    add_entity(alien_array,-3,0,0);
    add_entity(alien_array,-2,1,0);
    add_entity(alien_array,-1,1,0);

    add_entity(human_array,2,0,800);
    add_entity(human_array,1,0,700);
    add_entity(human_array,4,0,600);


    // game loop and display
    
    tempsinit = (int)time(NULL);
    printf("Au temps : %lf\n",tempsinit/CLOCKS_PER_SEC);
    
    
    for(int i = 0; i < 10 ; i++){
        show_tab_order_by_asc(human_array[0]);
        printf("------\n");
        show_tab_order_by_asc(alien_array[1]);
        printf("------ new refresh %d ----------\n",i);
        game_ended = update(human_array, alien_array, mower_array);
        if (game_ended == 1){
            printf("Partie terminee : Les aliens ont gagne\n");
            break;
        }
        if (i == 67){
            add_entity(alien_array,-1,1,0);
        }

        delay();
    }

    // free
    free_array(&human_array, &alien_array);
    free_mower(&mower_array);

    int close = 0;
    do{
        printf("Quit program ? (type 1)\n");
        scanf("%d", &close);
    } while (close != 1);

    return 0;
}
