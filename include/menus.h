#ifndef __MODULE_H__
#define __MODULE_H__
#include <stdbool.h>

typedef struct _menus * Menus;

void monmenus();
void menu_signup();
void menu_signin();

bool compare_mdp(char *password,char *passwordbis);

void menu_admin();
void menu_accueil();
int lire_entier(int *a);
int lire_fin_ligne ();
bool condition(char *ndc, char *format);


#endif
