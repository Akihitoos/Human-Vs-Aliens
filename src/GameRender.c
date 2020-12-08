#include "GameRender.h"

/*
    Return 0 on success or a negative error on failure.
    Create, allocate and load everything in order to initalise the game window, including the SDL
    gameMode : 0 = solo, 1 = multiplayer
*/
int GameRender_Init(SDL_Window **window, GameRender *gameRender, int gameMode)
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
        for (int i = 0; i < LANE; i++)
        {
            GameRender_AddEntity(*gameRender, 0, i, 0);
        }

        GameRender_AddEntityToRenderCell((*gameRender)->uiStruct, (*gameRender)->renderer, PATH_TO_PLAYGROUND, 0, 0, 1.2, 1);
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
                                 Mower mowerArray, Shop *humanShop, Shop *alienShop)
{
    for (int i = 0; i < LANE; i++)
    {
        GameRender_UpdateRcEntity(gameRender, &(gameRender->humanArrayStruct[i]), humanArrayEntity[i]);
        GameRender_UpdateRcEntity(gameRender, &(gameRender->alienArrayStruct[i]), alienArrayEntity[i]);

        //Update mowerStruct
        if (mowerArray[i] == 0 && gameRender->mowerStruct[i].texture != NULL)
        {
            SDL_DestroyTexture(gameRender->mowerStruct[i].texture);
            gameRender->mowerStruct[i].texture = NULL;
            GameRender_FreeAllRenderCell(&(gameRender->alienArrayStruct[i]));
        }
    }

    // ! Update the position of the cursor / Waiting for that part to be finished !
}

/*
    Copy everything inside the gameRender to the renderer
*/
void GameRender_UpdateRender(GameRender gameRender)
{
    // Update the UI
    for (RenderCell pointer = gameRender->uiStruct; pointer != NULL && pointer->texture != NULL; pointer = pointer->next)
    {
        SDL_RenderCopy(gameRender->renderer, pointer->texture, NULL, pointer->dst);
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
    for (RenderCell pointer = gameRender->mowerStruct; pointer != NULL && pointer->texture != NULL; pointer = pointer->next)
    {
        SDL_RenderCopy(gameRender->renderer, pointer->texture, NULL, pointer->dst);
    }

    SDL_RenderPresent(gameRender->renderer);
}

/*
    A function to test the others
*/
void GameRender_Test()
{
    GameRender gameRender = NULL;
    SDL_Window *windowMain = NULL;
    int width = 0, height = 0;

    Entity **human_array = NULL;
    Entity **alien_array = NULL;
    Mower mower_array = NULL;

    human_array = init_entity_array();
    alien_array = init_entity_array();
    mower_array = init_mower_tab();

    add_entity(alien_array, -1, 0, 0);
    add_entity(human_array, 1, 0, 100);

    GameRender_Init(&windowMain, &gameRender, 0);

    for (int i = 0; i < 120; i++)
    {

        update(human_array, alien_array, mower_array);
        GameRender_UpdateGameRender(gameRender, human_array, alien_array, mower_array, NULL, NULL);
        GameRender_UpdateRender(gameRender);

        SDL_Delay(100);
    }

    free_array(&human_array, &alien_array);
    free_mower(&mower_array);
    GameRender_FreeEverything(&windowMain, &gameRender);
}
