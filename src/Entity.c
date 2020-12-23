#include "Entity.h"

// Function returning a Human ranged
Entity *create_human_ranged(int positionX, int lane){
    Entity *new = NULL;
    new = (Entity *)malloc(sizeof(Entity));
    if(new != NULL){
        new->id = 2;
        new->hp = 600;
        new->damage = 90;         
        new->range = 350;
        new->income = 0;
        new->movement_speed = 0;
        new->position = positionX;
        new->lane = lane;
        new->next = NULL;
    } else {
        fprintf(stderr, "Allocation error in create_ranged()");
    }
    return new;
}

// Function returning a Human tank
Entity *create_human_tank(int positionX, int lane){
    Entity *new = NULL;
    new = (Entity *)malloc(sizeof(Entity));
    if(new != NULL){
        new->id = 3;
        new->hp = 2000;
        new->damage = 30;           
        new->range = 50;
        new->income = 0;
        new->movement_speed = 0;
        new->position = positionX;
        new->lane = lane;
        new->next = NULL;
    } else {
        fprintf(stderr, "Allocation error in create_tank()");
    }
    return new;
}

// Function returning a Human melee
Entity *create_human_melee(int positionX, int lane){
    Entity *new = NULL;
    new = (Entity *)malloc(sizeof(Entity));
    if(new != NULL){
        new->id = 1;
        new->hp = 1100;
        new->damage = 140;
        new->range = 50;
        new->income = 0;
        new->movement_speed = 0;
        new->position = positionX;
        new->lane = lane;
        new->next = NULL;
    } else {
        fprintf(stderr, "Allocation error in create_melee()");
    }
    return new;
}

// Function returning an Usine (a special type of Human)
Entity *create_human_factory(int positionX, int lane){
    Entity *new = NULL;
    new = (Entity *)malloc(sizeof(Entity));
    if(new != NULL){
        new->id = 4;
        new->hp = 700;
        new->damage = 0;
        new->range = 0;
        new->income = 15;
        new->movement_speed = 0;
        new->position = positionX;
        new->lane = lane;
        new->next = NULL;
    } else {
        fprintf(stderr, "Allocation error in create_melee()");
    }
    return new;
}

// Function returning a range alien
Entity* create_alien_range(int lane){     
    Entity *new = (Entity*)malloc(sizeof(Entity));
    if (new != NULL){
        new->id = -2;
        new->hp = 450;
        new->damage = 80;
        new->range = 350;
        new->movement_speed = 90;
        new->income = 0;
        new->position = 1000;
        new->lane = lane;
        new->next = NULL;
    }
    else
    {
        fprintf(stderr,"Malloc erroc");
    }
    
    return new;
}

// Function returning a melee alien
Entity* create_alien_melee(int lane){     
    Entity *new = (Entity*)malloc(sizeof(Entity));
    if ( new != NULL){
        new->id = -1;
        new->hp = 900;
        new->damage = 110;
        new->range = 50;
        new->movement_speed = 120;
        new->income = 0;
        new->position = 1000;
        new->lane = lane;
        new->next = NULL;
    }
    else
    {
        fprintf(stderr,"Malloc erroc");
    }
    return new;
}

// Function returning a tank alien
Entity* create_alien_tank(int lane){      
    Entity *new = (Entity*)malloc(sizeof(Entity));
    if ( new != NULL){
        new->id = -3;
        new->hp = 2100;
        new->damage = 80;
        new->range = 50;
        new->movement_speed = 70;
        new->income = 0;
        new->position = 1000;
        new->lane = lane;
        new->next = NULL;
    }
    else
    {
        fprintf(stderr,"Malloc erroc");
    }
    return new;
}