#include "RenderSDL.h"

//Call the SDL_Init function and exit if it fails
void GameRender_SDL_Init(Uint32 flags)
{
    if(SDL_Init(flags) != 0){
        SDL_Log("Error SDL_Init %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

/*
    Let the user choose a display mode, by displaying some possibility, and return
    the width and height through parameters. This is done manually
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

//Return 0 on success or a negative error on failure
//Create a window by asking the user the resolution he wants
SDL_Window *GameRender_CreateWindow()
{
    SDL_Window *window = NULL;
    int width = 0, height = 0, error = 0;;
    GameRender_GetDisplayMode(&width, &height);
    window = SDL_CreateWindow("Human vs Aliens", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_ALLOW_HIGHDPI);
    if(window == NULL){
        SDL_Log("Erreur in GameRender_CreateWindow() : %s \n", SDL_GetError());
    }
    return window;
}

/*
    Allocate a RenderCell* and return it
*/
RenderCell GameRender_InitRenderCell()
{
    RenderCell newCell = NULL;
    newCell = (RenderCell_Struct *)malloc(sizeof(RenderCell_Struct));
    if(newCell != NULL){
        newCell->textureArray = (SDL_Texture **)malloc(sizeof(SDL_Texture *));
        newCell->srcArray = (SDL_Rect *)malloc(sizeof(SDL_Rect));
        newCell->dstArray = (SDL_Rect *)malloc(sizeof(SDL_Rect));
        newCell->numberOfElements = 0;
    }

    if(newCell == NULL || newCell->textureArray == NULL || newCell->srcArray == NULL || newCell->dstArray == NULL){
        fprintf(stderr,"Error occured in GameRender_InitRenderCell() : %s\n", SDL_GetError());
    }  
    return newCell;
}

/*
    Allocate an array of RenderCell* and return it
*/
RenderCell *GameRender_InitArrayRenderCell()
{
    RenderCell *newCell = NULL;
    newCell = (RenderCell_Struct **)malloc(sizeof(RenderCell_Struct *) * LANE);
    if( newCell != NULL){
        for(int i = 0; i < LANE; i++){
            newCell[i] = GameRender_InitRenderCell();
        }
    } else {
        fprintf(stderr, "Error occured in GameRender_InitArrayRenderCell()\n");
    }
    return newCell;
}

/*
    Allocate a struct GameRender* and return it
*/
GameRender GameRender_InitGameRender(SDL_Window *window)
{
    GameRender gameRender = NULL;
    gameRender = (GameRender_Struct *)malloc(sizeof(GameRender_Struct));
    if(gameRender != NULL){
        gameRender->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        gameRender->humanArrayStruct = GameRender_InitArrayRenderCell();
        gameRender->alienArrayStruct = GameRender_InitArrayRenderCell();
        gameRender->mowerStruct = GameRender_InitRenderCell();
        gameRender->uiStruct = GameRender_InitRenderCell();
    }
    if( gameRender == NULL || gameRender->renderer == NULL)
    {
        fprintf(stderr, "Error occured in GameRender_InitGameRender() : %s\n", SDL_GetError());
    }
    return gameRender;
}


// Free a renderCell (doesn't replace the pointer by NULL)
void GameRender_FreeRenderCell(RenderCell renderCell)
{
    for (int i = 0; i < renderCell->numberOfElements; i++)
    {
        SDL_DestroyTexture(renderCell->textureArray[i]);
    }
    free(renderCell->textureArray);
    free(renderCell->srcArray);
    free(renderCell->dstArray);
    free(renderCell);
}

// Free an array of RenderCell (doesn't replace the pointer by NULL)
void GameRender_FreeArrayRenderCell(RenderCell *arrayRenderCell)
{
    for(int i = 0; i < LANE; i++){
        if (arrayRenderCell[i] != NULL) {
            GameRender_FreeRenderCell(arrayRenderCell[i]);
        }
    }

    free(arrayRenderCell);
}

// Free the whole GameRender (replace the pointer by NULL)
void GameRender_FreeGameRender(GameRender *gameRender)
{
    GameRender_FreeArrayRenderCell( (*gameRender)->humanArrayStruct );
    GameRender_FreeArrayRenderCell( (*gameRender)->alienArrayStruct );
    GameRender_FreeRenderCell( (*gameRender)->uiStruct    );
    GameRender_FreeRenderCell( (*gameRender)->mowerStruct );

    SDL_DestroyRenderer( (*gameRender)->renderer );
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

void GameRender_Test()
{
    GameRender gameRender = NULL;
    SDL_Window *windowMain = NULL;

    GameRender_SDL_Init(SDL_INIT_VIDEO);

    windowMain = GameRender_CreateWindow();

    gameRender = GameRender_InitGameRender(windowMain);

    SDL_Delay(5000);

    if (gameRender != NULL) {  
        GameRender_FreeGameRender(&gameRender);
    }
    
    SDL_DestroyWindow(windowMain);
    SDL_Quit();
}