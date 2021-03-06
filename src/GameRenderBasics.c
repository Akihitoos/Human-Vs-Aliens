#include "GameRenderBasics.h"

//Call the SDL_Init function and exit if it fails
void GameRender_InitSDL(Uint32 flags)
{
    if (SDL_Init(flags) != 0)
    {
        SDL_Log("Error SDL_Init %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if(TTF_Init() == -1){
        fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());
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
    do
    {
        fprintf(stdout, "Please choose a resolution :\n");
        fprintf(stdout, "1 : 640 x 360\n");
        fprintf(stdout, "2 : 960 x 540\n");
        fprintf(stdout, "3 : 1024 x 576\n");
        fprintf(stdout, "4 : 1280 x 720\n");
        fprintf(stdout, "5 : 1600 x 900\n");
        fprintf(stdout, "6 : 1920 x 1080\n");
        fscanf(stdin, "%d", &choice);
        switch (choice)
        {
        case 1:
            *width = 640;
            *height = 360;
            break;
        case 2:
            *width = 960;
            *height = 540;
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
    } while (choice < 1);

}

//Return a window by asking the user the resolution he wants, and return them via parameters
SDL_Window *GameRender_CreateWindow(int *width, int *height)
{
    SDL_Window *window = NULL;
    SDL_Surface *windowIcon = SDL_LoadBMP(PATH_TO_GAME_ICON);
    if(windowIcon == NULL){
        SDL_Log("Erreur in GameRender_CreateWindow() : %s \n", SDL_GetError());
    }
    GameRender_GetDisplayMode(width, height);
    window = SDL_CreateWindow("Human vs Aliens", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, *width, *height, SDL_WINDOW_ALLOW_HIGHDPI);
    if (window != NULL && windowIcon != NULL)
    {
        SDL_SetWindowIcon(window, windowIcon);
        SDL_FreeSurface(windowIcon);
    } else {
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
    if (newCell != NULL)
    {
        newCell->texture = NULL;
        newCell->src = (SDL_Rect *)malloc(sizeof(SDL_Rect));
        newCell->dst = (SDL_Rect *)malloc(sizeof(SDL_Rect));
        newCell->next = NULL;
    }

    if (newCell == NULL || newCell->src == NULL || newCell->dst == NULL)
    {
        fprintf(stderr, "Error occured in GameRender_InitRenderCell() : %s\n", SDL_GetError());
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
    if (newCell != NULL)
    {
        for (int i = 0; i < LANE; i++)
        {
            newCell[i] = GameRender_InitRenderCell();
        }
    }
    else
    {
        fprintf(stderr, "Error occured in GameRender_InitArrayRenderCell()\n");
    }
    return newCell;
}

/*
    Allocate a struct GameRender* and return it.
    Width and height correspond to the screen.
*/
GameRender GameRender_InitGameRender()
{
    GameRender gameRender = NULL;
    int width = -1,height = -1;
    gameRender = (GameRender_Struct *)malloc(sizeof(GameRender_Struct));
    if (gameRender != NULL)
    {
        gameRender->windowMain = GameRender_CreateWindow(&width, &height);
        if(gameRender->windowMain != NULL){
            gameRender->renderer = SDL_CreateRenderer(gameRender->windowMain, -1, SDL_RENDERER_ACCELERATED);
        }
        gameRender->humanArrayStruct = GameRender_InitArrayRenderCell();
        gameRender->alienArrayStruct = GameRender_InitArrayRenderCell();
        gameRender->hasBeenDeleted = (int **)malloc(sizeof(int*) * 2);
        if(gameRender->hasBeenDeleted != NULL){
            for(int i = 0; i < 2; i++){
                gameRender->hasBeenDeleted[i] = (int *)malloc(sizeof(int) * LANE);
                for(int j = 0; j < LANE; j++){
                    gameRender->hasBeenDeleted[i][j] = 0;
                }
            }
        }
        gameRender->cannonStruct = GameRender_InitRenderCell();
        gameRender->uiStruct = GameRender_InitRenderCell();
        gameRender->screen_width = width;
        gameRender->screen_height = height;
        gameRender->ratio = (float)width /(float)1920;
    }
    if (gameRender == NULL || gameRender->renderer == NULL || gameRender->hasBeenDeleted == NULL 
        || gameRender->hasBeenDeleted[0] == NULL || gameRender->hasBeenDeleted[1] == NULL)
    {
        fprintf(stderr, "Error occured in GameRender_InitGameRender() : %s\n", SDL_GetError());
    }
    return gameRender;
}

// Free every renderCell (need the first one in parameters)
void GameRender_FreeAllRenderCell(RenderCell *firstRC)
{
    RenderCell toDelete = *firstRC; // We delete this one
    RenderCell pointer = *firstRC;  // We search the next one to delete
    for (; pointer != NULL; toDelete = pointer)
    {
        pointer = pointer->next;

        SDL_DestroyTexture(toDelete->texture);
        free(toDelete->src);
        free(toDelete->dst);
        free(toDelete);
    }
    *firstRC = NULL;
}

// Free an array of RenderCell (replace the pointer by NULL)
void GameRender_FreeArrayRenderCell(RenderCell **arrayRenderCell)
{
    for (int i = 0; i < LANE; i++)
    {
        if ((*arrayRenderCell)[i] != NULL)
        {
            GameRender_FreeAllRenderCell(&((*arrayRenderCell)[i]));
        }
    }
    free(*arrayRenderCell);
    *arrayRenderCell = NULL;
}

// Free the whole GameRender (replace the pointer by NULL)
void GameRender_FreeGameRender(GameRender *gameRender)
{
    GameRender_FreeArrayRenderCell(&((*gameRender)->humanArrayStruct));
    GameRender_FreeArrayRenderCell(&((*gameRender)->alienArrayStruct));
    for(int i = 0; i < 2; i++){
        free((*gameRender)->hasBeenDeleted[i]);
        (*gameRender)->hasBeenDeleted[i] = NULL;
    }
    free((*gameRender)->hasBeenDeleted);
    (*gameRender)->hasBeenDeleted = NULL;
    GameRender_FreeAllRenderCell(&((*gameRender)->uiStruct));
    GameRender_FreeAllRenderCell(&((*gameRender)->cannonStruct));
    SDL_DestroyRenderer((*gameRender)->renderer);
    SDL_DestroyWindow((*gameRender)->windowMain);
    (*gameRender)->windowMain = NULL;
    free(*gameRender);
    *gameRender = NULL;
}

/*
    Return 0 on success, or negative on failure.
    Only add an element to the end of the chain of RenderCell
*/
int GameRender_AddRenderCell(RenderCell firstRC, RenderCell newRC)
{
    int error = 0;
    RenderCell temp = firstRC;

    if (firstRC->texture == NULL) //If the RenderCell doesn't contain anything
    {
        firstRC->texture = newRC->texture;
        firstRC->src = newRC->src;
        firstRC->dst = newRC->dst;
        firstRC->next = NULL; //Just to be sure
    }
    else
    { //If the RenderCell already contains something

        //Find the last RenderCell
        for (; temp->next != NULL; temp = temp->next);

        if (newRC != NULL)
        {
            temp->next = newRC;
        }
        else
        {
            fprintf(stderr, "Error in GameRender_AddRenderCell()\n");
            error = -1;
        }
    }

    return error;
}

/*
    Only delete one element of the chain, depending on pointer.
    id 0 = first element, id nb-1 or superior = last element
*/
void GameRender_DeleteRenderCell(RenderCell *firstRC, RenderCell *toDelete)
{
    RenderCell temp = *firstRC;
    RenderCell previous = temp;
    RenderCell next = NULL;

    // find the Element and keep the previous one
    for (; temp != *toDelete; previous = temp, temp = temp->next);

    // if the RenderCell in parameters isn't already null
    if (temp != NULL)
    {
        // next = NULL if temp is in last
        next = temp->next;
        SDL_DestroyTexture(temp->texture);
        free(temp->src);
        free(temp->dst);
        free(temp);
        toDelete = NULL;
        if (temp == *firstRC)
        { // if we're in the first position
            *firstRC = next;
        }
        else
        { // Else we're in the middle or in last. If in last, next is NULL
            previous->next = next;
        }
    }
    else
    {
        fprintf(stderr, "Trying to delete a NULL RenderCell\n");
    }
}

/*
    return a new RenderCell or NULL if it failed
*/
RenderCell GameRender_CreateEmptyRenderCell()
{
    RenderCell new = NULL;

    new = (RenderCell_Struct *)malloc(sizeof(RenderCell_Struct));
    if (new != NULL)
    {
        new->texture = NULL;
        new->src = (SDL_Rect *)malloc(sizeof(SDL_Rect));
        new->src->x = -500;
        new->dst = (SDL_Rect *)malloc(sizeof(SDL_Rect));
        new->dst->x = -500;
        new->next = NULL;

        // if something is wrong, we free everything and return NULL
        if (new->src == NULL)
        {
            free(new->dst);
            new->dst = NULL;
        }
        if (new->dst == NULL)
        {
            free(new->src);
            new->src = NULL;
        }
        if (new->src == NULL && new->dst == NULL)
        {
            free(new);
            new = NULL;
        }
    }

    return new;
}

/*
    return 0 on succes or negative if error.
    add a BMP to a renderCell.
    widthRatio and heightRatio dictate if we resize the image. There will conversion between int and double,
    but it won't cause problem
*/
int GameRender_AddElementToRenderCell(RenderCell renderCell, SDL_Renderer *renderer, char *path_to_element, int posX, int posY, float widthRatio, float heightRatio)
{
    int error = 0;
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;
    RenderCell newRC = NULL;
    int width = 0, height = 0;

    surface = SDL_LoadBMP(path_to_element);

    if (surface != NULL)
    {

        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        // Get the texture width and height
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);

        // Resize the texture
        width *= widthRatio;
        height *= heightRatio;

        //newRC = (RenderCell_Struct *)malloc(sizeof(RenderCell_Struct));
        newRC = GameRender_CreateEmptyRenderCell();

        if (newRC != NULL)
        {
            newRC->texture = texture;
            texture = NULL;

            newRC->src->x = -500; // Say that we take the entire texture to render
            newRC->src->y = -500; // (doesn't actually say it, I won't use it anyway in this version)
            newRC->src->w = -500;
            newRC->src->h = -500;

            newRC->dst->x = posX;
            newRC->dst->y = posY;
            newRC->dst->w = width;
            newRC->dst->h = height;

            error = GameRender_AddRenderCell(renderCell, newRC);
        }
    }
    if (surface == NULL || newRC == NULL)
    {
        fprintf(stderr, "Error in GameRender_AddElementToRenderCell() : %s \n", SDL_GetError());
        error = -1;
    }
    return error;
}

/*
    Return the path to the corresponding texture.
*/
char *GameRender_GetPathFromId(int id)
{
    char *temp = NULL;
    switch (id)
    {
    case -3:
        temp = PATH_TO_ALIEN_3;
        break;
    case -2:
        temp = PATH_TO_ALIEN_2;
        break;
    case -1:
        temp = PATH_TO_ALIEN_1;
        break;
    case 0:
        temp = PATH_TO_CANNON_0;
        break;
    case 1:
        temp = PATH_TO_HUMAN_1;
        break;
    case 2:
        temp = PATH_TO_HUMAN_2;
        break;
    case 3:
        temp = PATH_TO_HUMAN_3;
        break;
    case 4:
        temp = PATH_TO_HUMAN_4;
        break;
    default:
        break;
    }
    return temp;
}

/*
    return 0 on succes or negative if error. Only used in init
    Add every ui element needed in the game, depending on the gameMode
*/
int GameRender_PrepareGame(GameRender gameRender, int gameMode)
{
    int error = 0;

    // I. Ui

    // add the background
    error = GameRender_AddElementToRenderCell
    (
        gameRender->uiStruct, 
        gameRender->renderer, 
        PATH_TO_BACKGROUND, 
        0, 
        0, 
        gameRender->ratio, 
        gameRender->ratio
    );

    // add the playground
    error = GameRender_AddElementToRenderCell
    (
        gameRender->uiStruct, 
        gameRender->renderer, 
        PATH_TO_PLAYGROUND, 
        200 * gameRender->ratio, 
        20 * gameRender->ratio, 
        gameRender->ratio, 
        gameRender->ratio
    );

    // add the shop and the cursor
    if (gameMode < 0 || gameMode > 3) {
        fprintf(stderr, "Wrong gameMode, not finishing to load the UI\n");
    } else {
        error = GameRender_AddElementToRenderCell(
                gameRender->uiStruct,
                gameRender->renderer,
                PATH_TO_HUMAN_SHOP, 
                20 * gameRender->ratio, 
                800 * gameRender->ratio, 
                gameRender->ratio, 
                gameRender->ratio);
        error = GameRender_AddElementToRenderCell(
                gameRender->uiStruct,
                gameRender->renderer,
                PATH_TO_CURSOR_PLAYER_1, 
                200 * gameRender->ratio, 
                20 * gameRender->ratio, 
                gameRender->ratio, 
                gameRender->ratio);
        error = GameRender_AddElementToRenderCell(
                gameRender->uiStruct,
                gameRender->renderer,
                PATH_TO_CURSOR_SHOP_HUMAN, 
                20 * gameRender->ratio, 
                800 * gameRender->ratio,
                gameRender->ratio, 
                gameRender->ratio);
        SDL_Color humanColor = {0, 0, 255};;
        RenderCell headerMoneyHuman = GameRender_CreateEmptyRenderCell();
        headerMoneyHuman->dst->x = 680 * gameRender->ratio ;
        headerMoneyHuman->dst->y = 800 * gameRender->ratio ;
        headerMoneyHuman->dst->w = 250 * gameRender->ratio ;
        headerMoneyHuman->dst->h = 62 * gameRender->ratio ;
        GameRender_UpdateText(gameRender, headerMoneyHuman, "Money :", humanColor);
        error = GameRender_AddRenderCell(gameRender->uiStruct, headerMoneyHuman);
        headerMoneyHuman = NULL;

        RenderCell moneyHuman = GameRender_CreateEmptyRenderCell();
        moneyHuman->dst->x = 680 * gameRender->ratio ;
        moneyHuman->dst->y = 862 * gameRender->ratio ;
        moneyHuman->dst->w = 250 * gameRender->ratio ;
        moneyHuman->dst->h = 62 * gameRender->ratio ;
        error = GameRender_AddRenderCell(gameRender->uiStruct, moneyHuman);
        moneyHuman = NULL;

        RenderCell headerScoreHuman = GameRender_CreateEmptyRenderCell();
        headerScoreHuman->dst->x = 680 * gameRender->ratio ;
        headerScoreHuman->dst->y = 924 * gameRender->ratio ;
        headerScoreHuman->dst->w = 250 * gameRender->ratio ;
        headerScoreHuman->dst->h = 62 * gameRender->ratio ;
        GameRender_UpdateText(gameRender, headerScoreHuman, "Score :", humanColor);
        error = GameRender_AddRenderCell(gameRender->uiStruct, headerScoreHuman);
        headerScoreHuman = NULL;

        RenderCell scoreHuman = GameRender_CreateEmptyRenderCell();
        scoreHuman->dst->x = 680 * gameRender->ratio ;
        scoreHuman->dst->y = 986 * gameRender->ratio ;
        scoreHuman->dst->w = 250 * gameRender->ratio ;
        scoreHuman->dst->h = 62 * gameRender->ratio ;
        error = GameRender_AddRenderCell(gameRender->uiStruct, scoreHuman);
        scoreHuman = NULL;
    }

    if(gameMode == 0){
        error = GameRender_AddElementToRenderCell(
                gameRender->uiStruct,
                gameRender->renderer,
                PATH_TO_ALIEN_SHOP, 
                1250 * gameRender->ratio, 
                800 * gameRender->ratio, 
                gameRender->ratio, 
                gameRender->ratio);
        error = GameRender_AddElementToRenderCell(
                gameRender->uiStruct,
                gameRender->renderer,
                PATH_TO_CURSOR_PLAYER_2, 
                1850 * gameRender->ratio, 
                20 * gameRender->ratio, 
                gameRender->ratio, 
                gameRender->ratio);
        error = GameRender_AddElementToRenderCell(
                gameRender->uiStruct,
                gameRender->renderer,
                PATH_TO_CURSOR_SHOP_ALIEN, 
                1250 * gameRender->ratio, 
                800 * gameRender->ratio, 
                gameRender->ratio, 
                gameRender->ratio);

        SDL_Color alienColor = {0, 128, 0};
        RenderCell headerMoneyAlien = GameRender_CreateEmptyRenderCell();
        headerMoneyAlien->dst->x = 1000 * gameRender->ratio ;
        headerMoneyAlien->dst->y = 800 * gameRender->ratio ;
        headerMoneyAlien->dst->w = 250 * gameRender->ratio ;
        headerMoneyAlien->dst->h = 62 * gameRender->ratio ;
        GameRender_UpdateText(gameRender, headerMoneyAlien, "Money :", alienColor);
        error = GameRender_AddRenderCell(gameRender->uiStruct, headerMoneyAlien);
        headerMoneyAlien = NULL;

        RenderCell moneyAlien = GameRender_CreateEmptyRenderCell();
        moneyAlien->dst->x = 1000 * gameRender->ratio ;
        moneyAlien->dst->y = 862 * gameRender->ratio ;
        moneyAlien->dst->w = 250 * gameRender->ratio ;
        moneyAlien->dst->h = 62 * gameRender->ratio ;
        error = GameRender_AddRenderCell(gameRender->uiStruct, moneyAlien);
        moneyAlien = NULL;
    }

    // II. Cannon 
    
    for(int i = 0; i < LANE; i ++){
        error = GameRender_AddElementToRenderCell(
            gameRender->cannonStruct, 
            gameRender->renderer, 
            PATH_TO_CANNON_0, 
            20 * gameRender->ratio, 
            20 * gameRender->ratio + i*150 * gameRender->ratio, 
            gameRender->ratio, 
            gameRender->ratio);
    }

    if( error < 0){
        fprintf(stderr, "Error in Prepare Game\n");
    }
    return error;
}

/*
    return 0 on succes or negative if error.
    Takes the GameRender, the lane where the entity is added, and his id(for his texture)
    id : {1,2,3,4} for human, id : {-1,-2,-3} for alien, id : {0} for cannon
    posX : pos of the Human Entity
*/
int GameRender_AddEntity(GameRender gameRender, int idEntity, int lane, int posX)
{
    char *pathToEntity = NULL;
    SDL_Renderer *renderer = NULL;
    int x = 0;
    int y = 0;
    int screenW = 0;
    int screenH = 0;

    if (idEntity >= -3 && idEntity <= 4)
    {
        pathToEntity = GameRender_GetPathFromId(idEntity);
        renderer = gameRender->renderer;
        screenW = gameRender->screen_width;
        screenH = gameRender->screen_height;

        x = 200 * gameRender->ratio + (posX * 0.01) * 150 * gameRender->ratio;
        y = 20 * gameRender->ratio + lane * 150 * gameRender->ratio;

        if (idEntity < 0)
        { //It's an alien
            if(gameRender->alienArrayStruct[lane] == NULL){
                gameRender->alienArrayStruct[lane] = GameRender_CreateEmptyRenderCell();
            }
            GameRender_AddElementToRenderCell(gameRender->alienArrayStruct[lane], renderer, pathToEntity, x, y, gameRender->ratio, gameRender->ratio);
        }
        else if (idEntity > 0)
        { //It's an human
        if(gameRender->humanArrayStruct[lane] == NULL){
                gameRender->humanArrayStruct[lane] = GameRender_CreateEmptyRenderCell();
            }
            GameRender_AddElementToRenderCell(gameRender->humanArrayStruct[lane], renderer, pathToEntity, x, y, gameRender->ratio, gameRender->ratio);
        }
    }
}

/*
    Look at the entity, and convert his postion to the RenderCell corresponding
    (it only changes the x position)
*/
void GameRender_MoveEntity(float screenRatio, RenderCell rcToMove, Entity *entity)
{
    int newX = 0;
    newX = 200 * screenRatio + (entity->position * 1.5) * screenRatio; 
    rcToMove->dst->x = newX;
}

RenderCell GameRender_GetLastRC(GameRender gameRender, int id, int lane){

    RenderCell pointer = NULL;

    if(id > 0){
        pointer = gameRender->humanArrayStruct[lane];
    } else if(id < 0) {
        pointer = gameRender->alienArrayStruct[lane];
    } else {
        printf("Wrong id in GetLastRC");
    }

    for(; pointer->next != NULL; pointer = pointer->next);

    return pointer;
}

RenderCell GameRender_GetI_RC(RenderCell firstRC, int id){
    RenderCell temp = firstRC;
    for(int i = 0; i < id; i++){
        temp = temp->next;
    }
    return temp;
}

/*
    Take the gameRender, a chain of entity with its corresponding chain en RenderCell, browse every element
    and make the different adjustment
*/
void GameRender_UpdateRcEntity(GameRender gameRender, RenderCell *firstRC, Entity *firstEntity, int *waitingToUpdate)
{
    int minimumHealth = 100;
    Entity *tempEntity = firstEntity;
    RenderCell tempRC = *firstRC;
    
    for (; tempEntity != NULL && *waitingToUpdate != 1; tempEntity = tempEntity->next)
    {
        if (tempEntity != NULL && tempEntity->hp <= 30)
        {
            printf("[RENDER] Free RenderCell\n");
            RenderCell nextRC = tempRC->next;
            GameRender_DeleteRenderCell(firstRC, &tempRC);
            *waitingToUpdate = 1;
            tempRC = nextRC;
            continue;
        }

        if ((tempRC == NULL || tempRC->texture == NULL ) && tempEntity != NULL && tempEntity->hp > minimumHealth)
        {
            printf("[RENDER] Adding RenderCell\n");
            GameRender_AddEntity(gameRender, tempEntity->id, tempEntity->lane, tempEntity->position);
            tempRC = GameRender_GetLastRC(gameRender, tempEntity->id, tempEntity->lane);
        }

        if (tempRC != NULL)
        {
            GameRender_MoveEntity(gameRender->ratio, tempRC, tempEntity);
            tempRC = tempRC->next;
        }

    }
}

void GameRender_UpdateText(GameRender gameRender, RenderCell scoreCell, char *textToDisplay, SDL_Color color){
    TTF_Font *font;
    int newWidth = 0, newHeight = 0;

    font = TTF_OpenFont(PATH_TO_FONT, 48);
    if(!font){
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }

    SDL_Surface *text_surface = NULL;

    if(!(text_surface = TTF_RenderText_Solid(font, textToDisplay, color))){
        fprintf(stderr, "GameRender_UpdateMoney, TTF_RenderText_Solid: %s\n", TTF_GetError());
    } else {
        scoreCell->texture = SDL_CreateTextureFromSurface(gameRender->renderer, text_surface);

        SDL_QueryTexture(scoreCell->texture, NULL, NULL, &newWidth, &newHeight);
        scoreCell->dst->w =newWidth * gameRender->ratio;
        scoreCell->dst->h =newHeight * gameRender->ratio;


        SDL_FreeSurface(text_surface); 
    }

    TTF_CloseFont(font);
    font = NULL;
}

void GameRender_UpdateUi(GameRender gameRender, Shop *humanShop, Shop *alienShop, Player* humanPlayer, Player* alienPlayer, int gameMode)
{
    RenderCell pointer = gameRender->uiStruct;
    
    if (gameMode < 0 || gameMode > 3) {
        fprintf(stderr, "Wrong gameMode, not finishing to load the UI\n");
    } else {
        for(int i = 0; i < 3; i++){
            pointer = pointer->next;
        }
        pointer->dst->x = 200 * gameRender->ratio + humanShop->cursor_position * 1.5 * gameRender->ratio;
        pointer->dst->y = 20 * gameRender->ratio + (humanShop->cursor_lane * 150) * gameRender->ratio;
        pointer = pointer->next;

        pointer->dst->x = 20 * gameRender->ratio + (humanShop->cursor_shop -1) * 162 * gameRender->ratio;
        pointer = pointer->next->next;
        
        SDL_Color humanColor = {0, 0, 255};
        char textToDisplay[50];
        sprintf(textToDisplay, "%d", (int)humanPlayer->golds);  
        GameRender_UpdateText(gameRender, pointer, textToDisplay, humanColor);
        pointer = pointer->next->next;

        sprintf(textToDisplay, "%d", humanPlayer->score);
        GameRender_UpdateText(gameRender, pointer, textToDisplay, humanColor);
    }

    if(gameMode == 0){
        pointer = pointer->next->next;

        pointer->dst->y = 20 * gameRender->ratio + alienShop->cursor_lane * 150 * gameRender->ratio;
        pointer = pointer->next;

        pointer->dst->x = 1250 * gameRender->ratio + (-alienShop->cursor_shop -1) * 217 * gameRender->ratio;
        pointer = pointer->next->next;

        SDL_Color alienColor = {0, 128, 0};
        char textToDisplay[50];
        sprintf(textToDisplay, "%d", (int)alienPlayer->golds);  
        GameRender_UpdateText(gameRender, pointer, textToDisplay, alienColor);
    }

}

/*
    Display a specific RenderCell
*/
void GameRender_DisplayRenderCell(RenderCell rcToDisplay)
{
    int i = 0;
    printf("---------------------------------------------\n");
    for(RenderCell p = rcToDisplay; p != NULL; p = p->next, i++)
    {
        printf("%d. x : %d | y : %d | texture : %p\n",i , p->dst->x, p->dst->y, p->texture);
    }
}

/*
    Display everything
*/
void GameRender_DisplayEverything(GameRender gameRender)
{
    printf("---------------------------------------------\n");
    printf("gameRender : %p | width : %d | height : %d\n", gameRender, gameRender->screen_width, gameRender->screen_height);
    printf("renderer : %p\n", gameRender->renderer);
    printf("---------------------------------------------\n");
    printf("humanArrayStruct : %p\n", gameRender->humanArrayStruct);
    for(int i = 0; i < LANE; i++){
        GameRender_DisplayRenderCell(gameRender->humanArrayStruct[i]);
    } 
    printf("---------------------------------------------\n");
    printf("alienArrayStruct : %p\n", gameRender->humanArrayStruct);
    for(int i = 0; i < LANE; i++){
        GameRender_DisplayRenderCell(gameRender->alienArrayStruct[i]);
    } 
    printf("---------------------------------------------\n");
    printf("cannonStruct : %p\n", gameRender->cannonStruct);
    GameRender_DisplayRenderCell(gameRender->cannonStruct);
    printf("---------------------------------------------\n");
    printf("uiStruct : %p\n", gameRender->cannonStruct);
    GameRender_DisplayRenderCell(gameRender->uiStruct);
}