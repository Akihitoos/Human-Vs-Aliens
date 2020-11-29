#include "interaction.h"



// function which initialize and return a simple array of entity
Entity **init_entity_array(){
    Entity **p = NULL;
    p = (Entity**)malloc(sizeof(Entity**)*LANE); // Initialize the pointer onto the array of each lane 
    if (p != NULL){
        for (int i = 0; i<LANE;i++){
            *(p+i) = NULL;
        }
    }
    return p;
}

// Function returning an Entity depending on his id (the same as the one initialised in Entity.c)
Entity* create_entity_on_id(int id, int lane, int pos){
    Entity *new = NULL;
    switch(id){
        case 1:
            new = create_human_melee(pos, lane);
            break;
        case 2:
            new = create_human_ranged(pos, lane);
            break;
        case 3:
            new = create_human_tank(pos, lane);
            break;
        case 4:
            new = create_human_factory(pos, lane);
            break;
        case -1:
            new = create_alien_melee(lane);
            break;
        case -2:
            new = create_alien_range(lane);
            break;
        case -3:
            new = create_alien_tank(lane);
            break;
        default:
            new = NULL;
            break;
    }

    return new;
}


/*
    Add an Entity to a Lane.
    Entity *lane : This is a pointer onto the first element of the chain of Entity (which from the lane)
    Entity *new : This is the Entity to add in the chain
*/
void add_entity_to_lane(Entity *lane, Entity *new){
    Entity *temp = lane;
    if (temp == NULL){
        lane = new;
        return;
    }
    while (temp->next != NULL){
        temp = temp->next;
    }
    temp->next = new;
}

/* 
    Create an Entity (depending on the id) and add it to a chain list of entity
*/
void add_entity(Entity **simpleArray, int id, int lane, int pos)
{
    Entity *p = NULL;
    p = create_entity_on_id(id, lane, pos);
    if(p!=NULL){
        add_entity_to_lane(*(simpleArray+lane),p);      //input lanes from 0 to 4 

    }else{fprintf(stderr,"Malloc error");}
    
}

void delete_entity_on_lane(Entity **simpleArray,int lane, Entity *todelete)
{
    if (todelete == *(simpleArray+lane))
    {
        *(simpleArray+lane) = todelete->next;
        free(todelete);
    }
    else
    {
        Entity *temp = *(simpleArray+lane);
        while(temp->next != todelete)
        {
            temp = temp->next;
        }
        temp->next = temp->next->next;
        free(temp->next);
    }
}

//Free the content of a lane. The first occurence must be the first entity of the lane
void free_tab_content_recursive(Entity *entity){
    if (entity->next != NULL){
        free_tab_content_recursive(entity->next);
    }
    free(entity); 
}

void free_array(Entity ***Human, Entity ***Alien){
    for (int i = 0;i<LANE;i++){
    if ( *((*Human)+i) != NULL)
        {
            free_tab_content_recursive(*((*Human)+i));
        }
    if(*((*Alien)+i) != NULL)
        {
            free_tab_content_recursive(*((*Alien)+i));
        }
    }
    free(*Human);
    free(*Alien);
    *Human = NULL;
    *Alien = NULL;
}

Entity* alien_search_human (Entity * alien, Entity * tab_human)
{
    Entity *cible = NULL;
    Entity *temp = tab_human;
    while (temp != NULL)
    {
        if((alien->position - alien->range > temp->position) && (alien->position >= temp->position)
        && ((cible == NULL) || (cible->position < temp->position))){
            temp = cible;
        }
        temp = temp->next;
    }
    return cible;
}

Entity* human_search_alien (Entity * human, Entity * tab_alien)
{
    Entity *cible = NULL;
    Entity *temp = tab_alien;
    while (temp != NULL)
    {
        if((human->position + human->range > temp->position) && (human->position <= temp->position)
        && ((cible == NULL) || (cible->position > temp->position))){
            temp = cible;
        }
        temp = temp->next;
    }
    return cible;
}

void attack(Entity *attacker, Entity *attacked){
    attacked->hp -= attacker->damage/* /refresh_rate*/;
}

void factory_generation(Entity *factory/*, Joueur gain*/){
    /*Joueur->bank += (factory.revenus)/REFRESH_RATE;*/
}

void move(Entity *alien){        //Reduces alien position of its MS
    alien->position -= alien->movement_speed; // / refresh_rate
}

void debugEntityArray(Entity **array)
{
    //Affiche le pointeur du tableau
    printf("array pointer = %p\n", array);

    for(int i = 0; i < LANE; i++){
        if(array[i] != NULL){
            printf("array[%d], pointer = %p :\n", i, array[i]); // Affiche le premier element

            //On affiches toute les cases
            for(Entity *temp = array[i]; temp != NULL; temp = temp->next){
                printf("    Entity id = %d,pointer = %p :\n", i, array[i]->id, array[i]); //Affiche chaque element
            }
        } else {
            printf("array[%d] is NULL\n", i);
        }
    }
}

void testingInteraction()
{
    Entity **humanArray = NULL;
    Entity **alienArray = NULL;

    humanArray = init_entity_array();
    alienArray = init_entity_array();

    printf("humanArray : %p\n", humanArray);
    printf("alienArray : %p\n", alienArray);

    debugEntityArray(humanArray);

    // On doit passer par adresse si on veut free nos tableaux dans une fonction
    free_array(&humanArray, &alienArray);

    printf("humanArray : %p\n", humanArray);
    printf("alienArray : %p\n", alienArray);
}