#include <stdio.h>
#include <stdlib.h>
#include "../include/personnes.h"
#include "../include/ressources.h"
#include "../include/menus.h"
#include "../include/json.h"


int main (int argc, char *argv[]) {
    menu_accueil();
    char *objet = "livre";
    afficher_liste_obj(objet);
    return 0;
}
