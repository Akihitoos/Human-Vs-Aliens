#include "GameRender.h"

/*
    Return 0 on success or a negative error on failure.
    Create, allocate and load everything in order to initalise the game window, including the SDL 
    and his extension for text TTF
    gameMode : 0 = solo, 1 = multiplayer
*/
int GameRender_Init(GameRender *gameRender, int gameMode)
{
    int error = 0, width = 0, height = 0;

    GameRender_InitSDL(SDL_INIT_VIDEO);

    *gameRender = GameRender_InitGameRender();

    if ((*gameRender)->windowMain == NULL || *gameRender == NULL)
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
void GameRender_FreeEverything(GameRender *gameRender)
{
    GameRender_FreeGameRender(gameRender);

    TTF_Quit();
    SDL_Quit();
}

/*
    Take the gameRender and update/modify/add/remove when it's needed 
*/
void GameRender_UpdateGameRender(GameRender gameRender, Entity **humanArrayEntity, Entity **alienArrayEntity,
                                 Player* humanPlayer, Player* alienPlayer, Cannon cannonArray, Shop *humanShop, 
                                 Shop *alienShop, int gameMode)
{
    // Update the entity array
    for (int i = 0; i < LANE; i++)
    {
        GameRender_UpdateRcEntity(gameRender, &(gameRender->humanArrayStruct[i]), humanArrayEntity[i], &(gameRender->hasBeenDeleted[0][i]));
        GameRender_UpdateRcEntity(gameRender, &(gameRender->alienArrayStruct[i]), alienArrayEntity[i], &(gameRender->hasBeenDeleted[1][i]));

        // Update cannonStruct
        RenderCell temp = GameRender_GetI_RC(gameRender->cannonStruct, i);

        if (cannonArray[i] == false && temp->texture != NULL)
        {
            SDL_DestroyTexture(temp->texture);
            temp->texture = NULL;
            printf("[RENDER] Cannon texture destroyed : %d\n", i);

            GameRender_FreeAllRenderCell(&(gameRender->alienArrayStruct[i]));
            printf("[RENDER] AlienArrayStruct[%d] free\n", i);
        }
    }

    // Update the position of the cursor
    
    GameRender_UpdateUi(gameRender, humanShop, alienShop, humanPlayer, alienPlayer, gameMode);
}

/*
    Copy everything inside the gameRender to the renderer
*/
void GameRender_UpdateRender(GameRender gameRender, int gameMode)
{ 
    // Update the backgroung and the shop
    RenderCell uiPointer = gameRender->uiStruct;
    int i = 0;
    if(gameMode > 0 && gameMode <= 3){
        for (i = 0; uiPointer != NULL && i < 2; uiPointer = uiPointer->next, i++){
            SDL_RenderCopy(gameRender->renderer, uiPointer->texture, NULL, uiPointer->dst);
        }
    } else if (gameMode == 0) {
        for (i = 0; uiPointer != NULL && i < 3; uiPointer = uiPointer->next, i++){
            SDL_RenderCopy(gameRender->renderer, uiPointer->texture, NULL, uiPointer->dst);
        }
    } else {   
        fprintf(stderr, "Wrong gameMode\n");
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

    // Update the Cannon
    for (RenderCell pointer = gameRender->cannonStruct; pointer != NULL; pointer = pointer->next)
    {
        if(pointer->texture != NULL){
            SDL_RenderCopy(gameRender->renderer, pointer->texture, NULL, pointer->dst);
        }
    }

    //update the cursor
    
    if( gameMode > 0 && gameMode <= 3 ){
        for (; uiPointer != NULL; uiPointer = uiPointer->next){
            SDL_RenderCopy(gameRender->renderer, uiPointer->texture, NULL, uiPointer->dst);
        }
    } else if ( gameMode == 0) {
        for (; uiPointer != NULL; uiPointer = uiPointer->next){
            SDL_RenderCopy(gameRender->renderer, uiPointer->texture, NULL, uiPointer->dst);
        }
    } else {
        fprintf(stderr, "Wrong gameMode\n");
    }
    
    SDL_RenderPresent(gameRender->renderer);
    SDL_RenderClear(gameRender->renderer);
}

void EventHandler(Entity **humanArray, Entity **alienArray, Shop *humanShop, Shop *alienShop, Player* alienPlayer, Player* humanPlayer, int gameMode){
    SDL_Event event;
    int moveHuman = 0, moveAlien = 0;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_KEYDOWN){
            switch(event.key.keysym.sym){
                case SDLK_a:
                    moveHuman = -1;
                    break;
                case SDLK_LEFT:
                    moveAlien = -1;
                    break;
                case SDLK_e:
                    moveHuman = 1;
                    break;
                case SDLK_RIGHT:
                    moveAlien = 1;
                    break;
                case SDLK_s:
                    moveHuman = 2;
                    break;
                case SDLK_DOWN:
                    moveAlien = 2;
                    break;
                case SDLK_z:
                    moveHuman = -2;
                    break;
                case SDLK_UP:
                    moveAlien = -2;
                    break;
                case SDLK_q:
                    moveHuman = -3;
                    break;
                case SDLK_d:
                    moveHuman = +3;
                    break;
                case SDLK_SPACE:
                    if(can_buy(humanShop, humanPlayer) && can_place(humanShop->cursor_position, humanArray[humanShop->cursor_lane])){
                        add_entity(humanArray, humanShop->id[humanShop->cursor_shop - 1], humanShop->cursor_lane, humanShop->cursor_position);
                        humanPlayer->golds -= (double)humanShop->tab_cost[humanShop->cursor_shop - 1];
                    }
                    break;
                case SDLK_RETURN:
                    if(gameMode == 0){
                        if (can_buy(alienShop, alienPlayer)){
                            add_entity(alienArray, alienShop->id[ (- alienShop->cursor_shop) -1], alienShop->cursor_lane, alienShop->cursor_position);
                            alienPlayer->golds -= (double)alienShop->tab_cost[(- alienShop->cursor_shop) -1];
                        }
                    }
                    break; 
                default:
                    break;
            }   
            if (moveAlien != 0){
                shop_navigate(alienShop, moveAlien);
            } else if (moveHuman != 0){
                shop_navigate(humanShop, moveHuman);
            }
        }
    }
}
