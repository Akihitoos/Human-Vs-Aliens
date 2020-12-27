#include "update.h"
#include "GameRender.h"

int main(int argc, char **argv)
{

    GameRender gameRender = NULL;
    SDL_Window *windowMain = NULL;
    Entity **humanArray = NULL;
    Entity **alienArray = NULL;
    Mower mowerArray = NULL;
    Shop *humanShop = NULL;
    Shop *alienShop = NULL;
    Player *humanPlayer = NULL;
    Player *alienPlayer = NULL;
    int gameMode = 0, gameEnded = 0, menu_end = 0,choice = 0;;
    
    //Menu
    do
    {
        printf("Welcome to Human Vs Aliens !\n1. Play the game\n2. Choose a gamemode\n3. View records\n0. Exit the game\n");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            gameEnded = 0;
            humanArray = init_entity_array();
            alienArray = init_entity_array();
            mowerArray = init_mower_tab();
            humanShop = init_shop_human();
            alienShop = init_shop_alien();
            clock_t startingTime = clock();
            clock_t currentTime = startingTime;

            if(humanPlayer == NULL){
                humanPlayer = init_human_player();
                humanPlayer->gold_per_second = (double)50;
            } else {
                humanPlayer->golds = (double)500;
                humanPlayer->score = 0;
            }
        
            alienPlayer = init_alien_player(gameMode);
            alienPlayer->gold_per_second = GetIAGoldPerSecond(gameMode);
            alienShop->cursor_position = -( (rand()%3) + 1);

            GameRender_Init(&windowMain, &gameRender, gameMode, humanShop, alienShop);

            while (!gameEnded)
            {
                EventHandler(humanArray, alienArray, humanShop, alienShop, alienPlayer, humanPlayer, gameMode);
                if(gameMode > 0 && gameMode <= 3){
                    AIHandler(alienShop, alienPlayer, alienArray);
                }
                gameEnded = update(humanArray, alienArray, humanPlayer, alienPlayer, mowerArray, gameRender->hasBeenDeleted, startingTime, currentTime);
                GameRender_UpdateGameRender(gameRender, humanArray, alienArray, humanPlayer, alienPlayer,
                                            mowerArray, humanShop, alienShop, gameMode);
                GameRender_UpdateRender(gameRender, gameMode);
                
                SDL_Delay(1000/REFRESH_RATE);
            }
            
            free_array(&humanArray, &alienArray);
            free_mower(&mowerArray);
            free_shop(&humanShop);
            free_shop(&alienShop);
            free_player(&alienPlayer);
            GameRender_FreeEverything(&windowMain, &gameRender);
            break;
        case 2:
            GetGameMode(&choice, &gameMode);
            break;
        case 3:
            printf("Your score is %d \n", humanPlayer->score);
            break;
        case 0:
            menu_end = 1;
            break;
        default:
            break;
        }

    } while (!menu_end);

    free_player(&humanPlayer);

    return EXIT_SUCCESS;
}