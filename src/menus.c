#include "../include/menus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

struct _menus {
    char* etoiles;
    char normal;
};

void monmenus(){
    printf("menus ok\n");
}

void menu_sign(int sign){

    char NDC[200],ch;
    int i = 0;
    printf("Entrez votre nom de compte : ");
    ch = getchar();
    while ( ch != 10 ){
        NDC[i] = ch;
        ch = getchar();
        i++;
    }
    printf("caractère : %c\n",NDC[10]);
    char *password; // password string pointer
    password = getpass("Enter votre mot de passe : "); // get a password
    if (sign == 2){
        char *passwordbis; // password string pointer
        passwordbis = getpass("Confirmez votre mot de passe : "); // get a password
    }
    system("clear");
    printf("Vous etes : %s\n\n",NDC);
}

void menu_accueil(){
    system("clear");

  printf(" ----------------------------\n");
  printf("|Bienvenue dans Sharethings !|\n");
  printf(" ----------------------------\n\n");
  int erreur;
  int choix;
  do{
      printf("| 1 | - Se connecter\n| 2 | - S'inscrire\n\n");
      printf("choisissez : ");
      erreur = lire_entier(&choix);
      if (choix == 1){
          menu_sign(1);
      }else if (choix == 2){
          menu_sign(2);
      }else{
          printf("erreur, tapez 1 ou 2 \n\n");
      }
  }while ((choix != 1 && choix != 2) || erreur == 1);


}

int lire_entier(int *a){
    int nb_lu;
    int nb_jete;
    int erreur = 0;

        nb_lu=scanf("%d",a);
        nb_jete=lire_fin_ligne();
        if (nb_lu != 1){
            printf("veuillez tapez un entier\n\n");
            erreur = 1;
        }else if (nb_jete!=0){
            printf("veuillez ne tapez qu'une seule chaine de caractère\n\n");
            erreur = 1;
        }

    return erreur;
}

int lire_fin_ligne (){
    char c;
    int res=0;
    c=getchar();
    while ((c!= EOF) && (c!= '\n')){
        c=getchar();
        if (!isspace(c)){
            res=res+1;
        }

    }
    return res;
}

void menu_user(){
    printf("menus : \n\n");
    printf("1 - Rechercher une ressource\n");
    printf("2 - Gestion des ressources\n");
    printf("3 - Parametre compte\n\n");
    printf("    Choisissez entre les differents menus : ");
}
