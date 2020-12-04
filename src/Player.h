#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include "interaction.h"
#include "mower.h"
#include "update.h"
#include "Entity.h"

//Defines a Joueur struct
typedef struct Player
{
    int team; /* -1 if alien    0 if bot    1 if human */
    int score;
    double golds;
    double gold_per_second;
}Player;

/* Files interaction functions */

#endif