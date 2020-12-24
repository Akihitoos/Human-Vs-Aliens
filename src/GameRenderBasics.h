/*
    Contains all the basic functions needed for GameRenderMain
*/

#ifndef GAME_RENDER_BASICS_H
#define GAME_RENDER_BASICS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "interaction.h" // Get the constant LANE
#include "Shop.h"

//Below are all the define needed

// All the entity are in BMP 400*400

#define SIZE_ENTITY 400

// The number is the id
//#define PATH_TO_HUMAN_1 "src\\img\\Human_Melee.bmp"
#define PATH_TO_HUMAN_1 "img\\Human_Melee.bmp"
#define PATH_TO_HUMAN_2 "img\\Human_Range.bmp"
#define PATH_TO_HUMAN_3 "img\\Human_Tank.bmp"
#define PATH_TO_HUMAN_4 "img\\Human_Factory.bmp"
#define PATH_TO_MOWER_0 "img\\Mower.bmp"

// The real id is negative
#define PATH_TO_ALIEN_1 "img\\Alien_Melee.bmp"
#define PATH_TO_ALIEN_2 "img\\Alien_Range.bmp"
#define PATH_TO_ALIEN_3 "img\\Alien_Tank.bmp"

#define PATH_TO_BACKGROUND "img\\Background.bmp"

// It will show the lane, the box where the entity will be placed etc.
#define PATH_TO_PLAYGROUND "img\\Playground.bmp"

// It will be a box where the entity choosable will appear
#define PATH_TO_HUMAN_SHOP "img\\Human_Shop.bmp"
#define PATH_TO_ALIEN_SHOP "img\\Alien_Shop.bmp"

// Path to the different cursor used in the game
#define PATH_TO_CURSOR_PLAYER_1 "img\\Cursor_Human_Player.bmp"
#define PATH_TO_CURSOR_PLAYER_2 "img\\Cursor_Alien_Player.bmp"
#define PATH_TO_CURSOR_SHOP "img\\Cursor_Shop.bmp"

#define PATH_TO_FONT "consola.ttf"


// Below are the struct

// Struct defining a set of Texture with their corresponding SDL_Rect

typedef struct renderCell
{
    SDL_Texture *texture;    // texture
    SDL_Rect *src;           // Source SDL_Rect (which is copied) ! Will maybe never be used, but could be for said improvement
    SDL_Rect *dst;           // Destination SDL_Rect (where it's copied)
    struct renderCell *next; // A pointer onto the next RenderCell (struct renderCell* == RenderCell_Struct* == RenderCell)
} RenderCell_Struct;

typedef RenderCell_Struct *RenderCell;

// Struct containing all the information needed to display the game

typedef struct gameRender
{
    SDL_Renderer *renderer;
    RenderCell *humanArrayStruct;
    RenderCell *alienArrayStruct;
    int **hasBeenDeleted; // used to synchronise the SDL update with the game itself
    RenderCell mowerStruct;
    RenderCell uiStruct; // Need to be careful, and know which case is what
    int screen_width;
    int screen_height;
    float ratio;
} GameRender_Struct;

typedef GameRender_Struct *GameRender;

// Function inside RenderSDL.c

void GameRender_InitSDL(Uint32 flags);

void GameRender_GetDisplayMode(int *width, int *height);

SDL_Window *GameRender_CreateWindow(int *width, int *height);

// allocation function of the GameRender

RenderCell GameRender_InitRenderCell();

RenderCell GameRender_CreateEmptyRenderCell();

RenderCell *GameRender_InitArrayRenderCell();

GameRender GameRender_InitGameRender(SDL_Window *window, int width, int height);

// free function of the GameRender

void GameRender_FreeAllRenderCell(RenderCell *renderCell);

void GameRender_FreeArrayRenderCell(RenderCell **arrayRenderCell);

void GameRender_FreeGameRender(GameRender *gameRender);

// chain manipulation function

int GameRender_AddRenderCell(RenderCell firstRC, RenderCell newRC);

void GameRender_DeleteRenderCell(RenderCell *firstRC, RenderCell *toDelete);

char *GameRender_GetPathFromId(int id);

int GameRender_AddElementToRenderCell(RenderCell renderCell, SDL_Renderer *renderer, char *path_to_element,
                                      int posX, int posY, float widthRatio, float heightRatio);

int GameRender_PrepareGame(GameRender gameRender, int gameMode);

int GameRender_AddEntity(GameRender gameRender, int idEntity, int lane, int posX);

void GameRender_MoveEntity(float screenRatio, RenderCell rcToMove, Entity *entity);

RenderCell GameRender_GetLastRC(GameRender gameRender, int id, int lane);

RenderCell GameRender_GetI_RC(RenderCell firstRC, int id);

void GameRender_UpdateRcEntity(GameRender gameRender, RenderCell *firstRC, Entity *firstEntity, int *hasBeenDeleted);

void GameRender_UpdateText(GameRender gameRender, RenderCell scoreCell, char *textToDisplay, SDL_Color color);

void GameRender_UpdateUi(GameRender gameRender, Shop *humanShop, Shop *alienShop, Player* humanPlayer, Player* alienPlayer, int gameMode);

// Debugging function

void GameRender_DisplayRenderCell(RenderCell rcToDisplay);

void GameRender_DisplayEverything(GameRender gameRender);



#endif