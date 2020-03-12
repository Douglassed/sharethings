#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/personnes.h"
#include "../include/ressources.h"
#include "../include/menus.h"


int main (int argc, char *argv[]) {
    monmenus();
    maressources();
    mapersonnes();
    char ret = '\n';
    printf("%d\n",ret);
    char NDC[100],ch;
    int i = 0;
    printf("Bienvenue dans Sharethings ! \n");
    printf("Entrez votre nom de compte: \n");
    ch = getchar();
    while ( ch != 10 ){
        NDC[i] = ch;
        ch = getchar();
        i++;
    }
    char ndc[i];
    for (int j = 0; j < i; j++){
        ndc[j] = NDC[j];
    }
    char *password; // password string pointer
    password = getpass("Enter Password: "); // get a password

    //vider le buffer avant d'entrz le mot de passe




    printf("nom de compte : %s\n",ndc);
    printf("votre mot de passe: %s\n",password);


    return 0;
}
