/*
    Contains all the function needed to render the game in SDL
*/

#ifndef RENDERSDL_H
#define RENDERSDL_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "interaction.h" // Get the constant LANE

    //Below are all the define needed

// All the img are in BMP
// The number is the id
#define PATH_TO_HUMAN_1
#define PATH_TO_HUMAN_2
#define PATH_TO_HUMAN_3
#define PATH_TO_HUMAN_4

// The real id is negative
#define PATH_TO_ALIEN_1
#define PATH_TO_ALIEN_2
#define PATH_TO_ALIEN_3

// It will show the lane, the box where the entity will be placed etc.
#define PATH_TO_BACKGROUND

// It will be a box where the entity choosable will appear
#define PATH_TO_SHOP_UI

// Path to the different cursor used in the game
#define PATH_TO_CURSOR_PLAYER_1
#define PATH_TO_CURSOR_PLAYER_2
#define PATH_TO_CURSOR_SHOP

    // Below are the struct

// Struct defining a set of Texture with their corresponding SDL_Rect
typedef struct renderCell{
    SDL_Texture **textureArray;      // array of texture
    SDL_Rect *srcArray;                   // array Source SDL_Rect (which is copied)
    SDL_Rect *dstArray;                   // array Destination SDL_Rect (where it's copied)
    int numberOfElements;
}renderCell;

// We will always work with pointer
typedef renderCell *RenderCell;

// Struct containing all the information needed to display the game
typedef struct gameRender{
    SDL_Renderer *renderer;
    RenderCell *humanArrayStruct;
    RenderCell mowerStruct;
    RenderCell *alienArrayStruct;
    RenderCell uiStruct;
} gameRender;

// We will always work with pointer
typedef gameRender *GameRender;

    // Function inside RenderSDL.c
    // Those are (hopefully) ready

void GameRender_SDL_Init();

void GameRender_GetDisplayMode(int *width, int *height);

int GameRender_CreateWindow(SDL_Window **window);

// Need to rework these
int GameRender_InitRenderCell(RenderCell *renderCell);

int GameRender_InitGameRender(GameRender *gameRender, SDL_Window *window);

void GameRender_FreeRenderCell(RenderCell *renderCell);

void GameRender_FreeGameRender(GameRender *gameRender);


    // Function under work

int GameRender_Init(SDL_Window **window, GameRender *gameRender);

void GameRender_FreeEverything(SDL_Window **window, GameRender *gameRender);

    // Debugging function

// Display everything we need to know for the RenderCell
void GameRender_DebugRenderCell(RenderCell renderCell);

// Simply display everything we need to know if the gameRender is correctly working
void GameRender_DebugGameRender(GameRender gameRender);

// Simply call function to see if they work
void GameRender_Test();



    // Function that aren't well thought yet

/*
    Whenever we add a new Entity on the board, we need to call this function.
    The id is the id of the Entity we will add, this function will then load that entity
    into the right RenderCell.
*/
void GameRender_addEntity();
/*
    !Not definitive! this would change the position of the SDL_Rect dst of the
    corresponding Entity, still need to work out the actual parameters.
    Normally, the humanArray and alienArray of the gameRenderer will correspond to
    the ones in the game logic (created in the interaction.c)
*/
void GameRender_updatePos();

// Will simply apply the changes made to renderArray
void GameRender_UpdateWindow(GameRender gameRender);

#endif