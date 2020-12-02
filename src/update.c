#include "update.h"

void update (Entity ** array, Entity ** enemy_array)
{
    Entity * temp=NULL;
    Entity * target=NULL;

    for (int lane = 0; lane <LANE; lane++){

        temp=*(array+lane);

        for(;temp!=NULL;){
            // common update
            if (temp->hp <=0)
            {
                delete_entity_on_lane(array,lane,temp);
            }


            // human update
            if(temp->id>0){

                target = human_search_alien(temp,enemy_array);
                if(target != NULL){
                    attack(temp,target);
                }



                
            }

            // alien update
            if (temp->id < 0)
            {


               target = alien_search_human(temp,enemy_array);
               if(target!=NULL){
                   attack(temp,target);
               }

            }

            temp=temp->next;
        }    
}

