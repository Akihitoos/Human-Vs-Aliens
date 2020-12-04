#include "update.h"

/*
    Check if the Entity we're on is dead, if so, remove them from the lane.
    The temporary Entity is then replaced with the next one on the list (If there's none,
    we get a NULL pointer)
*/
void commonUpdate(Entity **entity_array, int lane, Entity* entity)
{
    Entity *nextTemp = NULL;
    if(entity->hp < 0){
        nextTemp = entity->next;
        delete_entity_on_lane(entity_array, lane, entity);
        entity = nextTemp; // If we don't do that, our loop will break
    }
}

/*
    Go through every entity of the entity_array, apply common update and attack if in range.
*/
int entityUpdate(Entity** entity_array, Entity** entity, Entity** ennemy_array, int lane, Mower mower_array)
{
    int temp = 0;
    Entity* target = NULL;
    for(;*entity!=NULL;){
        // common update
        commonUpdate(entity_array, lane, *entity);

        // research and move
        if( (*entity)->id > 0 ) {
            target = human_search_alien(*entity, ennemy_array[lane]);
        } else {
            target = alien_search_human(*entity, ennemy_array[lane]);

            // move
            if((target == NULL) || ((*entity)->position - ((*entity)->movement_speed/REFRESH_RATE) >= target->position) )
            {
                move(*entity);

                // Use the mower
            } 
            if((*entity)->position <= 0 ) {
                temp = activate_mower(mower_array, lane, entity_array);
                if (temp == 1){
                    return temp;
                }
            }
        }
        
        //attack
        if(target != NULL){
            attack(*entity, target);
        }

        (*entity)=(*entity)->next;  // Make the loop reach his condition
    }
    return temp;
}


int update (Entity ** human_array, Entity ** alien_array, Mower mower_array)
{
    int game_ended = 0;
    Entity* humanTemp=NULL;
    Entity* alienTemp=NULL;

    human_player->golds += (human_player->gold_per_second/REFRESH_RATE);
    alien_player->golds += (alien_player->gold_per_second/REFRESH_RATE);
    for (int lane = 0; lane <LANE; lane++){

        humanTemp=*(human_array+lane);
        alienTemp=*(alien_array+lane);
        entityUpdate(human_array, &humanTemp, alien_array, lane, mower_array);
        game_ended = entityUpdate(alien_array, &alienTemp, human_array, lane, mower_array);
        if (game_ended == 1){
            return game_ended;
        }
    }    
    return game_ended;
}