#ifndef PLAYER_H
#define PLAYER_H

//Defines a Joueur struct
typedef struct Player
{
    int team; /* -1 if alien    0 if bot    1 if human */
    int score;
    double golds;
    double gold_per_second;
}Player;


//Initialize human player
Player* init_human_player();
Player* init_alien_player(int gamemode);

//Free player memory
void free_player(Player **player);


/* Files interaction functions */

#endif