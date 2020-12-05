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
#define PATH_TO_HUMAN_1 "src\\img\\Human_Melee.bmp"
#define PATH_TO_HUMAN_2 "src\\img\\Human_Range.bmp"
#define PATH_TO_HUMAN_3 "src\\img\\Human_Tank.bmp"
#define PATH_TO_HUMAN_4 "src\\img\\Human_Range.bmp"

// The real id is negative
#define PATH_TO_ALIEN_1 "src\\img\\Alien_Melee.bmp"
#define PATH_TO_ALIEN_2 "src\\img\\Alien_Range.bmp"
#define PATH_TO_ALIEN_3 "src\\img\\Alien_Tank.bmp"

// It will show the lane, the box where the entity will be placed etc.
#define PATH_TO_PLAYGROUND "src\\img\\Playground.bmp"

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
}RenderCell_Struct;

typedef RenderCell_Struct *RenderCell;

// Struct containing all the information needed to display the game
typedef struct gameRender{
    SDL_Renderer *renderer;
    RenderCell *humanArrayStruct;
    RenderCell *alienArrayStruct;
    RenderCell mowerStruct;
    RenderCell uiStruct;                // Need to be careful, and know which case is what
} GameRender_Struct;

typedef GameRender_Struct *GameRender;

    // Function inside RenderSDL.c
    // Those are (hopefully) ready

void GameRender_SDL_Init(Uint32 flags);

void GameRender_GetDisplayMode(int *width, int *height);

SDL_Window* GameRender_CreateWindow();

    // allocation function of the GameRender

RenderCell GameRender_InitRenderCell();

RenderCell* GameRender_InitArrayRenderCell();

GameRender GameRender_InitGameRender(SDL_Window* window);

    // free function of the GameRender

void GameRender_FreeRenderCell(RenderCell renderCell);

void GameRender_FreeArrayRenderCell(RenderCell* arrayRenderCell);

void GameRender_FreeGameRender(GameRender* gameRender);

    // Function under work

int GameRender_Init(SDL_Window **window, GameRender *gameRender);

void GameRender_FreeEverything(SDL_Window **window, GameRender *gameRender);

    // Debugging function 

// Simply call function to see if they work
void GameRender_Test();

    // Function that aren't well thought yet | Will maybe move to another c files

/*
    Whenever we add a new Entity on the board, we need to call this function.
    The id is the id of the Entity we will add, this function will then load that entity
    into the right RenderCell.
*/
//void GameRender_addEntity();
/*
    !Not definitive! this would change the position of the SDL_Rect dst of the
    corresponding Entity, still need to work out the actual parameters.
    Normally, the humanArray and alienArray of the gameRenderer will correspond to
    the ones in the game logic (created in the interaction.c)
*/
//void GameRender_updatePos();

// Will simply apply the changes made to renderArray
//void GameRender_UpdateWindow(GameRender gameRender);

#endif