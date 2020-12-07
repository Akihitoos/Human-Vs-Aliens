#include "Shop.h"

//test update
int main(int argc, char **argv)
{
    Shop* human = init_shop_human();
    Shop* alien = init_shop_alien();
    printf("shop human :\n");
    afficher_curseurs(human);
    printf("shop alien : \n");
    afficher_curseurs(alien);
    printf(" deplacement des curseurs\n");
    for (int i = 0; i<= 20;i++){
        shop_navigate(alien,-1);
        shop_navigate(alien,-2);
        shop_navigate(alien,-3);
        afficher_curseurs(alien);
    }
}
