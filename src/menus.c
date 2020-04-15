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

    /* vérification de la taille du mot de passe */
    if (condition(ndc,"Nom de compte") || condition(password,"Mot de passe")){
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
    int restart = 1;
    int choix;
    char *NDC;
    bool leave = false;

    /* affichage du menu d'accueil */
    do{
        system("clear");
        printf(" ----------------------------\n");
        printf("|Bienvenue dans Sharethings !|\n");
        printf(" ----------------------------\n\n");
        printf("| 1 | - Se connecter\n| 2 | - S'inscrire\n| 3 | - Quittez\n\n");
        printf("choisissez : ");
        restart = lire_entier(&choix, 1, 3);
        switch (choix) {
            case 1:
                restart = menu_signin(&NDC);
                break;
            case 2:
                menu_signup(" ");
                restart = 1;
                break;
            case 3:
                leave = true;

                break;
            default:
                break;
        }
  } while (restart == 1);

  /* accès menu admin ou utilisateur*/
  if (compare_char(NDC,"admin")){
      menu_admin();
  } else if (!leave){
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
    }else if (max != 0 && (*a < min || *a > max)){
        printf("\nErreur : Entrez un entier entre %d et %d compris !\n", min, max);
        erreur = 1;
        *a = -1;
    }else if (*a < min){
        printf("\nErreur : Entrez un entier supérieur à %d compris !\n", min);
        erreur = 1;
        *a = -1;
    }
    if (nb_jete!=0){
        printf("\nErreur : veuillez ne pas séparer votre chaine de caractère\n\n");
        erreur = 1;
        *a = -1;
    }
    if (erreur == 1){
        getchar();
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
        res=res+1;

    }
    return res;
}

/*-------------------------------------------------------------------------*/

void menu_user(char **ndc){
    /* déclaration */
    char* cat;
    int choix;
    bool sortir = false;
    /* affichage du menu utilisateur et choix de l'action */
    do {
        system("clear");
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
                menu_affiche_ress(1,&cat,*ndc);
                break;
            case 2:
                menu_gestion_ress(ndc);
                break;
            case 3:
                if (verification()){
                    admin_del_someone(num_id(*ndc));
                    printf("Le compte %s a été supprimer avec succès\n", *ndc);
                    printf("\nVous allez quitter le programme\n");
                    printf("\nappuyez sur entrer pour continuer\n");
                    getchar();
                    sortir = true;
                }
                break;
            case 4:
                if (verification()){
                    system("clear");
                    printf("Nouveau mot de passe : (Ne quittez pas le programe !) \n\n");
                    admin_del_someone(num_id(*ndc));
                    while (menu_signup(*ndc) == 1);
                    system("clear");
                    printf("Mot de passe enregistré !\n");
                    printf("\nappuyez sur entrer pour continuer\n");
                    getchar();
                    system("clear");
                }
                break;
            case 5:
                sortir = true;
                break;
            default:
                break;
        }
        if (choix != 1 && choix != 5){

        }
    }while (sortir == false);
    system("clear");
    printf("\nAurevoir %s, et a bientot sur Sharethings :p\n\n", *ndc);
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
                system("grep ':' json/Client.json | cut -f1 -d ':' | tail +2 | grep -n '\"' ");
                printf("\nchoisir l'inscrit à modifier : ");
                lire_entier(&choix_user, 0, 0);
                if (check_n_id_existe(choix_user + 1) && choix_user != 0){
                    modif_user(choix_user + 1);
                }
                break;
            case 2:
                sorti = true;
                break;
            default:
                break;
        }
        printf("\nappuyez sur entrer pour continuer\n");
        getchar();
        system("clear");
    }while (!sorti);
}

/*-------------------------------------------------------------------------*/

bool condition(char *ndc, char *format){
    /* test de la taille de la chaîne de caractère */
    if (strlen(ndc) > 20 || strlen(ndc) < 2){
        printf("\nErreur : %s doit être compris entre 2 et 20 caractères\n", format);
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
        printf("1 - Supprimer le compte\n");
        printf("2 - Annuler\n");
        printf("\nChoix : ");

        /* gestion du choix */
        lire_entier(&choice, 1, 2);
        switch (choice) {
            case 1:
                if (verification()){
                    print_id(nbuser);
                    admin_del_someone(nbuser);
                    printf(" a été supprimer\n");
                    sorti = true;
                }
                break;
            case 2:
                sorti = true;
                break;
            default:
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
        goto verif;
    }else if (verif == 1){
        system("clear");
        return true;
    }else {
        system("clear");
        return false;
    }
}

/*-------------------------------------------------------------------------*/

void menu_recherche_specifique(char *obj, char* id){
  int choix;
  bool sorti = false;
  do {
      printf("Choisissez un objet par son numéro pour plus de détails :\n\n");
      printf("0. Retour\n\n");
      afficher_liste_obj(obj);
      printf("\nChoisissez : ");
      if (!lire_entier(&choix,0,0)){
          system("clear");
      }
      if (choix != 0){
          afficher_detail_obj(obj, choix);
          printf("\nappuyez sur entrer pour continuer\n");
          getchar();
          system("clear");
      }else{
          sorti = true;
      }
  }while (!sorti);
}

/*-------------------------------------------------------------------------*/

int menu_affiche_ress(int fonction, char** cat, char* id){
  /* déclaration */
  int choix;
  bool sorti = false;
  int ligne = 0;
  /* affichage du menu et choix de l'action */
  do {
      system("clear");
      printf("Choisissez la catégorie de l'objet : \n\n");
      printf("0 - Retour\n\n");
      printf("1 - Livre\n");
      printf("2 - Electronique\n");
      printf("3 - Outil\n\n");
      printf("Choisissez : ");
      //printf("%s, Choisissez : ",*ndc);
      lire_entier(&choix, 0, 3);
      system("clear");
      switch (choix) {
          case 0:
              sorti=true;
              break;
          case 1:
              *cat = "livre";
              break;
          case 2:
              *cat = "electronique";
              break;
          case 3:
              *cat = "outil";
              break;

          default:
            break;
      }
      if (!sorti && fonction == 1){
          menu_recherche_specifique(*cat,id);
      }
      if (!sorti && fonction == 2){
          sorti = true;
      }

  }while (sorti == false);
  return choix;
}


void menu_gestion_ress(char** id){
  /* déclaration */
  int choix;
  bool sorti = false;

  /* affichage du menu et choix de l'action */
  do {
      system("clear");
      printf("Gestion de mes ressources : \n\n");
      printf("0 - Retour\n\n");
      printf("1 - Ajouter une ressource\n");
      printf("2 - Modifier/Supprimer mes ressource\n");
      printf("3 - Ressources empruntées\n");
      printf("4 - Mon historique\n");

      printf("\nChoisissez, %s : ",*id);
      //printf("%s, Choisissez : ",*ndc);
      lire_entier(&choix, 0, 4);
      system("clear");
      switch (choix) {
          case 0:
              sorti = true;
              break;
          case 1:
              ajout_ress(id);
              break;
          case 2:
              modif_ress(id);
              break;
          case 3:
              //ressource
              break;
          case 4 :
              //history
              break;
          default:
            break;
      }


  }while (sorti == false);
}

int ajout_ress(char** id){
    char description[250];
    char name[60];
    char* cat;
    // argu 1
    int lignecat = ligne_bonne_categorie(menu_affiche_ress(2,&cat,*id)) + 2;
    system("clear");
    if (lignecat == 0){
        return 1;
    }
    //argu 4
    system("clear");
    printf("Entrez le nom de l'objet : \n(Entrer pour valider, 50 caractères maximum, 2 mini)\n");
    printf("\nNom de l'objet : ");
    char cha = getchar();
    int j = 0;
    while ( cha != 10 && j < 50 ){
        name[j] = cha;
        cha = getchar();
        j++;
        name[j] = '\0';
    }
    if (j >= 50 || j < 3){
        lire_fin_ligne();
        system("clear");
        printf("Format non respécté\n");
        printf("\nAppuyez sur entrer pour continuer\n");
        getchar();
        return 1;
    }

    //argu 3
    printf("\nEntrez la description de l'objet : \n(Entrer pour valider, 200 caractères maximum, 2 mini)\n");
    printf("\nDescription : ");
    char ch = getchar();
    int i = 0;
    while ( ch != 10 && i < 201 ){
        description[i] = ch;
        ch = getchar();
        i++;
        description[i] = '\0';
    }
    if (i >= 201 || i < 3){
        lire_fin_ligne();
        system("clear");
        printf("Format non respécté\n");
        getchar();
        return 1;
    }

    if (strlen(description) > 2 && strlen(name) > 2){
        add_ressource(lignecat, *id, description, name, ".");
        return 0;
    }
    return 1;
}

int modif_ress(char **id){
    char* cat;
    char* sauvobj;
    char* sauvdes;
    int choixobj;
    int choixnd;
    int nb_obj;
    int choix = menu_affiche_ress(2,&cat,*id);
    if (choix == 0){
        return 0;
    }
    printf("Vos objets :\n\n");
    printf("0. Retour\n\n");
    nb_obj = afficher_liste_obj_du_proprio(cat,*id);
    if (nb_obj == 0){
        system("clear");
        printf("Vous n'avez aucun objet dans la categorie %s\n", cat);
        printf("\nAppuyez sur entrer pour continuer");
        getchar();
        return 0;
    }
    printf("\nChoisissez : ");
    if(lire_entier(&choixobj,0,nb_obj) || choixobj == 0){
        return 0;
    }
    afficher_choix_obj_du_proprio(cat, *id, choixobj, &sauvobj);
    afficher_choix_desc_du_proprio(cat,*id, choixobj, &sauvdes);

    //sauvegarder_detail_obj(cat, choixobj, 2, &sauvdes);
    system("clear");
    printf("Modifier :\n\n");
    printf("0. Annuler\n\n");
    printf("1. Nom : %s\n\n",sauvobj );
    printf("2. Description : %s\n\n",sauvdes);
    printf("3. Supprimer\n");
    printf("\nChoisissez : ");
    lire_entier(&choixnd,0,3);
    system("clear");
    if (choixnd == 1 || choixnd == 2){
        modif_ressource_sauf_pret(choix, *id, sauvobj, choixnd);

    }
    if (choixnd == 3 && verification()){
        del_ressource(ligne_bon_obj(choix, *id, sauvobj));
    }
}
