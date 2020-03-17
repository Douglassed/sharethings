#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/personnes.h"
#include "../include/ressources.h"
#include "../include/menus.h"
#include "../include/json.h"
#include <json-c/json.h>


int main (int argc, char *argv[]) {
    //menu_accueil();
    char *id = "Clezzzment";
    char *MDP = "default";
    chercher_mdp(id, &MDP);
    printf("%s\n", MDP);
    return 0;
}
