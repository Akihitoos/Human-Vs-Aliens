/*
    Contains all the function needed to render the game in SDL
*/

#ifndef RENDERSDL_H
#define RENDERSDL_H

#include <SDL.h>

typedef struct RenderArray{
    SDL_Renderer *renderer;
    SDL_Texture **textureArray;
    SDL_Rect *rectArray;
}RenderArray;

#endif