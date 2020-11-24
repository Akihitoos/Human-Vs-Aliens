#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Shop.h"
#include "Alien.h"

typedef struct Shop  //Structure pour associer un nom à un prix. On considère que chaque entité a une position i. 
{
    char** nom;
    int* prix;
}Shop;


Shop create_shop_alien(){   
    Shop *shop = (Shop*)malloc(sizeof(Shop));                       //Creation du shop
    if (shop != NULL){
        shop->nom = (char**)malloc(sizeof(char*)*3);                  //Creation du tableau de tableau de char
        shop->prix = (int*)malloc(sizeof(int)*3);                     //Creation du tableau de prix
        if ((shop->nom != NULL)&&(shop->prix != NULL)){                 //Partie à recopier pour chaque alien à ajouter
            shop->nom[0] = (char*)malloc(sizeof("Range Alien\0"));      //*      //\0 important pour char fin de chaine
            if (shop->nom[0] != NULL){                                  
                strcpy(shop->nom[0], "Range Alien\0");                  //*     //Copie du nom dans le tab
                shop->prix[0] = 300;                                    //*     //Copie du prix dans le tab
            }
            else
            {
                fprintf(stderr,"Malloc error");
            }                                                           //* Fin de recopie
            shop->nom[1] = (char*)malloc(sizeof("Melee Alien\0"));      //Import Melee Alien
            if (shop->nom[1] != NULL){                                  
                strcpy(shop->nom[1], "Melee Alien\0");                  
                shop->prix[1] = 500;                                
            }
            else
            {
                fprintf(stderr,"Malloc error");
            }       
            shop->nom[2] = (char*)malloc(sizeof("Tank Alien\0"));      //Import Tank Alien
            if (shop->nom[2] != NULL){                                  
                strcpy(shop->nom[2], "Tank Alien\0");                  
                shop->prix[2] = 1100;                                
            }
            else
            {
                fprintf(stderr,"Malloc error");
            }                                                   
        }
        else
        {
            fprintf(stderr,"Malloc error");
        }  
    }
    else
    {
        fprintf(stderr,"Malloc error");
    }
    return *shop;
}

int main(int argc, char const *argv[])
{
    Shop shop = create_shop_alien();
    for (int i = 0; i <=sizeof(shop.prix)/sizeof(int);i++){
    printf("%s : %d\n",shop.nom[i],shop.prix[i]);
    }
    return 0;
}
