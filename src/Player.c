#include "Player.h"

Player* init_human_player(){
    Player* human = (Player*)malloc(sizeof(Player));
    if (human == NULL){
        fprintf(stderr, "Malloc error");
        return NULL;
    }
    human->team = 1;
    human->score = 0;
    human->golds = 500;
    human->gold_per_second = 1;
    return human;
}

// gamemode = 1(easy), 2(medium), 3(hard) if singleplayer, 0 if multiplayer
Player* init_alien_player(int gamemode){
    Player* alien = (Player*)malloc(sizeof(Player));

    if(alien == NULL){
        fprintf(stderr, "Error in init_alien_player\n");
        return NULL;
    }
  
    if(gamemode == 1){
        alien->team = -1;
    } else {
        alien->team = 0;
    }
    
    alien->score = 0;
    alien->golds = 500;
    alien->gold_per_second = 1;
    return alien;
}

void free_player(Player **player)
{
    free(*player);
    *player = NULL;
}