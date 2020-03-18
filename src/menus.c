#include "../include/menus.h"
#include "../include/json.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

void menu_signup(){
    bool compare;
    char NDC[30],ch;
    char *ndc = malloc(sizeof(char)*30);
    char *password; // password string pointer
    int i;
    int index;
    char *passwordbis; // password string pointer
    A:
    i = 0;
    printf("Entrez votre nom de compte : ");
    ch = getchar();
    while ( ch != 10 ){
        ndc[i] = ch;
        ch = getchar();
        i++;
    }
    ndc[i] = '\0';
    //verif nom de compte
    if (existe_id(ndc)){
        printf("Erreur : Nom de compte déjà existant\n");
        getchar();
        system("clear");
        goto A;
    }
    password = getpass("Entrer votre mot de passe : "); // get a password
    index = 0;
    char stock_password[30];
    while(password[index] != '\0'){
        stock_password[index] = password[index];
        stock_password[index+1] = '\0';
        index++;
    }
    passwordbis = getpass("confirmez votre mot de passe : "); // get a password
    compare = compare_char(stock_password,passwordbis);
    if (condition(ndc,"Nom de compte") || condition(passwordbis,"Mot de passe")){
        printf("appuyez sur entrer pour continuer\n");
        getchar();
        system("clear");
        goto A;
    }
    if (!compare){
        printf("\nErreur : mot de passe non similaire\n\n");
        printf("appuyez sur entrer pour continuer\n");
        getchar();
        system("clear");
        goto A;
    }
    stocker_id_mdp_inscription(ndc, stock_password);
    system("clear");
    printf("Vous vous êtes inscrit !\nSous le pseudo : %s\n", ndc);
    printf("\nappuyez sur entrer pour continuer\n");

    getchar();
    menu_accueil();
}

/*-----------------------SIGNIN-----------------------*/

void menu_signin(char **ndc){
    bool verif;
    char ch;
    char *NDC = malloc(sizeof(char)*30);
    char *password; // password string pointer
    char *password_check;
    int i;
    error_signin:
    printf("Entrez votre nom de compte : ");
    ch = getchar();
    i=0;
    while ( ch != 10 ){
        NDC[i] = ch;
        ch = getchar();
        i++;
    }
    NDC[i] = '\0';
    password = getpass("Enter votre mot de passe : "); // get a password
    //verifier nom de compte et mot de passe
    chercher_mdp(NDC,&password_check);
    verif = compare_char(password_check,password);
    if (condition(NDC,"Nom de compte") || condition(password,"Mot de passe")){
        printf("appuyez sur entrer pour continuer\n");
        getchar();
        system("clear");
        goto error_signin;
    }
    if (!verif){
        printf("\nErreur : combinaison nom de compte et mot de passe erronée\n\n");
        printf("appuyez sur entrer pour continuer\n");
        getchar();
        system("clear");
        goto error_signin;
    }
    system("clear");
    *ndc = NDC;

}

bool compare_char(char *password,char *passwordbis){
    int j = 0;
    bool correct = true;

    while(!((password[j] != '\0' || passwordbis[j] != '\0') || correct == false)){
        if (password[j] != passwordbis[j]){
            correct = false;
        }
        j++;
    }
    return (correct && (strlen(passwordbis) == strlen(password)));
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
          menu_signin(&NDC);
      }else if (choix == 2){
          menu_signup();
      }else{
          printf("Erreur : tapez 1 ou 2 \n\n");
      }
  }while ((choix != 1 && choix != 2) || erreur == 1);
  if (compare_char(NDC,"admin")){
      menu_admin();
  }else{
      menu_user(&NDC);
  }

}

int lire_entier(int *a){
    int nb_lu;
    int nb_jete;
    int erreur = 0;

        nb_lu=scanf("%d",a);
        nb_jete=lire_fin_ligne();
        if (nb_lu != 1){
            printf("Erreur : veuillez entrez un entier\n\n");
            erreur = 1;
        }else if (nb_jete!=0){
            printf("Erreur : veuillez ne pas séparer votre chaine de caractère\n\n");
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

void menu_user(char **ndc){
    int choix;
    bool sorti = false;
    do {
        printf("menus : \n\n");
        printf("1 - Rechercher une ressource\n");
        printf("2 - Gestion des ressources\n");
        printf("3 - Quittez le programme\n\n");
        printf("%s, Choisissez : ",*ndc);
        lire_entier(&choix);
        switch (choix) {
            case 1:
                system("clear");
                system("sh script/afficheRessources.sh");
                //ressource
                goto texte;
            case 2:
                //modif mdp inscrits
                goto texte;
            case 3:
                sorti = true;
                break;
            default:
                printf("Erreur : Entrez un entier entre 1 et 3 !\n");
                texte:
                printf("appuyez sur entrer pour continuer\n");
                getchar();
                system("clear");
                break;
        }
    }while (!sorti);
}

void menu_admin(){
    bool sorti = false;
    int choix;
    do {
        printf("menus : \n\n");
        printf("1 - Afficher liste inscrit\n");
        printf("2 - Modifier le mot de passe d'un inscrit\n");
        printf("3 - Quittez le programme\n\n");
        printf("admin, Choisissez : ");
        lire_entier(&choix);
        switch (choix) {
            case 1:
                system("clear");
                printf("Liste des inscrits\n\n");
                system("grep \":\" json/Client.json | cut -f1 -d ':'");
                goto texte;
            case 2:
                //modif mdp inscrits
                break;
            case 3:
                sorti = true;
                break;
            default:
                printf("Erreur : Entrez un entier entre 1 et 3 !\n");
                texte:
                printf("\nappuyez sur entrer pour continuer\n");
                getchar();
                system("clear");
                break;
        }
    }while (!sorti);
}

bool condition(char *ndc, char *format){
    if (strlen(ndc) > 20 || strlen(ndc) < 2){
        printf("Erreur : %s doit être compris entre 2 et 20 caractères\n", format);
        return true;
    }
    return false;
}
