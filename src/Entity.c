#include "Entity.h"

// Function returning a Human ranged
Entity *create_human_ranged(int positionX, int lane){
    Entity *new = NULL;
    new = (Entity *)malloc(sizeof(Entity));
    if(new != NULL){
        new->id = 2;
        new->hp = 300;
        new->damage = 70;         
        new->range = 250;
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
        new->hp = 1000;
        new->damage = 30;           
        new->range = 30;
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
        new->hp = 600;
        new->damage = 60;
        new->range = 30;
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
        new->hp = 450;
        new->damage = 0;
        new->range = 0;
        new->income = 10;
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
        new->hp = 300;
        new->damage = 70;
        new->range = 300;
        new->movement_speed = 100;
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
        new->movement_speed = 150;
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
        new->damage = 150;
        new->range = 50;
        new->movement_speed = 50;
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