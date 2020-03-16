#include "../include/menus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

struct _menus {
    char* etoiles;
    char normal;
};

void monmenus(){
    printf("menus ok\n");
}

char* menu_signup(){
    bool compare = true;
    char NDC[200],ch;
    char *passwordbis; // password string pointer
    char *password; // password string pointer
    int i = 0;
    do{
        i = 0;
        printf("Entrez votre nom de compte : ");
        ch = getchar();
        while ( ch != 10 ){
            NDC[i] = ch;
            ch = getchar();
            i++;
        }
        password = getpass("Enter votre mot de passe : "); // get a password
        passwordbis = getpass("Confirmez votre mot de passe : "); // get a password
        bool compare = compare_mdp(password,passwordbis);
        if (!compare){
            printf("mot de passe non similaire\n");
        }
        printf("appuyez sur entrer pour continuer\n");
        getchar();
    }while(compare == false);
    system("clear");
    printf("Vous etes : %s\n\n",NDC);
    return NDC;
}

/*void menu_signin(){
    char NDC[200],ch;
    char *passwordbis; // password string pointer
    char *password; // password string pointer
    int i = 0;
    printf("Entrez votre nom de compte : ");
    ch = getchar();
    while ( ch != 10 ){
        NDC[i] = ch;
        ch = getchar();
        i++;
    }

    password = getpass("Enter votre mot de passe : "); // get a password

    passwordbis = getpass("Confirmez votre mot de passe : "); // get a password
    bool compare = compare_mdp(password,passwordbis);
    if (!compare){
        printf("mot de passe non similaire");
    }
    printf("appuyez sur entrer pour continuer\n");
        getchar();

    }
    system("clear");
    printf("Vous etes : %s\n\n",NDC);
}*/

bool compare_mdp(char *password,char *passwordbis){
    int j = 0;
    bool correct = true;
    while(password[j] != '\0' && passwordbis[j] != '\0' && correct == true && j != 10){
        if (password[j] != passwordbis[j]){
            correct = true;
        }
        j++;
    }
    return correct;
}

void menu_accueil(){
    system("clear");

  printf(" ----------------------------\n");
  printf("|Bienvenue dans Sharethings !|\n");
  printf(" ----------------------------\n\n");
  int erreur;
  int choix;
  char *NDC;
  do{
      printf("| 1 | - Se connecter\n| 2 | - S'inscrire\n\n");
      printf("choisissez : ");
      erreur = lire_entier(&choix);
      if (choix == 1){
          //menu_signin();
      }else if (choix == 2){
          NDC = menu_signup();
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
