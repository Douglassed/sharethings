#include "../include/menus.h"
#include <stdio.h>
#include <stdlib.h>

struct _menus {
    char* etoiles;
    char normal;
};

void testchar(){
    Menus m = (Menus)malloc(sizeof(Menus));
    m->etoiles = "bonjour";
    m->normal = 'a';
    printf("%s\n", m->etoiles);
}

void menu_signin(){
  printf("Login:");
  printf("Password:");
}

void menu_accueil(){
  printf("\t ----\n");
  printf("\t|MENU|\n");
  printf("\t ----\n\n\n\n");
  printf("Rechercher une ressource");
  printf("Gestion des ressources");
  printf("Parametre compte");
}
