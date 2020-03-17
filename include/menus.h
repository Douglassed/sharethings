#ifndef __MODULE_H__
#define __MODULE_H__
#include <stdbool.h>

typedef struct _menus * Menus;

void monmenus();
char* menu_signup();
//void menu_signin();

bool compare_mdp(char *password);

void menu_admin();
void menu_accueil();
int lire_entier(int *a);
int lire_fin_ligne ();

#endif
