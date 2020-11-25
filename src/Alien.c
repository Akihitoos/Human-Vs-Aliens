#include "Alien.h"

typedef struct Alien    //Structure contenant les stats des aliens.
{
    int hp;
    int damage;
    int range;
    int movement_speed;
    double attack_speed;
    int position;
    int lane;
}Alien;

Alien* create_range(int lane){     // Retourne un nouvel alien "range" avec ses statistiques.
    Alien *new = (Alien*)malloc(sizeof(Alien));
    if ( new != NULL){
        new->hp = 300;
        new->damage = 70;
        new->range = 300;
        new->movement_speed = 100;
        new->attack_speed = 1.2;
        new->position = 1000;
        new->lane = lane;
    }
    else
    {
        fprintf(stderr,"Malloc erroc");
    }
    
    return new;
}

Alien* create_melee(int lane){     // Retourne un nouvel alien "melee" avec ses statistiques
    Alien *new = (Alien*)malloc(sizeof(Alien));
    if ( new != NULL){
        new->hp = 900;
        new->damage = 110;
        new->range = 50;
        new->movement_speed = 150;
        new->attack_speed = 1.8;
        new->position = 1000;
        new->lane = lane;
    }
    else
    {
        fprintf(stderr,"Malloc erroc");
    }
    return new;
}

Alien* create_tank(int lane){      // Retourne un nouvel alien "tank" avec ses statistiques
    Alien *new = (Alien*)malloc(sizeof(Alien));
    if ( new != NULL){
        new->hp = 2100;
        new->damage = 150;
        new->range = 50;
        new->movement_speed = 50;
        new->attack_speed = 0.3;
        new->position = 1000;
        new->lane = lane;
    }
    else
    {
        fprintf(stderr,"Malloc erroc");
    }
    return new;
}

void move(Alien *alien){        /*Susceptible de changer*/  //Incrémente la position de l'alien de sa ms
    alien->position -= alien->movement_speed;
}

void upon_death(Alien *alien){    // Fonction qui s'éxecute si hp = 0, et libère la mémoire allouée
    if (alien->hp <= 0){
        /* Eventuelles actions */
        free(alien);
    }
}
