/*
    Contains all the function needed to render the game in SDL
*/

#ifndef RENDERSDL_H
#define RENDERSDL_H

#include <SDL.h>

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

    // Below are our struct

// Struct defining a set of Texture with their corresponding SDL_Rect
typedef struct RenderCell{
    SDL_Texture **textureArray;      // array of texture
    SDL_Rect *src;                   // array Source SDL_Rect (which is copied)
    SDL_Rect *dst;                   // array Destination SDL_Rect (where it's copied)
}RenderCell;

// Struct containing all the information needed to display the game
typedef struct GameRender{
    SDL_Renderer *renderer;
    RenderCell *humanArray;
    RenderCell *alienArray;
    RenderCell *uiArray;
} GameRender;

// Create, allocate and load everything in order to initalise the game window
void GameRender_Init(SDL_Window **window, GameRender *gameRender);

/*

    Whenever we add a new Entity on the board, we need to call this function.
    The id is the id of the Entity we will add, this function will then load that entity
    into the right RenderCell.

void GameRender_addEntity(int id, RenderArray *GameRender)

    !Not definitive! this would change the position of the SDL_Rect dst of the
    corresponding Entity, still need to work out the actual parameters.
    Normally, the humanArray and alienArray of the gameRenderer will correspond to
    the ones in the game logic (created in the interaction.c)
 
void GameRender_updatePos(int idInArray, int x, int y);

*/

// Will simply apply the changes made to renderArray
void GameRender_UpdateWindow(GameRender *gameRender);

// Free and destroy everything in order to finish the game
void GameRender_Free(SDL_Window **window, GameRender *gameRender);

#endif