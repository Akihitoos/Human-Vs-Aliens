/*
    Contains all the main function needed to render the game in SDL
*/

#ifndef GAME_RENDER_H
#define GAME_RENDER_H

#include "GameRenderBasics.h"
#include "update.h"

// First and last function

int GameRender_Init(SDL_Window **window, GameRender *gameRender, int gameMode);

void GameRender_FreeEverything(SDL_Window **window, GameRender *gameRender);

// Function of the game loop

void GameRender_UpdateGameRender(GameRender gameRender, Entity **humanArrayEntity, Entity **alienArrayEntity,
                                 Mower mowerArray, Shop *humanShop, Shop *alienShop);

void GameRender_UpdateRender(GameRender gameRender);

// Debugging function

void GameRender_Test();

#endif