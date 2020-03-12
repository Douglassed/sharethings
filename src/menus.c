#include "../include/menus.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


struct _menus {
    char* etoiles;
    char normal;
};

void monmenus(){
    printf("menus ok\n");
}

void menu_signin(){
    char NDC[100],ch;
    int i = 0;
    printf("Entrez votre nom de compte : ");
    ch = getchar();
    while ( ch != 10 ){
        NDC[i] = ch;
        ch = getchar();
        i++;
    }
    char ndc[i];
    for (int j = 0; j < i; j++){
        ndc[j] = NDC[j];
    }
    char *password; // password string pointer
    password = getpass("Enter votre mot de passe : "); // get a password
    system("clear");
    printf("Vous etes connecter : %s\n",ndc);
}

void menu_accueil(){
  printf("\t ----------------------------\n");
  printf("\t|Bienvenue dans Sharethings !|\n");
  printf("\t ----------------------------\n\n");
  menu_signin();
  printf("1 - Rechercher une ressource\n");
  printf("2 - Gestion des ressources\n");
  printf("3 - Parametre compte\n");
  int nb;
  scanf("%d",nb);
}
