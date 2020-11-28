#include "interaction.h"

// function which initialize a double array of entity
Entity ***init_entity_double_array(){
    Entity ***p = NULL; 
    p = (Entity ***)malloc(sizeof(Entity***) * LANE); // Initialise the pointer onto the array of each lane 

    if(p != NULL){

        // Initialise each array of Entity (per lane)
        for(int i = 0; i < LANE; i++){

            p[i] = (Entity **)malloc(sizeof(Entity**)); 
            if(p[i] == NULL){
                fprintf(stderr,"Allocation error in init_entity_double_array()\n");
            }
        }
    } else {
        fprintf(stderr,"Allocation error in init_entity_double_array()\n");
    }

    return p;
}

// Function returning a entity depending on his id
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


// Add an Entity to a Lane
Entity ***add_entity_to_lane(Entity **lane, Entity *new){

    // return the first Entity of the lane

}

// create an Entity (depending on the id) and add it to a double array of entity
void add_entity(Entity ***doubleArray, int id, int lane, int pos)
{
    Entity *p = NULL;
    p = create_entity_on_id(id, lane, pos);
    if(p!=NULL){
        
    }
}
