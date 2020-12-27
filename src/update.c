#include "update.h"

/*
    Check if the Entity we're on is dead, if so, remove them from the lane.
    The temporary Entity is then replaced with the next one on the list (If there's none,
    we get a NULL pointer)
*/
void commonUpdate(Entity **entity_array, int lane, Entity* entity, int *hasBeenDeleted)
{
    Entity *nextTemp = NULL;
    if(entity->hp < 0){
        nextTemp = entity->next;
        delete_entity_on_lane(entity_array, lane, entity);
        hasBeenDeleted[lane] = 0;
        entity = nextTemp; // If we don't do that, our loop will break
    }
}

/*
    return 1 if the entity can move, 0 if not
*/
int CanMove(Entity* entity, Entity* target, Entity *entity_array){
    int canMove = 1;
    int worldUnitUntilYouCantMove = 50;
    Entity *temp;

    if( ( (target == NULL) || ( entity->position - ( entity->movement_speed/REFRESH_RATE) >= target->position) ) == 0){
        canMove = 0;
    }

    for(temp = entity_array; temp != NULL; temp = temp->next){
        if(temp == entity){
            continue;
        }
        if( temp->position < entity->position && temp->position >= entity->position - worldUnitUntilYouCantMove){
            canMove = 0;
            break;
        }
    }

    return canMove;
}

/*
    Go through every entity of the entity_array, apply common update and attack if in range.
*/
int entityUpdate(Entity** entity_array, Entity** entity, Entity** ennemy_array, int lane, Cannon cannon_array, int **hasBeenDeleted, Player *player)
{
    int gameEnded = 0;
    int cannonActivated = 0;
    Entity* target = NULL;
    for(;*entity!=NULL && cannonActivated == 0;){
        // common update
        if((*entity)->id > 0){
            commonUpdate(entity_array, lane, *entity, hasBeenDeleted[0]);
        } else if ((*entity)->id < 0){
            commonUpdate(entity_array, lane, *entity, hasBeenDeleted[1]);
        }
        
        //Factory generation
        if ((*entity)->id == 4 && (*entity)->hp > 0){
            factory_generation(*entity,player);
        }

        // research and move
        if( (*entity)->id > 0 ) {
            target = human_search_alien(*entity, ennemy_array[lane]);
        } else {
            target = alien_search_human(*entity, ennemy_array[lane]);

            // move
            if( (CanMove(*entity, target, entity_array[lane]) == 1) )
            {
                move(*entity);

                // Use the cannon
            } 
            if((*entity)->position <= -50 ) {
                cannonActivated = activate_cannon(cannon_array, lane, entity_array);
                if(cannonActivated == 2){
                    gameEnded = 1;
                }
            }
        }
        
        //attack
        if(target != NULL){
            attack(*entity, target);
        }

        (*entity)=(*entity)->next;  // Make the loop reach his condition
    }
    return gameEnded;
}


int update (Entity ** human_array, Entity ** alien_array, Player *human_player, Player *alien_player, Cannon cannon_array, int **hasBeenDeleted, clock_t startingTime, clock_t currentTime)
{
    int game_ended = 0;
    int scoreIncrement = 0;
    Entity* humanTemp=NULL;
    Entity* alienTemp=NULL;

    human_player->golds += (human_player->gold_per_second/REFRESH_RATE);
    alien_player->golds += (alien_player->gold_per_second/REFRESH_RATE);

    currentTime = clock();
    if(currentTime > startingTime + 1000.0){
        startingTime = currentTime;
        human_player->score += 2;
    }
    
    for (int lane = 0; lane <LANE; lane++){

        humanTemp=*(human_array+lane);
        alienTemp=*(alien_array+lane);
        entityUpdate(human_array, &humanTemp, alien_array, lane, cannon_array, hasBeenDeleted, human_player);
        game_ended = entityUpdate(alien_array, &alienTemp, human_array, lane, cannon_array, hasBeenDeleted, alien_player);
        if (game_ended == 1){
            return game_ended;
        }
    }    
    return game_ended;
}