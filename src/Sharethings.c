#include <stdio.h>
#include <stdlib.h>
#include "../include/personnes.h"
#include "../include/ressources.h"
#include "../include/menus.h"
#include "../include/json.h"


int main (int argc, char *argv[]) {
    //menu_accueil();
    char *id = "Clement";
    char *IDD = chercher_mdp(id);
    printf("%s\n", IDD);
    return 0;
}
