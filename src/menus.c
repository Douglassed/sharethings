#include "../include/menus.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


struct _menus {
    char* etoiles;
    char normal;
};

void monmenus(){
    printf("menus ok\n");
}

void menu_signin(){

    char NDC[100],ch;
    int i = 0;
    printf("Entrez votre nom de compte : ");
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
    password = getpass("Enter votre mot de passe : "); // get a password
    system("clear");
    printf("Vous etes : %s\n\n",ndc);
}

void menu_signup(){

}

void menu_accueil(){
    system("clear");

  printf(" ----------------------------\n");
  printf("|Bienvenue dans Sharethings !|\n");
  printf(" ----------------------------\n\n");
  printf("1 - Se connecter\n2 - S'inscrire\n\n")
  printf("choisissez : ");
  int choix;
  do{
      lire_entier(&choix);
      if (choix == 1){
          menu_signin();
      }else if (choix == 2){
          menu_signup();
      }else{
          printf("erreur : \n", );
      }
  }while (choix != 1 || choix != 2);


}

void lire_entier(int *a){
    int nb_lu;
    int nb_jete;
    do{
        nb_lu=scanf("%d",a);
        nb_jete=lire_fin_ligne();
        if ((nb_jete!=0) || (nb_lu!=1)){
            printf("erreur recommencer\n");
        }
    }while((nb_jete!=0) || (nb_lu!=1));
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
