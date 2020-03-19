#include "../include/menus.h"
#include "../include/json.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

void menu_signup(){
    /* déclaration des variables */
    bool compare;
    char NDC[30],ch;
    char *ndc = malloc(sizeof(char)*30);
    char *password; // password string pointer
    int i;
    int index;
    char *passwordbis; // password string pointer

    /* stockage du nom de compte */
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

    /* vérification de l'existance du com de compte */
    if (existe_id(ndc)){
        printf("Erreur : Nom de compte déjà existant\n");
        getchar();
        system("clear");
        goto A;
    }
    /* stockage du mot de passe */
    password = getpass("Entrer votre mot de passe : "); // get a password
    index = 0;
    char stock_password[30];
    while(password[index] != '\0'){
        stock_password[index] = password[index];
        stock_password[index+1] = '\0';
        index++;
    }

    /* stockage de la verification du mot de passe */
    passwordbis = getpass("confirmez votre mot de passe : "); // récuperation du mot de passe
    compare = compare_char(stock_password,passwordbis); //comparation des mots de passe

    /* vérification de la taille du mot de passe */
    if (condition(ndc,"Nom de compte") || condition(passwordbis,"Mot de passe")){
        printf("appuyez sur entrer pour continuer\n");
        getchar();
        system("clear");
        goto A;
    }

    /* vérification de la similitude des mots de passe et gestion erreur */
    if (!compare){
        printf("\nErreur : mot de passe non similaire\n\n");
        printf("appuyez sur entrer pour continuer\n");
        getchar();
        system("clear");
        goto A;
    }

    /* message de finalisation */
    stocker_id_mdp_inscription(ndc, stock_password);
    system("clear");
    printf("Vous vous êtes inscrit !\nSous le pseudo : %s\n", ndc);
    printf("\nappuyez sur entrer pour continuer\n");
    getchar();
    menu_accueil();
}

/*-------------------------------------------------------------------------*/

void menu_signin(char **ndc){
    /* déclaration des variables */
    bool verif;
    char ch;
    char *NDC = malloc(sizeof(char)*30);
    char *password; // password string pointer
    char *password_check;
    int i;

    /* récuperation du nom de compte */
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

    /* récuperation du mot de passe */
    password = getpass("Enter votre mot de passe : "); // get a password

    /* test de l'exactitude du mot de passe */
    chercher_mdp(NDC,&password_check);
    verif = compare_char(password_check,password);
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

/*-------------------------------------------------------------------------*/

bool compare_char(char *password,char *passwordbis){
    /* déclaration */
    int j = 0;
    bool correct = true;

    /* test de la similitude des mots de passe */
    while(!((password[j] != '\0' || passwordbis[j] != '\0') || correct == false)){
        if (password[j] != passwordbis[j]){
            correct = false;
        }
        j++;
    }
    return (correct && (strlen(passwordbis) == strlen(password)));
}

/*-------------------------------------------------------------------------*/

void menu_accueil(){
    /* déclaration */
    int erreur;
    int choix;
    char *NDC;
    system("clear");

    /* affichage du menu d'accueil */
    do{
        printf(" ----------------------------\n");
        printf("|Bienvenue dans Sharethings !|\n");
        printf(" ----------------------------\n\n");
        printf("| 1 | - Se connecter\n| 2 | - S'inscrire\n\n");
        printf("choisissez : ");
        erreur = lire_entier(&choix);
      if (choix == 1){
          menu_signin(&NDC);
      }else if (choix == 2){
          menu_signup();
      }else{
          printf("Erreur : tapez 1 ou 2 \n\n");
          printf("appuyez sur entrer pour continuer\n");
          getchar();
          system("clear");
      }
  } while ((choix != 1 && choix != 2) || erreur == 1);

  /* accès menu admin ou utilisateur*/
  if (compare_char(NDC,"admin")){
      menu_admin();
  } else {
      menu_user(&NDC);
  }

}

/*-------------------------------------------------------------------------*/

int lire_entier(int *a){
    /* déclaration */
    int nb_lu;
    int nb_jete;
    int erreur = 0;

    /* test fiabilité de la variable */
    nb_lu=scanf("%d",a);
    nb_jete=lire_fin_ligne();
    if (nb_lu != 1){
        printf("\nErreur : veuillez entrez un entier\n\n");
        erreur = 1;
    }else if (nb_jete!=0){
        printf("Erreur : veuillez ne pas séparer votre chaine de caractère\n\n");
        erreur = 1;
    }
    return erreur;
}

/*-------------------------------------------------------------------------*/

int lire_fin_ligne (){
    /* déclaration */
    char c;
    int res=0;
    /* vide le buffer */
    c=getchar();
    while ((c!= EOF) && (c!= '\n')){
        c=getchar();
        if (!isspace(c)){
            res=res+1;
        }

    }
    return res;
}

/*-------------------------------------------------------------------------*/

void menu_user(char **ndc){
    /* déclaration */
    int choix;
    bool sorti = false;

    /* affichage du menu utilisateur et choix de l'action */
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

/*-------------------------------------------------------------------------*/

void menu_admin(){
    /* déclaration */
    bool sorti = false;
    int choix;
    int choix_user;

    /* affichage du menu admin et choix de l'action */
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
                printf("Liste des inscrits :\n\n");
                system("grep ':' json/Client.json | cut -f1 -d ':' | grep -n '\"' ");
                printf("choisir l'inscrit à modifier :");
                lire_entier(&choix_user);

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

/*-------------------------------------------------------------------------*/

bool condition(char *ndc, char *format){
    /* test de la taille de la chaîne de caractère */
    if (strlen(ndc) > 20 || strlen(ndc) < 2){
        printf("Erreur : %s doit être compris entre 2 et 20 caractères\n", format);
        return true;
    }
    return false;
}

/*-------------------------------------------------------------------------*/

void modif_user(int choix){
    /* déclaration */
    int jsp;
    //thomas : affiche le user : choix
    printf("1 - modifier le mot de passe\n");
    printf("2 - Supprimer le compte\n");
    printf("3 - Annuler\n");




}
