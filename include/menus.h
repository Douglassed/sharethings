#ifndef __MODULE_H__
#define __MODULE_H__
#include <stdbool.h>

typedef struct _menus * Menus;

void menu_signup(void);
void menu_signin(char **ndc);
bool compare_char(char *password,char *passwordbis);
void menu_admin(void);
void menu_accueil(void);
int lire_entier(int *a);
int lire_fin_ligne(void);
void menu_user(char **ndc);
bool condition(char *ndc, char *format);
void modif_user(int choix);



#endif
