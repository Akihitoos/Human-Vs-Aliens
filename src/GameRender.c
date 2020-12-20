#include "GameRender.h"

/*
    Return 0 on success or a negative error on failure.
    Create, allocate and load everything in order to initalise the game window, including the SDL
    gameMode : 0 = solo, 1 = multiplayer
*/
int GameRender_Init(SDL_Window **window, GameRender *gameRender, int gameMode, Shop *humanShop, Shop *alienShop)
{
    int error = 0, width = 0, height = 0;

    // initialise the SDL
    GameRender_InitSDL(SDL_INIT_VIDEO);

    // Create the window
    *window = GameRender_CreateWindow(&width, &height);

    // Allocate the gameRender
    *gameRender = GameRender_InitGameRender(*window, width, height);

    if (*window == NULL || *gameRender == NULL)
    {
        fprintf(stderr, "Error in GameRender_Init : %s\n", SDL_GetError());
        error = -1;
    }
    else
    {
        error = GameRender_PrepareGame(*gameRender, gameMode);
    }

    return error;
}

/*
    Free every rendering component, including SDL
*/
void GameRender_FreeEverything(SDL_Window **window, GameRender *gameRender)
{
    // Free the gameRender
    GameRender_FreeGameRender(gameRender);

    // destroy the window
    SDL_DestroyWindow(*window);
    *window = NULL;

    // uninitialise the SDL ?
    SDL_Quit();
}

/*
    Take the gameRender and update/modify/add/remove when it's needed 
*/
void GameRender_UpdateGameRender(GameRender gameRender, Entity **humanArrayEntity, Entity **alienArrayEntity,
                                 Mower mowerArray, Shop *humanShop, Shop *alienShop, int gameMode)
{
    // Update the entity array
    for (int i = 0; i < LANE; i++)
    {
        GameRender_UpdateRcEntity(gameRender, &(gameRender->humanArrayStruct[i]), humanArrayEntity[i]);
        GameRender_UpdateRcEntity(gameRender, &(gameRender->alienArrayStruct[i]), alienArrayEntity[i]);

        // Update mowerStruct
        RenderCell temp = GameRender_GetI_RC(gameRender->mowerStruct, i);

        if (mowerArray[i] == false && temp->texture != NULL)
        {
            SDL_DestroyTexture(temp->texture);
            temp->texture = NULL;
            printf("[RENDER] Mower texture destroyed : %d\n", i);

            GameRender_FreeAllRenderCell(&(gameRender->alienArrayStruct[i]));
            printf("[RENDER] AlienArrayStruct[%d] free\n", i);
        }
    }

    // Update the position of the cursor
    
    GameRender_UpdateCursor(gameRender, humanShop, alienShop, gameMode);

}

/*
    Copy everything inside the gameRender to the renderer
*/
void GameRender_UpdateRender(GameRender gameRender, int gameMode)
{ 
    // Update the backgroung and the shop
    RenderCell uiPointer = gameRender->uiStruct;
    int i = 0;
    switch(gameMode){
        case 0:
            for (i = 0; uiPointer != NULL && i < 2; uiPointer = uiPointer->next, i++){
                SDL_RenderCopy(gameRender->renderer, uiPointer->texture, NULL, uiPointer->dst);
            }
            break;
        case 1:
            for (i = 0; uiPointer != NULL && i < 3; uiPointer = uiPointer->next, i++){
                SDL_RenderCopy(gameRender->renderer, uiPointer->texture, NULL, uiPointer->dst);
            }
            break;
        default:
            fprintf(stderr, "Wrong gameMode\n");
            break;
    }
    
    // Update the Entity
    for (int i = 0; i < LANE; i++)
    {
        for (RenderCell pointer = gameRender->humanArrayStruct[i]; pointer != NULL && pointer->texture != NULL; pointer = pointer->next)
        {
            SDL_RenderCopy(gameRender->renderer, pointer->texture, NULL, pointer->dst);
        }
        for (RenderCell pointer = gameRender->alienArrayStruct[i]; pointer != NULL && pointer->texture != NULL; pointer = pointer->next)
        {
            SDL_RenderCopy(gameRender->renderer, pointer->texture, NULL, pointer->dst);
        }
    }

    // Update the Mower
    for (RenderCell pointer = gameRender->mowerStruct; pointer != NULL; pointer = pointer->next)
    {
        if(pointer->texture != NULL){
            SDL_RenderCopy(gameRender->renderer, pointer->texture, NULL, pointer->dst);
        }
    }

    //update the cursor
    
    switch(gameMode){
        case 0:
            for (; uiPointer != NULL; uiPointer = uiPointer->next){
                SDL_RenderCopy(gameRender->renderer, uiPointer->texture, NULL, uiPointer->dst);
            }
            break;
        case 1:
            for (; uiPointer != NULL; uiPointer = uiPointer->next){
                SDL_RenderCopy(gameRender->renderer, uiPointer->texture, NULL, uiPointer->dst);
            }
            break;
        default:
            fprintf(stderr, "Wrong gameMode\n");
            break;
    }
    
    SDL_SetRenderDrawColor(gameRender->renderer, 255, 255, 255, 255);
    SDL_RenderPresent(gameRender->renderer);
    SDL_RenderClear(gameRender->renderer);
}

void EventHandler(int *moveHuman, int *moveAlien){
    SDL_Event movementEvent;
    while(SDL_PollEvent(&movementEvent)){
        if(movementEvent.type == SDL_KEYDOWN){
            switch(movementEvent.key.keysym.sym){
                case SDLK_q:
                    *moveHuman = -1;
                    break;
                case SDLK_LEFT:
                    *moveAlien = -1;
                    break;
                case SDLK_d:
                    *moveHuman = 1;
                    break;
                case SDLK_RIGHT:
                    *moveAlien = 1;
                    break;
                case SDLK_z:
                    *moveHuman = 2;
                    break;
                case SDLK_UP:
                    *moveAlien = 2;
                    break;
                case SDLK_s:
                    *moveHuman = -2;
                    break;
                case SDLK_DOWN:
                    *moveAlien = -2;
                    break;
                case SDLK_a:
                    *moveHuman = 3;
                    break;
                case SDLK_e:
                    *moveHuman = -3;
                    break;
                case SDLK_SPACE:
                    break;
            }
        }
    }
}

/*
    A function to test the others
*/
void GameRender_Test()
{
    GameRender gameRender = NULL;
    SDL_Window *windowMain = NULL;
    int width = 0, height = 0, gameMode = 0;

    Entity **human_array = NULL;
    Entity **alien_array = NULL;
    Mower mower_array = NULL;

    Shop *humanShop = NULL;
    Shop *alienShop = NULL;

    human_array = init_entity_array();
    alien_array = init_entity_array();
    mower_array = init_mower_tab();
    humanShop = init_shop_human();
    alienShop = init_shop_alien();

    add_entity(alien_array, -1, 0, 0);
    add_entity(alien_array, -1, 0, 0);
    add_entity(alien_array, -1, 0, 0);
    add_entity(alien_array, -1, 0, 0);
    add_entity(alien_array, -1, 1, 0);
    add_entity(alien_array, -1, 2, 0);
    add_entity(alien_array, -1, 4, 0);
    add_entity(human_array, 1, 0, 200);
    add_entity(human_array, 1, 1, 200);
    add_entity(human_array, 1, 2, 200);
    add_entity(human_array, 1, 4, 200);
    
    GameRender_Init(&windowMain, &gameRender, gameMode, humanShop, alienShop);

    for (int i = 0; i < 300; i++)
    {
        update(human_array, alien_array, mower_array);
        GameRender_UpdateGameRender(gameRender, human_array, alien_array, mower_array, humanShop, alienShop, gameMode);
        GameRender_UpdateRender(gameRender, gameMode);

        SDL_Delay(100);
    }

    free_array(&human_array, &alien_array);
    free_mower(&mower_array);
    GameRender_FreeEverything(&windowMain, &gameRender);
    printf("Finis\n");
}