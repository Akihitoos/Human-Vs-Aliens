/*
    Contains all the main function needed to render the game in SDL
*/

#ifndef GAME_RENDER_H
#define GAME_RENDER_H

#include "GameRenderBasics.h"
#include "update.h"

// First and last function

int GameRender_Init(GameRender *gameRender, int gameMode);

void GameRender_FreeEverything(GameRender *gameRender);

// Function of the game loop

void GameRender_UpdateGameRender(GameRender gameRender, Entity **humanArrayEntity, Entity **alienArrayEntity,
                                 Player* humanPlayer, Player* alienPlayer, Cannon cannonArray, Shop *humanShop, 
                                 Shop *alienShop, int gameMode);

void GameRender_UpdateRender(GameRender gameRender, int gameMode);

void EventHandler(Entity **humanArray, Entity **alienArray, Shop *humanShop, Shop *alienShop, Player* alienPlayer, Player* humanPlayer, int gameMode);

#endif