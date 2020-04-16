#ifndef __MODULE_H__
#define __MODULE_H__
#include <stdbool.h>

typedef struct _menus * Menus;

int menu_affiche_ress();
void menu_recherche_specifique(char *obj,int choix, char* id);
int menu_signup(char * modif);
int menu_signin(char **ndc);
bool compare_char(char *password,char *passwordbis);
void menu_admin(void);
void menu_accueil(void);
int lire_entier(int *a,int min, int max);
int lire_fin_ligne(void);
void menu_user(char **ndc);
bool condition(char *ndc, char *format);
void modif_user(int choix);
bool verification(void);
void menu_gestion_ress(char** id);
int ajout_ress(char** id);
int modif_ress(char **id);
int menu_affiche_ress(int fonction, char** cat, char* id);
int chiffrement (char* mdp);


#endif
