#include "GameRenderBasics.h"

//Call the SDL_Init function and exit if it fails
void GameRender_InitSDL(Uint32 flags)
{
    if (SDL_Init(flags) != 0)
    {
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
    do
    {
        fprintf(stdout, "Please choose a resolution :\n");
        fprintf(stdout, "1 : 640 x 480\n");
        fprintf(stdout, "2 : 960 x 720\n");
        fprintf(stdout, "3 : 1024 x 576\n");
        fprintf(stdout, "4 : 1280 x 720\n");
        fprintf(stdout, "5 : 1600 x 900\n");
        fprintf(stdout, "6 : 1920 x 1080\n");
        fscanf(stdin, "%d", &choice);
        switch (choice)
        {
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
    } while (choice < 1);
}

//Return 0 on success or a negative error on failure
//Create a window by asking the user the resolution he wants, and return them via parameters
SDL_Window *GameRender_CreateWindow(int *width, int *height)
{
    SDL_Window *window = NULL;
    GameRender_GetDisplayMode(width, height);
    window = SDL_CreateWindow("Human vs Aliens", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, *width, *height, SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == NULL)
    {
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
GameRender GameRender_InitGameRender(SDL_Window *window, int width, int height)
{
    GameRender gameRender = NULL;
    gameRender = (GameRender_Struct *)malloc(sizeof(GameRender_Struct));
    if (gameRender != NULL)
    {
        gameRender->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        gameRender->humanArrayStruct = GameRender_InitArrayRenderCell();
        gameRender->alienArrayStruct = GameRender_InitArrayRenderCell();
        gameRender->mowerStruct = GameRender_InitRenderCell();
        gameRender->uiStruct = GameRender_InitRenderCell();
        gameRender->screen_width = width;
        gameRender->screen_height = height;
    }
    if (gameRender == NULL || gameRender->renderer == NULL)
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
    GameRender_FreeAllRenderCell(&((*gameRender)->uiStruct));
    GameRender_FreeAllRenderCell(&((*gameRender)->mowerStruct));
    SDL_DestroyRenderer((*gameRender)->renderer);
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
        for (; temp->next != NULL; temp = temp->next)
            ;

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
    Only delete one element of the chain, depending on his position.
    id 0 = first element, id nb-1 or superior = last element
*/
void GameRender_DeleteRenderCell(RenderCell *firstRC, int id)
{
    RenderCell toDelete = *firstRC;
    RenderCell previous = toDelete;
    RenderCell next = NULL;
    int i = 0;

    // find the Element and keep the previous one
    for (; toDelete->next != NULL && i < id; previous = toDelete, toDelete = toDelete->next, i++)
        ;

    // if the RenderCell in parameters isn't already null
    if (toDelete != NULL)
    {
        // next = NULL if toDelete is in last
        next = toDelete->next;
        SDL_DestroyTexture(toDelete->texture);
        free(toDelete->src);
        free(toDelete->dst);
        free(toDelete);
        if (id == 0)
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
    Not done yet
*/
void GameRender_ModifyRenderCell()
{
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
        new->dst = (SDL_Rect *)malloc(sizeof(SDL_Rect));
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
int GameRender_AddEntityToRenderCell(RenderCell renderCell, SDL_Renderer *renderer, char *path_to_element, int posX, int posY, double widthRatio, double heightRatio)
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
        temp = PATH_TO_MOWER_0;
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
    return 0 on succes or negative if error.
    Takes the GameRender, the lane where the entity is added, and his id(for his texture)
    id : {1,2,3,4} for human, id : {-1,-2,-3} for alien, id : {0} for mower
    posX : pos of the Human Entity
*/
int GameRender_AddEntity(GameRender gameRender, int idEntity, int lane, int posX)
{
    /*
        This function is a bit experimental / tricky, because of the equation. 
        We need to find where to position and redimension the different element, so
        I tried to find some equation allowing it, depending on the screen.
        Maybe do it depending on the 
    */
    char *pathToEntity = NULL;
    SDL_Renderer *renderer = NULL;
    RenderCell rcLane = NULL;
    int x = 0;
    int y = 0;
    double widthRatio = 0;
    double heightRatio = 0;
    int screenW = 0;
    int screenH = 0;

    if (idEntity >= -3 && idEntity <= 4)
    {

        pathToEntity = GameRender_GetPathFromId(idEntity);
        renderer = gameRender->renderer;
        screenW = gameRender->screen_width;
        screenH = gameRender->screen_height;

        // position are in int, but I expect the approximation to be usable
        // position x of entity: (screen width * 13/96) + posX * (screen width * 35/48)
        // position y of entity: (screen height * 7/96) + lane * (screen width * 5/96 + screen width * 1/128)
        //                                                       ( screen width * 23/384 )
        // width of entity is  : screen width * 5/96
        // height of entity is : screen height * 1/20

        y = (screenH * 7 / 96) + lane * (screenH * 23 / 384);

        widthRatio = (((double)screenW * 5. / 96.) / ((double)SIZE_ENTITY / 4.));
        heightRatio = widthRatio;

        if (idEntity < 0)
        { //It's an alien
            x = (screenW * 13 / 96) + 1000 * (screenW * 35 / 48);
            rcLane = gameRender->alienArrayStruct[lane];
        }
        else if (idEntity > 0)
        { //It's an human
            x = (screenW * 13 / 96) + posX * (screenW * 35 / 48);
            rcLane = gameRender->humanArrayStruct[lane];
        }
        else
        { //It's a mower
            rcLane = gameRender->humanArrayStruct[lane];
        }
        GameRender_AddEntityToRenderCell(rcLane, renderer, pathToEntity, x, y, widthRatio, heightRatio);
    }
}

/*
    Look at the entity, and convert his postion to the RenderCell corresponding
    (it only changes the x position)
*/
void GameRender_MoveEntity(RenderCell rcToMove, Entity *entity)
{
    int newX = 0;
    newX = entity->position; // Need the equation to transform it from 1000 to the actual size of the lane
    rcToMove->dst->x = newX;
}

/*
    Take the gameRender, a chain of entity with its corresponding chain en RenderCell, browse every element
    and make the different adjustment
*/
void GameRender_UpdateRcEntity(GameRender gameRender, RenderCell *firstRC, Entity *firstEntity)
{
    Entity *tempEntity = firstEntity;
    RenderCell tempRC = *firstRC;
    for (int i = 0; tempEntity != NULL; tempEntity = tempEntity->next, tempRC = tempRC->next, i++)
    {
        // Check if the entity is dead
        if (tempEntity->hp < 0)
        {
            GameRender_DeleteRenderCell(firstRC, i);
        }

        // Check if the entity was created
        if ((tempRC->texture == NULL || tempRC == NULL) && tempEntity != NULL)
        {
            GameRender_AddEntity(gameRender, tempEntity->id, tempEntity->lane, tempEntity->position);
        }

        // Make the entity move
        GameRender_MoveEntity(tempRC, tempEntity);
    }
}
