#include "../include/menus.h"
#include "../include/json.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

// debut

int menu_signup(char * modif){
    /* déclaration des variables */
    bool compare;
    char NDC[30],ch;
    char *ndc = malloc(sizeof(char)*30);
    char *password; // password string pointer
    int i;
    int index;
    char *passwordbis; // password string pointer

    /* stockage du nom de compte */
    i = 0;
    if (modif == " "){
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
            printf("appuyez sur entrer pour continuer\n");
            getchar();
            system("clear");
            return 1;
        }
    }else{
        while (modif[i] != '\0'){
            ndc[i] = modif[i];
            i++;
        }
        ndc[i] = '\0';
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
        return 1;
    }

    /* vérification de la similitude des mots de passe et gestion erreur */
    if (!compare){
        printf("\nErreur : mot de passe non similaire\n\n");
        printf("appuyez sur entrer pour continuer\n");
        getchar();
        system("clear");
        return 1;
    }

    /* message de finalisation */
    stocker_id_mdp_inscription(ndc, stock_password);
    system("clear");
        if (modif == " "){
        printf("Vous vous êtes inscrit !\nSous le pseudo : %s\n", ndc);
        printf("\nappuyez sur entrer pour continuer\n");
        getchar();
    }
    return 0;
}

/*-------------------------------------------------------------------------*/

int menu_signin(char **ndc){
    /* déclaration des variables */
    bool verif;
    char ch;
    char *NDC = malloc(sizeof(char)*30);
    char *password; // password string pointer
    char *password_check;
    int i;

    /* récuperation du nom de compte */
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
    password = getpass("Entrez votre mot de passe : "); // get a password

    /* test de l'exactitude du mot de passe */
    chercher_mdp(NDC,&password_check);
    verif = compare_char(password_check,password);

    if (!verif){
        printf("\nErreur : combinaison nom de compte et mot de passe erronée\n\n");
        printf("appuyez sur entrer pour continuer\n");
        getchar();
        system("clear");
        return 1;
    }
    system("clear");
    *ndc = NDC;
    return 0;

}

/*-------------------------------------------------------------------------*/

bool compare_char(char *password,char *passwordbis){
    /* déclaration */
    int j = 0;
    bool correct = true;

    /* test de la similitude des mots de passe */
    while(password[j] != '\0' && passwordbis[j] != '\0' ){
        if (password[j] != passwordbis[j]){
            correct = false;
        }
        j++;
    }
    if (correct && (strlen(passwordbis) == strlen(password))){
        return true;
    }
    return false;
}

/*-------------------------------------------------------------------------*/

void menu_accueil(){
    /* déclaration */
    int restart;
    int choix;
    char *NDC;

    /* affichage du menu d'accueil */
    do{
        system("clear");
        printf(" ----------------------------\n");
        printf("|Bienvenue dans Sharethings !|\n");
        printf(" ----------------------------\n\n");
        printf("| 1 | - Se connecter\n| 2 | - S'inscrire\n\n");
        printf("choisissez : ");
        restart = lire_entier(&choix, 1, 2);
      if (choix == 1){
          restart = menu_signin(&NDC);
      }else if (choix == 2){
          menu_signup(" ");
          restart = 1;
      }else{
          printf("Erreur : tapez 1 ou 2 \n\n");
          printf("appuyez sur entrer pour continuer\n");
          getchar();
          system("clear");
      }
  } while ((choix != 1 && choix != 2) || restart == 1);

  /* accès menu admin ou utilisateur*/
  if (compare_char(NDC,"admin")){
      menu_admin();
  } else {
      menu_user(&NDC);
  }

}

/*-------------------------------------------------------------------------*/

int lire_entier(int *a,int min, int max){
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
        *a = -1;
    }else if (nb_jete!=0){
        printf("\nErreur : veuillez ne pas séparer votre chaine de caractère\n\n");
        erreur = 1;
        *a = -1;
    }else if (max != 0 && (*a < min || *a > max)){
        printf("\nErreur : Entrez un entier entre %d et %d compris !\n", min, max);
        erreur = 1;
        *a = -1;
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
    bool sortir = false;
    /* affichage du menu utilisateur et choix de l'action */
    A:
    do {
        printf("menus : \n\n");
        printf("1 - Rechercher une ressource\n");
        printf("2 - Gestion des ressources\n");
        printf("3 - Supprimer son compte\n");
        printf("4 - Modifier son mot de passe\n");
        printf("5 - Quittez le programme\n\n");
        printf("%s, Choisissez : ",*ndc);
        lire_entier(&choix, 1, 5);
        switch (choix) {
            case 1:
                system("clear");
                system("sh script/afficheRessources.sh");
                break;
            case 2:
                // Gestion des ressources
                break;
            case 3:
                if (verification()){
                    admin_del_someone(num_id(*ndc));
                    printf("Le compte %s a été supprimer avec succès\n", *ndc);
                    printf("\nVous allez quitter le programme\n");
                    sortir = true;
                }
                break;
            case 4:
                system("clear");
                printf("Nouveau mot de passe : \n\n");
                admin_del_someone(num_id(*ndc));
                while (menu_signup(*ndc) == 1);
                system("clear");
                printf("Mot de passe enregistré !\n");
                break;
            case 5:
                sortir = true;
                break;
            default:
                break;
        }
        if (!sortir){
            printf("\nappuyez sur entrer pour continuer\n");
            getchar();
            system("clear");
        }
    }while (sortir == false);
    LEAVE:
    system("clear");
    printf("Aurevoir %s, et a bientot sur Sharethings :p\n", *ndc);
    getchar();
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
        printf("1 - Modifier un inscrit\n");
        printf("2 - Quittez le programme\n\n");
        printf("admin, Choisissez : ");
        lire_entier(&choix, 1, 2);
        switch (choix) {
            case 1:
                system("clear");
                printf("Liste des inscrits :\n\n");
                printf("0:  Annuler\n\n");
                system("grep ':' json/Client.json | cut -f1 -d ':' | grep -n '\"' ");
                printf("\nchoisir l'inscrit à modifier : ");
                lire_entier(&choix_user, 0, 0);
                if (check_n_id_existe(choix_user)){
                    modif_user(choix_user);
                }
                goto texte;
            case 2:
                sorti = true;
                break;
            default:
                printf("Erreur : Entrez un entier entre 1 et 2 !\n");
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

void modif_user(int nbuser){
    /* déclaration */
    int choice;
    bool sorti = false;

    /* affcihe le menu modification d'un utilisateur */
    do{
        printf("pour ");
        system("clear");
        print_id(nbuser);
        printf(" :\n\n");
        printf("1 - modifier le mot de passe\n");
        printf("2 - Supprimer le compte\n");
        printf("3 - Annuler\n");
        printf("\nChoix : ");

        /* gestion du choix */
        lire_entier(&choice, 1, 3);
        switch (choice) {
            case 1:
                //modif mdp
                sorti = true;
            case 2:
                if (verification()){
                    print_id(nbuser);
                    admin_del_someone(nbuser);
                    printf(" a été supprimer\n");
                    sorti = true;
                }
                break;
            case 3:
                sorti = true;
                break;
            default:
                printf("Erreur : Entrez un entier entre 1 et 3 !\n");
                printf("\nappuyez sur entrer pour continuer\n");
                getchar();
                system("clear");
                break;
        }
    } while (!sorti);
}

/*-------------------------------------------------------------------------*/

bool verification(void){
    int verif;
    verif:
    system("clear");
    printf("Êtes vous sur ? \n\n");
    printf("1 - Oui \n");
    printf("2 - Non \n");
    printf("\nChoix : ");
    if (lire_entier(&verif, 1, 2)){
        printf("\nappuyez sur entrer pour continuer\n");
        getchar();
        system("clear");
        goto verif;
    }else if (verif == 1){
        system("clear");
        return true;
    }else {
        system("clear");
        return false;
    }

}
