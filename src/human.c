#include <stdio.h>

// Struct defining a Human
typedef struct human{
    int hp;
    int damage;
    int range;
    double revenus;
    int movement_speed;
    double attack_speed;
    int position;
    int lane;
} Human;

// Function creating a ranged Human
Human *create_ranged(int lane){
    Human *ranged = NULL;
    ranged = (Human *)malloc(sizeof(Human));
    if(ranged != NULL){
        ranged->hp = 300;
        ranged->damage = 70;
        ranged->movement_speed = 0;
        ranged->attack_speed = 1.2;
        ranged->position = 0;
        ranged->lane = lane;
    } else {
        fprintf(stderr, "Allocation error in ranged");
    }
    return ranged;
}
