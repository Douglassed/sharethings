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
    char *stock = chercher_mdp(id);
    stock = chercher_mdp(id);
    //for (int i=0;idd[i] != '\0';i++){
    printf("%s\n",stock );
    free (stock);


    return 0;
}
