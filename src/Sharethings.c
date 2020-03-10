#include "../include/ressources.h"
#include "../include/personnes.h"
#include "../include/menus.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char NDC[10],MDP[10],ch;
    char *mdp;
    int i = 0;
    printf("Bienvenue dans Sharethings ! \n");
    printf("Entrez votre nom de compte: \n");
    ch = getchar();
    while ( ch != 10 && ch != 32){
        MDP[i] = ch;
        ch = getchar();
        i++;
    }
    printf("%s",MDP);
    /*for (i = 0; i < 5; i++){
        ch = mdp[i];
        printf("%c",ch);
    }
    /*printf("Entrez votre mot de passe: ");
    int i = 0;
    ch = 'a';
    do{
        ch = getchar();
        MDP[i] = ch;
        printf("%c\n",ch);
        printf("%d",i);
        i++;

    }while (ch != '\n' && i<15);*/
    //for (int i = 0; i < 8; i++){


    return 0;
}
