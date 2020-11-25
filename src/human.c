/*
File dealing with the Human faction. It provides :
    - Different function creating different type of Human
    - Different function managing them

    (The struct Human is defined in the human.h)

first version (unbalanced)
*/

#include "human.h"

// Function returning a Human ranged
Human *create_ranged(int positionX, int lane){
    Human *new = NULL;
    new = (Human *)malloc(sizeof(Human));
    if(new != NULL){
        new->hp = 300;
        new->damage = 70;         // DPS : 84
        new->range = 250;
        new->revenus = 0.;
        new->attack_speed = 1.2;
        new->position = positionX;
        new->lane = lane;
    } else {
        fprintf(stderr, "Allocation error in create_ranged()");
    }
    return new;
}

// Function returning a Human tank
Human *create_tank(int positionX, int lane){
    Human *new = NULL;
    new = (Human *)malloc(sizeof(Human));
    if(new != NULL){
        new->hp = 1000;
        new->damage = 30;            // DPS : 36
        new->range = 30;
        new->revenus = 0.;
        new->attack_speed = 0.8;
        new->position = positionX;
        new->lane = lane;
    } else {
        fprintf(stderr, "Allocation error in create_tank()");
    }
    return new;
}

// Function returning a Human melee
Human *create_melee(int positionX, int lane){
    Human *new = NULL;
    new = (Human *)malloc(sizeof(Human));
    if(new != NULL){
        new->hp = 600;
        new->damage = 60;            // DPS : 60
        new->range = 30;
        new->revenus = 0.;
        new->attack_speed = 1;
        new->position = positionX;
        new->lane = lane;
    } else {
        fprintf(stderr, "Allocation error in create_melee()");
    }
    return new;
}

// Function returning an Usine (a special type of Human)
Human *create_factory(int positionX, int lane){
    Human *new = NULL;
    new = (Human *)malloc(sizeof(Human));
    if(new != NULL){
        new->hp = 450;
        new->damage = 0;
        new->range = 0;
        new->revenus = 10;
        new->attack_speed = 0;
        new->position = positionX;
        new->lane = lane;
    } else {
        fprintf(stderr, "Allocation error in create_melee()");
    }
    return new;
}

//deallocate the memory for the human given in parameters
void free_human(Human *human){
    free(human);
}