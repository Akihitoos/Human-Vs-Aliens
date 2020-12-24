#include "update.h"
#include "GameRender.h"

int main(int argc, char **argv)
{

    GameRender gameRender = NULL;
    SDL_Window *windowMain = NULL;
    Entity **humanArray = init_entity_array();
    Entity **alienArray = init_entity_array();
    Mower mowerArray = init_mower_tab();
    Shop *humanShop = init_shop_human();
    Shop *alienShop = init_shop_alien();
    Player *humanPlayer;
    Player *alienPlayer;
    int gameMode = 0, gameEnded = 0, menu_end = 0,choice = 0;;
    
    //Menu
    do
    {
        printf("Welcome to Human Vs Aliens !\n1. Play the game\n2. Choose a gamemode\n3. View records\n0. Exit the game\n");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:

            if(!gameEnded){

                humanPlayer = init_human_player();
                humanPlayer->gold_per_second = (double)50;
                alienPlayer = init_alien_player(gameMode);
                alienPlayer->gold_per_second = GetIAGoldPerSecond(gameMode);

                GameRender_Init(&windowMain, &gameRender, gameMode, humanShop, alienShop);

                while (!gameEnded)
                {
                    EventHandler(humanArray, alienArray, humanShop, alienShop, alienPlayer, humanPlayer, gameMode);
                    if(gameMode > 0 && gameMode <= 3){
                        AIHandler(alienShop, alienPlayer, alienArray);
                    }
                    gameEnded = update(humanArray, alienArray, humanPlayer, alienPlayer, mowerArray, gameRender->hasBeenDeleted);
                    GameRender_UpdateGameRender(gameRender, humanArray, alienArray, humanPlayer, alienPlayer,
                                                mowerArray, humanShop, alienShop, gameMode);
                    GameRender_UpdateRender(gameRender, gameMode);
                    
                    SDL_Delay(1000/REFRESH_RATE);
                }
                free_array(&humanArray, &alienArray);
                free_mower(&mowerArray);
                GameRender_FreeEverything(&windowMain, &gameRender);
                gameEnded = 1;

            } else {
                printf("Game already ended !\n");
            }

            break;
        case 2:
            GetGameMode(&choice, &gameMode);
            break;
        case 3:
            printf("DLC features \n");
            break;
        case 0:
            gameEnded = 1;
            menu_end = 1;
            break;
        default:
            break;
        }

    } while (!menu_end);

    return EXIT_SUCCESS;
}