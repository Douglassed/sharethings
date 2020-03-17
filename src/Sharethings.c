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
    char *id = "Clement";
    char *IDD;
    chercher_mdp(id, &IDD);
    printf("%s\n", IDD);
    return 0;
}
