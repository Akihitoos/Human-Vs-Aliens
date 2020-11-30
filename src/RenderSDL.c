#include "RenderSDL.h"

//Call the SDL_Init function and exit if it fails
void GameRender_SDL_Init()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_Log("Error SDL_Init %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

/*
    Let the user choose a display mode, by displaying some possibility, and return
    the width and height through parameters. This is done manually.
*/
void GameRender_GetDisplayMode(int *width, int *height)
{
    int choice = 0;
    do{
        fprintf(stdout, "Please choose a resolution :\n");
        fprintf(stdout, "1 : 640 x 480\n");
        fprintf(stdout, "2 : 960 x 720\n");
        fprintf(stdout, "3 : 1024 x 576\n");
        fprintf(stdout, "4 : 1280 x 720\n");
        fprintf(stdout, "5 : 1600 x 900\n");
        fprintf(stdout, "6 : 1920 x 1080\n");
        fscanf(stdin, "%d", &choice);
        switch(choice){
            case 1:
                *width = 640;
                *height = 480;
                break;
            case 2:
                *width = 960;
                *height = 720;
                break;
            case 3:
                *width = 1024;
                *height = 576;
                break;
            case 4:
                *width = 1280;
                *height = 720;
                break;
            case 5:
                *width = 1600;
                *height = 900;
                break;
            case 6:
                *width = 1920;
                *height = 1080;
                break;
            default:
                break;
        }
    } while(choice < 1);
}

//Return 0 on success or a negative error on failure.
//Create a window by asking the user the resolution he wants.
int GameRender_CreateWindow(SDL_Window **window)
{
    int width = 0, height = 0, error = 0;;
    GameRender_GetDisplayMode(&width, &height);
    *window = SDL_CreateWindow("Human vs Aliens", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_ALLOW_HIGHDPI);
    if(*window == NULL){
        error = -1;
    }
    return error;
}

/*
    Return 0 on success or a negative error on failure.
    Allocate every RenderCell.
*/
int GameRender_InitRenderCell(RenderCell *renderCell)
{
    int error = 0;

    (*renderCell) = (RenderCell)malloc(sizeof(RenderCell));
    if((*renderCell) != NULL){
        (*renderCell)->textureArray = (SDL_Texture **)malloc(sizeof(SDL_Texture *));
        (*renderCell)->textureArray[0] = NULL;
        (*renderCell)->srcArray = (SDL_Rect *)malloc(sizeof(SDL_Rect));
        (*renderCell)->dstArray = (SDL_Rect *)malloc(sizeof(SDL_Rect));
        (*renderCell)->numberOfElements = 0;
    }

    if((*renderCell) == NULL || (*renderCell)->textureArray == NULL || (*renderCell)->srcArray == NULL || (*renderCell)->dstArray == NULL){
        fprintf(stderr,"Allocation error in GameRender_InitRenderCell()\n");
        error = -1;
    }  
    return error;
}

/*
    Return 0 on success or a negative error on failure.
    Allocate the struct gameRender.
*/
int GameRender_InitGameRender(GameRender *gameRender, SDL_Window *window)
{
    int error = 0;
    *gameRender = (GameRender)malloc(sizeof(GameRender));
    if(*gameRender != NULL){
        (*gameRender)->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        error = GameRender_InitRenderCell( &((*gameRender)->humanStruct) );
        error = GameRender_InitRenderCell( &((*gameRender)->alienStruct) );
        error = GameRender_InitRenderCell( &((*gameRender)->uiStruct) );
    }
    if( *gameRender == NULL || (*gameRender)->renderer == NULL || error == -1)
    {
        fprintf(stderr, "Error occured in GameRender_InitGameRender() : %s\n", SDL_GetError());
        error = -1;
    }
    return error;
}

void GameRender_FreeRenderCell(RenderCell *renderCell)
{
    for(int i = 0; i < (*renderCell)->numberOfElements ; i++)
    {
        if((*renderCell)->textureArray[i] != NULL){
            SDL_DestroyTexture((*renderCell)->textureArray[i]);
            (*renderCell)->textureArray[i] = NULL;
        }
    }
    free((*renderCell)->textureArray);
    (*renderCell)->textureArray = NULL;

    free((*renderCell)->srcArray);
    (*renderCell)->srcArray = NULL;

    free((*renderCell)->dstArray);
    (*renderCell)->dstArray = NULL;

    free(*renderCell);
    *renderCell = NULL;
        
}

void GameRender_FreeGameRender(GameRender *gameRender)
{
    GameRender_FreeRenderCell( &( (*gameRender)->humanStruct ) );
    GameRender_FreeRenderCell( &( (*gameRender)->alienStruct ) );
    GameRender_FreeRenderCell( &( (*gameRender)->uiStruct    ) );
    SDL_DestroyRenderer( (*gameRender)->renderer );

    (*gameRender)->renderer = NULL;
    free(*gameRender);
    *gameRender = NULL;
}






/*
    Return 0 on success or a negative error on failure.
    Create, allocate and load everything in order to initalise the game window, including the SDL
    The Window is currently 
*/
int GameRender_Init(SDL_Window **window, GameRender *gameRender)
{
    int error = 0;
    // initialise the SDL ?

    // Create the window

    // Allocate the gameRender

    return error;
}

/*
    Free every rendering component, including SDL
*/
void GameRender_FreeEverything(SDL_Window **window, GameRender *gameRender)
{
    // Free the gameRender

    // destroy the window
    
    // uninitialise the SDL ?
}

// Still need to check if the next two work.
void GameRender_DebugRenderCell(RenderCell renderCell)
{
    printf("    -> numberOfElement: %d\n", renderCell->numberOfElements);
    if(renderCell->textureArray != NULL){
        for(int i = 0; i < renderCell->numberOfElements ; i++ )
        {
            printf("    -> textureArray[%d] : %p", i, renderCell->textureArray[i]);
        }
    } else {
        printf("    -> textureArray is NULL",renderCell->textureArray);
    }

    if(renderCell->srcArray != NULL){
        for(int i = 0; i < renderCell->numberOfElements ; i++ )
        {
            printf("    -> textureArray[%d] : %p", i, renderCell->srcArray[i]);
        }
    } else {
        printf("    -> srcArray is NULL",renderCell->srcArray);
    }

    if(renderCell->dstArray != NULL){
        for(int i = 0; i < renderCell->numberOfElements ; i++ )
        {
            printf("    -> textureArray[%d] : %p", i, renderCell->dstArray[i]);
        }
    } else {
        printf("    -> dstArray is NULL",renderCell->dstArray);
    }

}

void GameRender_DebugGameRender(GameRender gameRender)
{
    if(gameRender != NULL)
    {
        printf("gameRender allocated at %p\n", gameRender);

        if(gameRender->renderer != NULL)
        {
            printf("    gameRender->renderer allocated at %p\n", gameRender->renderer);
        } else {
            printf("    gameRender->renderer is NULL.\n");
        }

        if(gameRender->humanStruct != NULL){
            printf("    gameRender->humanStruct allocated at %p\n", gameRender->humanStruct);
            GameRender_DebugRenderCell(gameRender->humanStruct);
        } else {
            printf("    gameRender->humanStruct is NULL.\n");
        }

        if(gameRender->alienStruct != NULL){
            printf("    gameRender->alienStruct allocated at %p\n", gameRender->alienStruct);
            GameRender_DebugRenderCell(gameRender->alienStruct);
        } else {
            printf("    gameRender->alienStruct is NULL.\n");
        }

        if(gameRender->uiStruct != NULL){
            printf("    gameRender->uiStruct allocated at %p\n", gameRender->uiStruct);
            GameRender_DebugRenderCell(gameRender->uiStruct);
        } else {
            printf("    gameRender->uiStruct is NULL.\n");
        }

    } else {
        printf("gameRender is NULL.\n");
    }

}

void GameRender_Test()
{
    GameRender gameRender = NULL;
    SDL_Window *windowMain = NULL;

    GameRender_SDL_Init();
    GameRender_CreateWindow(&windowMain);

    GameRender_InitGameRender(&gameRender, windowMain);
    GameRender_DebugGameRender(gameRender);

    SDL_DestroyWindow(windowMain);
    SDL_Quit();
}