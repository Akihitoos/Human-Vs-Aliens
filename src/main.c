#include "update.h"
#include "GameRender.h"
#include "FileHandler.h"

int main(int argc, char **argv)
{
    GameRender gameRender = NULL;
    SDL_Window *windowMain = NULL;
    Entity **humanArray = NULL;
    Entity **alienArray = NULL;
    Cannon cannonArray = NULL;
    Shop *humanShop = NULL;
    Shop *alienShop = NULL;
    Player *humanPlayer = NULL;
    Player *alienPlayer = NULL;
    char *gameModeMessage = NULL;
    int gameMode = 0, gameEnded = 0, menu_end = 0, choice = 0;

    gameModeMessage = GetArgumentConfiguration(argc, argv, &gameMode);

    printf("Welcome to Human Vs Aliens !\n");
    printf("%s\n", gameModeMessage);
    FreeString(&gameModeMessage);

    //Menu
    while(!menu_end && gameMode != -1)
    {
        printf("1. Play the game\n");
        printf("2. View records\n");
        printf("0. Exit the game\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            gameEnded = 0;
            humanArray = init_entity_array();
            alienArray = init_entity_array();
            cannonArray = init_cannon_tab();
            humanShop = init_shop_human();
            alienShop = init_shop_alien();
            clock_t startingTime = clock();
            clock_t currentTime = startingTime;

            humanPlayer = init_human_player();
            alienPlayer = init_alien_player(gameMode);
            alienPlayer->gold_per_second = GetIAGoldPerSecond(gameMode);
            alienShop->cursor_position = -((rand() % 3) + 1);

            GameRender_Init(&windowMain, &gameRender, gameMode, humanShop, alienShop);

            while (!gameEnded)
            {   
                EventHandler(humanArray, alienArray, humanShop, alienShop, alienPlayer, humanPlayer, gameMode);
                if (gameMode > 0 && gameMode <= 3)
                {
                    AIHandler(alienShop, alienPlayer, alienArray);
                }
                gameEnded = update(humanArray, alienArray, humanPlayer, alienPlayer, cannonArray, gameRender->hasBeenDeleted, startingTime, currentTime);
                GameRender_UpdateGameRender(gameRender, humanArray, alienArray, humanPlayer, alienPlayer,
                                            cannonArray, humanShop, alienShop, gameMode);
                GameRender_UpdateRender(gameRender, gameMode);

                SDL_Delay(1000 / REFRESH_RATE);
            }

            GameRender_FreeEverything(&windowMain, &gameRender);

            FH_WriteScore(PATH_TO_HIGHSCORE_TXT, humanPlayer->score);

            free_array(&humanArray, &alienArray);
            free_cannon(&cannonArray);
            free_shop(&humanShop);
            free_shop(&alienShop);
            free_player(&humanPlayer);
            free_player(&alienPlayer);
            break;
        case 2:
            FH_DisplayAllScore(PATH_TO_HIGHSCORE_TXT);
            break;
        case 0:
            menu_end = 1;
            break;
        default:
            break;
        }

    }
    

    return EXIT_SUCCESS;
}