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
    char NDC[30],ch;
    char *password; // password string pointer
    int i = 0;
    int index;
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
        index = 0;
        char stock_password[30];
        while(password[index] != '\0'){
            stock_password[index] = password[index];
            stock_password[index+1] = '\0';
            index++;
        }
        printf("%s\n",stock_password );
        bool compare = compare_mdp(stock_password);
        if (!compare){
            printf("mot de passe non similaire\n");
            printf("appuyez sur entrer pour continuer\n");
            printf("%d\n",compare );

            getchar();
            system("clear");
        }
    }while(compare != false);
    system("clear");
    printf("Vous etes : %s\n\n",NDC);
    return NDC;
}

void menu_signin(){
    bool verif;
    char NDC[200],ch;
    char *password; // password string pointer
    int i = 0;
    error_signin:
    printf("Entrez votre nom de compte : ");
    ch = getchar();
    while ( ch != 10 ){
        NDC[i] = ch;
        ch = getchar();
        i++;
    }

    password = getpass("Enter votre mot de passe : "); // get a password
    //verifier nom de compte et mot de passe
    verif = false;
    if (!verif){
        printf("\ncombinaison nom de compte et mot de passe erronée\n\n");
        printf("appuyez sur entrer pour continuer\n");
        getchar();
        goto error_signin;
    }

    system("clear");
    printf("Vous etes : %s\n\n",NDC);
}

bool compare_mdp(char *password){
    int j = 0;
    bool correct = true;
    char *passwordbis; // password string pointer
    passwordbis = getpass("confirmez votre mot de passe : "); // get a password
    printf("%s\n",password );
    printf("%s\n",passwordbis );

    while(password[j] != '\0' || passwordbis[j] != '\0' && correct == true){
        if (password[j] != passwordbis[j]){
            correct = false;
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
          menu_signin();
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
