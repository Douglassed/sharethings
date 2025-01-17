#include <stdio.h>
#include <stdlib.h>
#include "../include/json.h"
#include <json-c/json.h>
#include <string.h>
#include <stdbool.h>


void afficher_liste_obj_raw(char *obj){
  FILE *fic;
  char buffer[1024];

  struct json_object *parsed_json;
  struct json_object *liste_objet;
  struct json_object *objet;
  size_t n_obj;
  size_t i;

  fic = fopen("./json/Json.json","r");
  fread(buffer, 1024, 1, fic);
  fclose(fic);

  parsed_json = json_tokener_parse(buffer);

  json_object_object_get_ex(parsed_json, obj, &liste_objet);//changer "vert" en variable à choisir ici obj

  n_obj = json_object_array_length(liste_objet);
  printf("\n\nFound %lu %s(s)\n",n_obj, obj);

  for(i=0;i<n_obj;i++) {
    objet = json_object_array_get_idx(liste_objet, i);
    printf("%lu. %s\n",i+1,json_object_get_string(objet));
  }
}
//Exemple d'utilisation:
//char *objet = "livre";
//afficher_liste_obj_raw(objet);

/*-------------------------------------------------------------------------*/
void afficher_detail_obj(char *obj, int choix){
  struct json_object *o_obj, *o_array, *o_array_obj, *o_array_obj_name;
  int arraylen, j;
  static const char filename[] = "./json/Json.json";
  o_obj = json_object_from_file(filename);
  o_array = json_object_object_get(o_obj, obj);//changer "vert" en objet à choisir ici obj

  // o_array is an array of objects
  arraylen = json_object_array_length(o_array);

  choix = choix-1;

  for (j = 0; j < arraylen; j++) {
    if(choix==j){
      // get the i-th object in o_array
      o_array_obj = json_object_array_get_idx(o_array, j);
      // get the name attribute in the i-th object
      o_array_obj_name = json_object_object_get(o_array_obj, "Name");//changer "vert" en détail à choisir
      // print out the name attribute
      printf("Name : %s\n",json_object_get_string(o_array_obj_name));
      o_array_obj_name = json_object_object_get(o_array_obj, "Description");//changer "vert" en détail à choisir
      printf("Description : %s\n",json_object_get_string(o_array_obj_name));
      o_array_obj_name = json_object_object_get(o_array_obj, "En cours de pret");//changer "vert" en détail à choisir
      if(strcmp(json_object_get_string(o_array_obj_name),".")!=0)
        printf("En cours de pret : %s\n",json_object_get_string(o_array_obj_name));
      o_array_obj_name = json_object_object_get(o_array_obj, "Proprietaire");//changer "vert" en détail à choisir
      printf("Proprietaire : %s\n",json_object_get_string(o_array_obj_name));
    }
  }
}
//Exemple d'utilisation:
//char *objet = "livre";
//int choix = 3;
//afficher_liste_obj(objet);
//afficher_detail_obj(objet, choix);

/*-------------------------------------------------------------------------*/

int afficher_liste_obj(char *obj){
  struct json_object *o_obj, *o_array, *o_array_obj, *o_array_obj_name;
  int arraylen, j;
  static const char filename[] = "./json/Json.json";
  o_obj = json_object_from_file(filename);
  o_array = json_object_object_get(o_obj, obj);//changer "vert" en objet à choisir ici obj

  // o_array is an array of objects
  arraylen = json_object_array_length(o_array);
  int a;

  for (j = 0; j < arraylen; j++) {
    // get the i-th object in o_array
    o_array_obj = json_object_array_get_idx(o_array, j);
    // get the name attribute in the i-th object
    o_array_obj_name = json_object_object_get(o_array_obj, "Name");//changer "vert" en détail à choisir
    // print out the name attribute
    printf("%d. %s",j+1,json_object_get_string(o_array_obj_name));
    o_array_obj_name = json_object_object_get(o_array_obj, "En cours de pret");
    int a = savoir_si_en_pret(obj, j+1);
    if(a==1)
      printf("  (Indisponible)\n");
    else
      printf("\n");
  }
  return arraylen;
}
//Exemple d'utilisation:
//char *objet = "livre";
//afficher_liste_obj(objet);

/*-------------------------------------------------------------------------*/

void chercher_mdp(char *iD, char ** p){
    FILE *fic;
	  char buffer[1024];
	  struct json_object *parsed_json;
	  struct json_object *mdp;

	  fic = fopen("./json/Client.json","r");
	  fread(buffer, 1024, 1, fic);
	  fclose(fic);

	  parsed_json = json_tokener_parse(buffer);

	  json_object_object_get_ex(parsed_json, iD, &mdp);
    if (json_object_get_string(mdp) == NULL)
      *p = "\0";
    else
      *p = (json_object_get_string(mdp));

	  //printf("Le MDP est %s\n", json_object_get_string(mdp));
  }
//Exemple d'utilisation:
//char *id = "Cleement";
//char *MDP = "basique";
//afficher_mdp(id, &MDP);
//printf("%s\n", MDP);

/*-------------------------------------------------------------------------*/

bool existe_id(char *iD){
    FILE *fic;
	  char buffer[1024];
	  struct json_object *parsed_json;
	  struct json_object *mdp;

	  fic = fopen("./json/Client.json","r");
	  fread(buffer, 1024, 1, fic);
	  fclose(fic);

	  parsed_json = json_tokener_parse(buffer);

	  json_object_object_get_ex(parsed_json, iD, &mdp);
    if (json_object_get_string(mdp) == NULL)
    {
      //printf("L'ID n'existe pas");
      return(false);
    }
    else
    {
      //printf("L'ID existe");
      return(true);
    }
  }
//Exemple d'utilisation:
//char *Id = "Cleeement";
//bool ok = existe_id(Id);

/*-------------------------------------------------------------------------*/

void stocker_id_mdp_inscription(char *iD, int mdp){
    FILE *fic = fopen("./json/Client.json", "r+");

    fseek(fic, -3, SEEK_END);

    fputs(",\n  \"", fic);
    fputs(iD, fic);
    fputs("\": \"", fic);
    char b[12];
    sprintf(b, "%d", mdp);//conversion int en string
    fputs(b, fic);
    fputs("\"\n}\n", fic);

    fclose(fic);
  }
//Exemple d'utilisation:
//char *i = "New";
//int = 156458;
//stocker_id_mdp_inscription(i, m);

/*-------------------------------------------------------------------------*/

void modifier_fichier_base_proto(){ //ne sert a rien, sert de base, schema pour autre fonction
  /* Open the file for reading and the other to write */
  char *line_buf = NULL;
  size_t line_buf_size = 0;
  int line_count = 0;
  ssize_t line_size;
  FILE *fp = fopen("./json/Client.json", "r");
  FILE *fic2 = fopen("./json/Client2.json", "w");
  /*if (!fp)
  {
    fprintf(stderr, "Error opening file '%s'\n", "./json/Client.json");
    return EXIT_FAILURE;
  }*/

  /* Get the first line of the file. */
  line_size = getline(&line_buf, &line_buf_size, fp);

  /* Loop through until we are done with the file. */
  while (line_size >= 0)
  {
    /* Increment our line count */
    line_count++;

    /* Show the line details and printing them into the second file */
    printf("Contents: %s", line_buf);
    fputs(line_buf, fic2);

    /* Get the next line */
    line_size = getline(&line_buf, &line_buf_size, fp);
  }

  /* Free the allocated line buffer */
  free(line_buf);
  //line_buf = NULL;

  /* Close files now that we are done with */
  fclose(fp);
  fclose(fic2);
}
//Exemple d'utilisation:
//modifier_fichier();

/*-------------------------------------------------------------------------*/

void admin_del_someone(int choix){
  /* Open the file for reading and the other to write */
  char *line_buf = NULL;
  size_t line_buf_size = 0;
  int line_count = 0;
  ssize_t line_size;
  FILE *fp = fopen("./json/Client.json", "r");
  FILE *fic2 = fopen("./json/Client2.json", "w");

  /* Get the first line of the file. */
  line_size = getline(&line_buf, &line_buf_size, fp);

  /* Loop through until we are done with the file. */
  while (line_size >= 0)
  {
    /* Increment our line count */
    line_count++;

    /* Show the line details and printing them into the second file */
    //printf("Contents: %s", line_buf);
    if(line_count!=(choix+1))
        fputs(line_buf, fic2);

    /* Get the next line */
    line_size = getline(&line_buf, &line_buf_size, fp);
  }

  /* Free the allocated line buffer */
  free(line_buf);

  /* Close files now that we are done with */
  fclose(fp);
  fclose(fic2);
  system("sh ./script/scriptVirgule.sh ./json/Client2.json");
  remove("./json/Client.json");
  rename("./json/Client2.json", "./json/Client.json");
}
//Exemple d'utilisation:
//admin_del_someone(7);

/*-------------------------------------------------------------------------*/

bool check_n_id_existe(int choix){
    /* Open the file for reading */
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    ssize_t line_size;
    FILE *fp = fopen("./json/Client.json", "r");

    /* Get the first line of the file. */
    line_size = getline(&line_buf, &line_buf_size, fp);

    /* Loop through until we are done with the file. */
    while (line_size >= 0)
    {
      line_count++;

      /* Get the next line */
      line_size = getline(&line_buf, &line_buf_size, fp);
    }

    /* Check choix autorisé */
    if(choix>=(line_count-1) || choix < 1){
      printf("\nChoix invalide\n");
      return(false);
    }
    else{
      return(true);
    }

    /* Free the allocated line buffer */
    free(line_buf);

    /* Close files now that we are done with */
    fclose(fp);
  }
//Exemple d'utilisation:
//check_n_id_existe(6);

/*-------------------------------------------------------------------------*/

void sauv_id(int choix, char **sauv){
  /* Open the file for reading */
  char *line_buf = NULL;
  size_t line_buf_size = 0;
  int line_count = 0;
  ssize_t line_size;
  FILE *fp = fopen("./json/Client.json", "r");

  /* Get the first line of the file. */
  line_size = getline(&line_buf, &line_buf_size, fp);

  /* Loop through until we are done with the file. */
  while (line_size >= 0)
  {
    line_count++;
  /* Printing the lane we want */
    if(line_count==(choix+1)){
      for(int i = 3; (line_buf[i])!= '"'; i++){
        printf("%c", line_buf[i]);
        sauv[0][i-3]=line_buf[i];
        sauv[0][i-2]='\0';
      }
    }
    /* Get the next line */
    line_size = getline(&line_buf, &line_buf_size, fp);
  }
  /* Free the allocated line buffer */
  free(line_buf);

  /* Close files now that we are done with */
  fclose(fp);
}
//Exemple d'utilisation:
//char *id = "NULL";
//sauv_id(5, id);

/*-------------------------------------------------------------------------*/


void print_id(int choix){
  /* Open the file for reading */
  char *line_buf = NULL;
  size_t line_buf_size = 0;
  int line_count = 0;
  ssize_t line_size;
  FILE *fp = fopen("./json/Client.json", "r");

  /* Get the first line of the file. */
  line_size = getline(&line_buf, &line_buf_size, fp);

  /* Loop through until we are done with the file. */
  while (line_size >= 0)
  {
    line_count++;
  /* Printing the lane we want */
    if(line_count==(choix+1)){
      for(int i = 3; (line_buf[i])!= '"'; i++){
        printf("%c", line_buf[i]);
      }
    }
    /* Get the next line */
    line_size = getline(&line_buf, &line_buf_size, fp);
  }

  /* Free the allocated line buffer */
  free(line_buf);

  /* Close files now that we are done with */
  fclose(fp);
}
//Exemple d'utilisation:
//print_id(5);


/*-------------------------------------------------------------------------*/

void fprint_id(int choix){
    /* Open the file for reading and the other to write */
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    ssize_t line_size;
    FILE *fp = fopen("./json/Client.json", "r");
    FILE *ft = fopen("temp.txt", "w");

    /* Get the first line of the file. */
    line_size = getline(&line_buf, &line_buf_size, fp);

    /* Loop through until we are done with the file. */
    while (line_size >= 0)
    {
      line_count++;
    /* Printing the lane */
      if(line_count==(choix+1)){
        for(int i = 3; (line_buf[i])!= '"'; i++)
          fputc(line_buf[i], ft);
      }
      /* Get the next line */
      line_size = getline(&line_buf, &line_buf_size, fp);
    }

    /* Free the allocated line buffer */
    free(line_buf);

    /* Close files now that we are done with */
    fclose(fp);
    fclose(ft);
  }
//Exemple d'utilisation:
//fprint_id(1);

/*-------------------------------------------------------------------------*/

int num_id(char* iD){
    FILE *ftp = fopen("temp.txt", "r");
    char lettre;
    bool check = false;
    int j;
    int i = 1;
    int position_curseur;
    A:
    while(check == false){
      FILE *ftp = fopen("temp.txt", "r");
      fprint_id(i);
      j = 0;
      check = true;

      fseek(ftp, 0, SEEK_END);
      position_curseur = ftell(ftp);
      fseek(ftp, 0, SEEK_SET);
      //printf("PC:%d\n", position_curseur);
      do{
        lettre = fgetc(ftp);
        //printf("%c", lettre);
        //printf("%c", iD[j]);
        if(lettre!=iD[j])
          check = false;
        j++;
      }while((iD[j]!='\0') && (check==true));
      //printf("\n");
      fclose(ftp);
      i++;
      if(position_curseur!=j){
        check = false;
        goto A;
      }
    }
    //printf("PC:%d J:%d final\n", position_curseur,j);
    //printf("%d\n", (i-1));
    remove("temp.txt");
    return(i-1);
  }
//Exemple d'utilisation:
//char *nom = "Lou";
//int a = num_id(nom);
//printf("%d\n", a);

/*-------------------------------------------------------------------------*/

int ligne_bonne_categorie(int choix){
    /* Open the file for reading */
    bool in_categorie;
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    ssize_t line_size;
    FILE *fp = fopen("./json/Json.json", "r");
    char *line_buf_check;
    int res;

    switch (choix) {
      case 1:
        line_buf_check = "  \"Livre\": [";
        break;
      case 2:
        line_buf_check = "  \"Informatique\": [";
        break;
      case 3:
        line_buf_check = "  \"Bricolage\": [";
        break;
      case 4:
        line_buf_check = "  \"Sport\": [";
        break;
      case 5:
        line_buf_check = "  \"Jouet\": [";
        break;
      case 6:
        line_buf_check = "  \"Cuisine\": [";
        break;
      case 7:
        line_buf_check = "  \"Autre\": [";
        break;
      case 8:
        line_buf_check ="  \"NULL\": [";
        break;
      default:
        break;
    }

    /* Get the first line of the file. */
    line_size = getline(&line_buf, &line_buf_size, fp);

    /* Loop through until we are done with the file. */
    while (line_size >= 0)
    {
      line_count++;
      /* Show the line details */
      //printf("Contents: %s", line_buf);
      in_categorie = true;
      for(int a = 0; line_buf_check[a]!='\0'; a++){
        if(line_buf[a]!=line_buf_check[a])
          in_categorie = false;
      }
      if(in_categorie==true)
        res = line_count;

      /* Get the next line */
      line_size = getline(&line_buf, &line_buf_size, fp);
    }

    /* Free the allocated line buffer */
    free(line_buf);

    /* Close files now that we are done with */
    fclose(fp);
    return res;
  }
//Exemple d'utilisation:
//int a = ligne_bonne_categorie(2);
//printf("%d\n",a); --> 16

/*-------------------------------------------------------------------------*/

int ligne_bon_obj(int num_cat, char *iD, char *Obj){
    /* Open the file for reading */
    bool in_categorie;
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    ssize_t line_size;
    FILE *fp = fopen("./json/Json.json", "r");
    char *line_buf_check;
    int bombe;
    int res;

    /*printf("C'est ça la taille de Obj: %ld.\n", strlen(Obj));
    char *mot_vide_obj = NULL;
    mot_vide_obj = malloc(sizeof(char) * 100);
    *mot_vide_obj = "      \"Name\": \"";//17
    char mot_vide_fin[3] = "\",";
    char *line_buf_check_tmp_obj = strcat(mot_vide_obj, Obj);
    char *line_buf_check_obj = strcat(line_buf_check_tmp_obj, mot_vide_fin);
    printf("%s\n",line_buf_check_obj);*/
    //printf("C'est ça la taille de Obj: %ld.\n", strlen(Obj));
    //char *line_buf_check_obj = NULL;
    char *mot_deb = "      \"Name\": \"";//17
    char *mot_fin = "\",\n";
    int Long = (strlen(mot_deb)+strlen(mot_fin)+strlen(Obj)+1);
    //printf("%d\n",Long);
    char *line_buf_check_obj = (char *)calloc(Long, sizeof(char));
    //printf("%s\n",line_buf_check_obj);
    strcat(line_buf_check_obj, mot_deb);
    strcat(line_buf_check_obj, Obj);
    strcat(line_buf_check_obj, mot_fin);
    //strcat(line_buf_check_obj, mot_0);
    //line_buf_check_obj[LONG]='\0';
    /*printf("1.C'est ça la taille de mot_deb: %ld.\n", strlen(mot_deb));
    printf("1.C'est ça la taille de mot_fin: %ld.\n", strlen(mot_fin));
    printf("1.C'est ça la taille de Obj: %ld.\n", strlen(Obj));
    printf("1.C'est ça la taille de line_buf_check_obj: %ld.\n", strlen(line_buf_check_obj));*/
    //printf("\n%s",line_buf_check_obj);


    //char *line_buf_check_iD = NULL;
    char *mot_deb2 = "      \"Proprietaire\": \"";//25
    char *mot_fin2 = "\"";
    char *mot_02 = "\n";
    int Long2 = (strlen(mot_deb2)+strlen(iD)+strlen(mot_fin2)+strlen(mot_02)+1);
    char *line_buf_check_iD = (char *)calloc(Long2, sizeof(char));
    /*printf("2.C'est ça la taille de mot_deb2: %ld.\n", strlen(mot_deb2));
    printf("2.C'est ça la taille de mot_fin2: %ld.\n", strlen(mot_fin2));
    printf("2.C'est ça la taille de iD: %ld.\n", strlen(iD));*/
    //printf("2.C'est ça la taille de line_buf_check_iD: %ld.\n\n", strlen(line_buf_check_iD));
    strcat(line_buf_check_iD, mot_deb2);
    //printf("Le check : %s\n\n", line_buf_check_iD);
    strcat(line_buf_check_iD, iD);
    strcat(line_buf_check_iD, mot_fin2);
    strcat(line_buf_check_iD, mot_02);
    //printf("%s", mot_fin2);
    //printf("%s\n", line_buf_check_iD);
    //printf("La lettre : %c", line_buf_check_iD[LONG2]);
    //line_buf_check_iD[Long2-1]='\"\0';
    //printf("2.C'est ça la taille de line_buf_check_iD: %ld.\n\n", strlen(line_buf_check_iD));
    //printf("%s\n",line_buf_check_obj);
    //printf("2.C'est ça la taille de line_buf_check_iD: %ld.\n\n", strlen(line_buf_check_iD));

    //printf("%s\n\n", line_buf_check_iD);
    //printf("%s\n\n", line_buf_check_obj);
    //printf("%s\n\n", line_buf_check_iD);

    switch (num_cat) {
      case 1:
        line_buf_check = "  \"Livre\": [";
        break;
      case 2:
        line_buf_check = "  \"Informatique\": [";
        break;
      case 3:
        line_buf_check = "  \"Bricolage\": [";
        break;
      case 4:
        line_buf_check = "  \"Sport\": [";
        break;
      case 5:
        line_buf_check = "  \"Jouet\": [";
        break;
      case 6:
        line_buf_check = "  \"Cuisine\": [";
        break;
      case 7:
        line_buf_check = "  \"Autre\": [";
        break;
      default:
        break;
    }

    /* Get the first line of the file. */
    line_size = getline(&line_buf, &line_buf_size, fp);

    /* Loop through until we are done with the file. */
    while (line_size >= 0)
    {
      line_count++;
      /* Show the line details */
      //printf("Contents: %s", line_buf);
      in_categorie = true;
      //printf("Line_buf_check :%s a\nLine_buf :%s a\n",line_buf_check, line_buf);
      for(int a = 0; line_buf_check[a]!='\0'; a++){
        if(line_buf[a]!=line_buf_check[a])
          in_categorie = false;
      }
      if(in_categorie==true){
        //printf("%d ", line_count);
        goto N;
      }

      /* Get the next line */
      line_size = getline(&line_buf, &line_buf_size, fp);
    }
/*----------*//*----------*//*----------*//*----------*//*----------*/
    N:
    line_size = getline(&line_buf, &line_buf_size, fp);

    /* Loop through until we are done with the file. */
    while (line_size >= 0)
    {
      line_count++;
      /* Show the line details */
      //printf("Contents: %s", line_buf);
      //printf("Line_buf_check_obj :%s.\nLine_buf :%s.\n",line_buf_check_obj, line_buf);
      in_categorie = true;
      for(int a = 0; line_buf_check_obj[a]!='\0'; a++){
        if(line_buf[a]!=line_buf_check_obj[a])
          in_categorie = false;
      }
      if(in_categorie==true){
        //printf("-%d-", line_count);
        goto ID;
      }

      /* Get the next line */
      line_size = getline(&line_buf, &line_buf_size, fp);
      //printf("Check-%d ",line_count);
    }
/*----------*//*----------*//*----------*//*----------*//*----------*/
    ID:
    bombe = 0;
    line_size = getline(&line_buf, &line_buf_size, fp);

    /* Loop through until we are done with the file. */
    while (line_size >= 0)
    {
      //printf("Line_buf_check_iD :%s\n",line_buf_check_iD);
      line_count++;
      /* Show the line details */
      //printf("Contents: %s", line_buf);
      in_categorie = true;
      for(int a = 0; line_buf_check_iD[a]!='\n'; a++){
        if(line_buf[a]!=line_buf_check_iD[a])
          in_categorie = false;
      }
      if(in_categorie==true){
        res = line_count;
        //printf(" \n---%d---\n\n",line_count);
      }
      bombe++;
      if(bombe == 3)
        goto N;

      /* Get the next line */
      line_size = getline(&line_buf, &line_buf_size, fp);
    }



    /* Close files now that we are done with */
    fclose(fp);
    /* Free the allocated buffers */
    free(line_buf);
    free(line_buf_check_obj);
    free(line_buf_check_iD);
    //printf("\n\n---%d---\n\n",line_count);
    return res;
  }
//Exemple d'utilisation:
//char *Name = "TourPC HP";
//char *iD = "Monsieur Durand";
//int a = ligne_bon_obj(2,iD,Name);
//printf("\n%d\n",a);

/*-------------------------------------------------------------------------*/

void del_ressource(int num_ligne){
  /* Open the file for reading and the other to write */
  char *line_buf = NULL;
  size_t line_buf_size = 0;
  int line_count = 0;
  ssize_t line_size;
  FILE *fp = fopen("./json/Json.json", "r");
  FILE *fic2 = fopen("./json/Jsonbis.json", "w");

  /* Get the first line of the file. */
  line_size = getline(&line_buf, &line_buf_size, fp);

  /* Loop through until we are done with the file. */
  while (line_size >= 0)
  {
    /* Increment our line count */
    line_count++;

    /* Show the line details and printing them into the second file */
    //printf("Contents: %s", line_buf);
    if(line_count!=(num_ligne+1) && line_count!=(num_ligne) && line_count!=(num_ligne-1) && line_count!=(num_ligne-2) && line_count!=(num_ligne-3) && line_count!=(num_ligne-4))
        fputs(line_buf, fic2);

    /* Get the next line */
    line_size = getline(&line_buf, &line_buf_size, fp);
  }

  /* Free the allocated line buffer */
  free(line_buf);

  /* Close files now that we are done with */
  fclose(fp);
  fclose(fic2);
  remove("./json/Json.json");
  rename("./json/Jsonbis.json", "./json/Json.json");
  }
//Exemple d'utilisation:
//del_ressource(a);

/*-------------------------------------------------------------------------*/

void add_ressource(int num_ligne_cat, char *iD, char *Descr, char *ObjName, char *nom_pret){
  /* Open the file for reading and the other to write */
  char *line_buf = NULL;
  size_t line_buf_size = 0;
  int line_count = 0;
  ssize_t line_size;
  char *Concat = NULL;
  char *Concat2 = NULL;
  char *Concat3 = NULL;
  char *Concat4 = NULL;
  char *mot_deb,*mot_deb2,*mot_deb3,*mot_deb4,*mot_fin,*mot_fin2,*mot_fin3,*mot_fin4 = NULL;
  FILE *fp = fopen("./json/Json.json", "r");
  FILE *fic2 = fopen("./json/Jsonbis.json", "w");

  /* Get the first line of the file. */
  line_size = getline(&line_buf, &line_buf_size, fp);

  /* Loop through until we are done with the file. */
  while (line_size >= 0)
  {
    /* Increment our line count */
    line_count++;

    /* Show the line details and printing them into the second file */
    if(line_count==num_ligne_cat-1){
      fputs("    {\n", fic2);

      char *mot_deb = "      \"Name\": \"";
      char *mot_fin = "\",\n";
      int Long = (strlen(mot_deb)+strlen(mot_fin)+strlen(ObjName)+1);
      Concat = calloc(Long, sizeof(char));
      strcat(Concat, mot_deb);
      strcat(Concat, ObjName);
      strcat(Concat, mot_fin);
      //printf("1.C'est ça la taille de Concat: %ld.\n", strlen(Concat));
      //printf("%s\n",Concat);
      fputs(Concat, fic2);
      free(Concat);

      char *mot_deb2 = "      \"Description\": \"";
      char *mot_fin2 = "\",\n";
      int Long2 = (strlen(mot_deb2)+strlen(mot_fin2)+strlen(Descr)+1);
      Concat2 = calloc(Long2, sizeof(char));
      strcat(Concat2, mot_deb2);
      strcat(Concat2, Descr);
      strcat(Concat2, mot_fin2);
      //printf("2.C'est ça la taille de Concat2: %ld.\n", strlen(Concat2));
      //printf("%s\n",Concat2);
      fputs(Concat2, fic2);
      free(Concat2);

      char *mot_deb3 = "      \"En cours de pret\": \"";
      char *mot_fin3 = "\",\n";
      int Long3 = (strlen(mot_deb3)+strlen(mot_fin3)+strlen(nom_pret)+1);
      Concat3 = calloc(Long3, sizeof(char));
      strcat(Concat3, mot_deb3);
      strcat(Concat3, nom_pret);
      strcat(Concat3, mot_fin3);
      //printf("3.C'est ça la taille de Concat3: %ld.\n", strlen(Concat3));
      //printf("%s\n",Concat3);
      fputs(Concat3, fic2);
      free(Concat3);

      char *mot_deb4 = "      \"Proprietaire\": \"";
      char *mot_fin4 = "\"\n";
      int Long4 = (strlen(mot_deb4)+strlen(mot_fin4)+strlen(iD)+1);
      Concat4 = calloc(Long4, sizeof(char));
      strcat(Concat4, mot_deb4);
      strcat(Concat4, iD);
      strcat(Concat4, mot_fin4);
      //printf("4.C'est ça la taille de Concat4: %ld.\n", strlen(Concat4));
      //printf("%s\n",Concat4);
      fputs(Concat4, fic2);
      free(Concat4);

      fputs("    },\n", fic2);
    }
    fputs(line_buf, fic2);

    /* Get the next line */
    line_size = getline(&line_buf, &line_buf_size, fp);
  }

  /* Free the allocated line buffer */
  free(line_buf);

  /* Close files now that we are done with */
  fclose(fp);
  fclose(fic2);
  remove("./json/Json.json");
  rename("./json/Jsonbis.json", "./json/Json.json");
  }
//Exemple d'utilisation:
//int n = 22;
//char *id = "John";
//char *pret = "KGB";
//char *des = "Voici une super BD";
//char *obj = "Asterix";
//add_ressource(n, id, des, obj, pret);

/*-------------------------------------------------------------------------*/

void sauvegarder_detail_obj(char *obj, int choix, int choix_modif, char **sauv){
    struct json_object *o_obj, *o_array, *o_array_obj, *o_array_obj_name;
    int arraylen, j;
    static const char filename[] = "./json/Json.json";
    o_obj = json_object_from_file(filename);
    o_array = json_object_object_get(o_obj, obj);

    // o_array is an array of objects
    arraylen = json_object_array_length(o_array);

    choix = choix-1;

    for (j = 0; j < arraylen; j++) {
      if(choix==j){
        // get the i-th object in o_array
        o_array_obj = json_object_array_get_idx(o_array, j);
        switch (choix_modif) {
          case 1:
            o_array_obj_name = json_object_object_get(o_array_obj, "Name");
            *sauv = json_object_get_string(o_array_obj_name);
            break;
          case 2:
            o_array_obj_name = json_object_object_get(o_array_obj, "Description");
            *sauv = json_object_get_string(o_array_obj_name);
            break;
          default:
            break;
        }
      }
    }
  }
//Exemple d'utilisation:
//char *objet = "livre";
//int choix_livre = 2;
//char *sauvegarde_detail;
//sauvegarder_detail_obj(objet, choix_livre,1,&sauvegarde_detail);
//printf("%s\n", sauvegarde_detail);

/*-------------------------------------------------------------------------*/

int quel_n_eme_obj(int l,int l_c){
    l=l-5;
    int i = 1;
    if(l==l_c)
      return 1;
    else{
      while(l!=l_c){
        l=l-6;
        i++;
      }
      return i;
    }
  }
//Exemple d'utilisation:
//int i = quel_n_eme_obj(19, 2);
//printf("%d", i);

/*-------------------------------------------------------------------------*/

void modif_ressource_sauf_pret(int num_cat, char *iD, char *ObjName, int choix_modif){
    FILE *fp = fopen("./json/Json.json", "r+");
    int l = ligne_bon_obj(num_cat,iD,ObjName);
    int l_c = ligne_bonne_categorie(num_cat+1);
    int l_c_toknow_n_eme_obj = ligne_bonne_categorie(num_cat);
    char *categorie;
    char Nom[60];
    char Desc[250];

    switch (num_cat) {
      case 1:
        categorie = "Livre";
        break;
      case 2:
        categorie = "Informatique";
        break;
      case 3:
        categorie = "Bricolage";
        break;
      case 4:
        categorie = "Sport";
        break;
      case 5:
        categorie = "Jouet";
        break;
      case 6:
        categorie = "Cuisine";
        break;
      case 7:
        categorie = "Autre";
        break;
      default:
        break;
    }

    int n_eme_obj = quel_n_eme_obj(l, l_c_toknow_n_eme_obj);
    char *Description = NULL;
    sauvegarder_detail_obj(categorie,n_eme_obj,2,&Description);
    int i;
    char ch;
    if(choix_modif==1){
      printf("Actuel nom : %s\n", ObjName);
      printf("Nouveau nom: ");

      i=0;
      ch = getchar();
      while ( ch != 10 ){
          Nom[i] = ch;
          ch = getchar();
          i++;
          Nom[i] = '\0';
      }
    }
    else{
      printf("Actuelle description : %s\n", Description);
      printf("Nouvelle description: ");

      i=0;
      ch = getchar();
      while ( ch != 10 ){
          Desc[i] = ch;
          ch = getchar();
          i++;
          Desc[i] = '\0';
      }
    }
    char *id_pret = NULL;
    savoir_nom_pret(categorie, n_eme_obj, &id_pret);
    if(choix_modif==1)
      add_ressource(l_c, iD, Description, Nom, id_pret);
    else
      add_ressource(l_c, iD, Desc, ObjName, id_pret);
    del_ressource(l);
    fclose(fp);

    /* In order to make suitable the history for "name's modification" */
    char *NewName = NULL;
    char *mott = "-->";
    int Longe = (strlen(ObjName)+strlen(mott)+strlen(Nom)+1);
    NewName = calloc(Longe, sizeof(char));
    strcat(NewName, ObjName);
    strcat(NewName, mott);
    strcat(NewName, Nom);
    int Ligne = ligne_bonne_personne(iD);
    if(choix_modif==1)
      add_hist(Ligne, NewName, 3);
    else
      add_hist(Ligne, ObjName, 3);
    free(NewName);
  }
//Exemple d'utilisation:
//char *Name = "RussiaIsAHeaven";
//char *iD = "KGB";
//int choix_modif = 2;
//modif_ressource_sauf_pret(1,iD,Name,choix_modif);

/*-------------------------------------------------------------------------*/

int afficher_liste_obj_du_proprio(char *obj,char *proprio){
  struct json_object *o_obj, *o_array, *o_array_obj, *o_array_obj_name;
  int arraylen, j;
  int count = 0;
  bool appartient = true;
  static const char filename[] = "./json/Json.json";
  o_obj = json_object_from_file(filename);
  o_array = json_object_object_get(o_obj, obj);

  // o_array is an array of objects
  arraylen = json_object_array_length(o_array);

  for (j = 0; j < arraylen; j++) {
    // get the i-th object in o_array
    o_array_obj = json_object_array_get_idx(o_array, j);
    // get the name attribute in the i-th object
    o_array_obj_name = json_object_object_get(o_array_obj, "Proprietaire");
    char *id_a_check = json_object_get_string(o_array_obj_name);
    appartient = true;
    for(int a = 0; proprio[a]!='\0'; a++){
      if(id_a_check[a]!=proprio[a])
        appartient = false;
    }
    if(appartient==true){
      o_array_obj_name = json_object_object_get(o_array_obj, "Name");
      printf("%d. %s\n",count+1,json_object_get_string(o_array_obj_name));
      count++;
    }
  }
  return count;
}
//Exemple d'utilisation:
//char *objet = "electronique";
//char *proprio ="Monsieur Durand";
//afficher_liste_obj_du_proprio(objet, proprio);

/*-------------------------------------------------------------------------*/

void savoir_choix_obj_du_proprio(char *obj,char *proprio, int choix, char **sauv){ //donne le nom de l'objet
  struct json_object *o_obj, *o_array, *o_array_obj, *o_array_obj_name;
  int arraylen, j;
  int count = 0;
  bool appartient = true;
  static const char filename[] = "./json/Json.json";
  o_obj = json_object_from_file(filename);
  o_array = json_object_object_get(o_obj, obj);

  // o_array is an array of objects
  arraylen = json_object_array_length(o_array);

  for (j = 0; j < arraylen; j++) {
    // get the i-th object in o_array
    o_array_obj = json_object_array_get_idx(o_array, j);
    // get the name attribute in the i-th object
    o_array_obj_name = json_object_object_get(o_array_obj, "Proprietaire");
    char *id_a_check = json_object_get_string(o_array_obj_name);
    appartient = true;
    for(int a = 0; proprio[a]!='\0'; a++){
      if(id_a_check[a]!=proprio[a])
        appartient = false;
    }
    if(appartient==true){
      if(count==choix-1){
        o_array_obj_name = json_object_object_get(o_array_obj, "Name");
        //printf("%s\n",json_object_get_string(o_array_obj_name));
        *sauv = json_object_get_string(o_array_obj_name);
      }
      count++;
    }
  }
}
//Exemple d'utilisation:
//char *objet = "electronique";
//char *proprio ="Monsieur Durand";
//int choix = 2;
//char *sauvegarde_detail;
//savoir_choix_obj_du_proprio(objet, proprio, choix, &sauvegarde_detail);
//printf("%s\n", sauvegarde_detail);

/*-------------------------------------------------------------------------*/

void savoir_choix_desc_du_proprio(char *obj,char *proprio, int choix, char **sauv){//donne la description de l'objet
  struct json_object *o_obj, *o_array, *o_array_obj, *o_array_obj_name;
  int arraylen, j;
  int count = 0;
  bool appartient = true;
  static const char filename[] = "./json/Json.json";
  o_obj = json_object_from_file(filename);
  o_array = json_object_object_get(o_obj, obj);

  // o_array is an array of objects
  arraylen = json_object_array_length(o_array);

  for (j = 0; j < arraylen; j++) {
    // get the i-th object in o_array
    o_array_obj = json_object_array_get_idx(o_array, j);
    // get the name attribute in the i-th object
    o_array_obj_name = json_object_object_get(o_array_obj, "Proprietaire");
    char *id_a_check = json_object_get_string(o_array_obj_name);
    appartient = true;
    for(int a = 0; proprio[a]!='\0'; a++){
      if(id_a_check[a]!=proprio[a])
        appartient = false;
    }
    if(appartient==true){
      if(count==choix-1){
        o_array_obj_name = json_object_object_get(o_array_obj, "Description");
        //printf("%s\n",json_object_get_string(o_array_obj_name));
        *sauv = json_object_get_string(o_array_obj_name);
      }
      count++;
    }
  }
}
//Exemple d'utilisation:
//char *objet = "electronique";
//char *proprio ="Monsieur Durand";
//int choix = 2;
//char *sauvegarde_detail;
//savoir_choix_desc_du_proprio(objet, proprio, choix, &sauvegarde_detail);
//printf("%s\n", sauvegarde_detail);

/*-------------------------------------------------------------------------*/

void savoir_nom_pret(char *obj, int choix, char **sauv){
    struct json_object *o_obj, *o_array, *o_array_obj, *o_array_obj_name;
    int arraylen, j;
    static const char filename[] = "./json/Json.json";
    o_obj = json_object_from_file(filename);
    o_array = json_object_object_get(o_obj, obj);

    // o_array is an array of objects
    arraylen = json_object_array_length(o_array);

    choix = choix-1;

    for (j = 0; j < arraylen; j++) {
      if(choix==j){
        // get the i-th object in o_array
        o_array_obj = json_object_array_get_idx(o_array, j);
        o_array_obj_name = json_object_object_get(o_array_obj, "En cours de pret");
        *sauv = json_object_get_string(o_array_obj_name);
      }
    }
  }
//Exemple d'utilisation:
//char *objet = "livre";
//int choix_livre = 1;
//char *ID;
//savoir_nom_pret(objet, choix_livre, &ID);
//printf("%s\n", ID);

/*-------------------------------------------------------------------------*/

void savoir_nom_proprio(char *obj, int choix, char **sauv){
    struct json_object *o_obj, *o_array, *o_array_obj, *o_array_obj_name;
    int arraylen, j;
    static const char filename[] = "./json/Json.json";
    o_obj = json_object_from_file(filename);
    o_array = json_object_object_get(o_obj, obj);

    // o_array is an array of objects
    arraylen = json_object_array_length(o_array);

    choix = choix-1;

    for (j = 0; j < arraylen; j++) {
      if(choix==j){
        // get the i-th object in o_array
        o_array_obj = json_object_array_get_idx(o_array, j);
        o_array_obj_name = json_object_object_get(o_array_obj, "Proprietaire");
        *sauv = json_object_get_string(o_array_obj_name);
      }
    }
  }
//Exemple d'utilisation:
//char *objet = "livre";
//int choix_livre = 1;
//char *ID;
//savoir_nom_proprio(objet, choix_livre, &ID);
//printf("%s\n", ID);

/*-------------------------------------------------------------------------*/

int savoir_si_en_pret(char *obj, int choix){
    struct json_object *o_obj, *o_array, *o_array_obj, *o_array_obj_name;
    int arraylen, j;
    static const char filename[] = "./json/Json.json";
    o_obj = json_object_from_file(filename);
    o_array = json_object_object_get(o_obj, obj);

    // o_array is an array of objects
    arraylen = json_object_array_length(o_array);

    choix = choix-1;
    int rep;

    for (j = 0; j < arraylen; j++) {
      if(choix==j){
        // get the i-th object in o_array
        o_array_obj = json_object_array_get_idx(o_array, j);
        o_array_obj_name = json_object_object_get(o_array_obj, "En cours de pret");
        int test = strcmp(json_object_get_string(o_array_obj_name), ".");
      	if(test == 0)
          rep = 2;
        else
          rep = 1;
      }
    }
    return rep;
  }
//Exemple d'utilisation:
//char *objet = "livre";
//int choix_livre = 2;
//int a = savoir_si_en_pret(objet, choix_livre);
//printf("%d\n", a); //1 si en pret sinon 2 si libre

/*-------------------------------------------------------------------------*/

void mettre_en_pret_ou_finir_le_pret(int num_cat, char *iD, char *ObjName, char *iD2){
    FILE *fp = fopen("./json/Json.json", "r+");
    int l = ligne_bon_obj(num_cat,iD,ObjName);
    int l_c = ligne_bonne_categorie(num_cat+1);
    int l_c_toknow_n_eme_obj = ligne_bonne_categorie(num_cat);
    char *Nom;
    char *Desc;
    char *categorie;

    switch (num_cat) {
      case 1:
        categorie = "Livre";
        break;
      case 2:
        categorie = "Informatique";
        break;
      case 3:
        categorie = "Bricolage";
        break;
      case 4:
        categorie = "Sport";
        break;
      case 5:
        categorie = "Jouet";
        break;
      case 6:
        categorie = "Cuisine";
        break;
      case 7:
        categorie = "Autre";
        break;
      default:
        break;
    }

    int n_eme_obj = quel_n_eme_obj(l, l_c_toknow_n_eme_obj);

    sauvegarder_detail_obj(categorie,n_eme_obj,1,&Nom);
    sauvegarder_detail_obj(categorie,n_eme_obj,2,&Desc);
    char *point;
    savoir_nom_pret(categorie, n_eme_obj, &point);
    if(strcmp(point, ".") == 0)
      add_ressource(l_c, iD, Desc, Nom, iD2);
    else
      add_ressource(l_c, iD, Desc, Nom, ".");
    del_ressource(l);
    fclose(fp);
  }
//Exemple d'utilisation:
//char *Name = "RussiaIsAHeaven";
//char *iD = "KGB"; -> proprietaire
//char *ID2 = "FSB"; -> veux la ressource
//mettre_en_pret_ou_finir_le_pret(1,iD,Name,ID2);

/*-------------------------------------------------------------------------*/

void add_hist(int num_ligne_pers, char *iD, int ope){
  /* Open the file for reading and the other to write */
  /*-----*//*-----*//*-----*/
  system("sh ./script/Date.sh");
  FILE *ftmp = fopen("Tempo.txt", "r");
  signed char date[64];
  fgets(date, 63, ftmp);
  fclose(ftmp);

  char *Datetmp = NULL;
  int Larg = strlen(date);
  Datetmp = calloc(Larg, sizeof(char));
  strcat(Datetmp, date);
  Datetmp[strlen(Datetmp)-1]='\0';
  /*-----*//*-----*//*-----*/
  char *line_buf = NULL;
  size_t line_buf_size = 0;
  int line_count = 0;
  ssize_t line_size;
  FILE *fp = fopen("./json/Historique.json", "r");
  FILE *fic2 = fopen("./json/Historiquebis.json", "w");
  char *Operation;
  char *Concat = NULL;
  char *Concat2 = NULL;
  char *Concat3 = NULL;

  switch (ope) {
    case 1:
      Operation = "Ajout";
      break;
    case 2:
      Operation = "Supprimer";
      break;
    case 3:
      Operation = "Modifier";
      break;
    case 4:
      Operation = "Emprunt";
      break;
    case 5:
      Operation = "Fin de pret";
      break;
    default:
      break;
  }

  /* Get the first line of the file. */
  line_size = getline(&line_buf, &line_buf_size, fp);

  /* Loop through until we are done with the file. */
  while (line_size >= 0)
  {
    /* Increment our line count */
    line_count++;

    /* Show the line details and printing them into the second file */
    if(line_count==num_ligne_pers+1){
      fputs("    {\n", fic2);


      char *mot_deb = "      \"Operation\": \"";
      char *mot_fin = "\",\n";
      int Long = (strlen(mot_deb)+strlen(mot_fin)+strlen(Operation)+1);
      Concat = calloc(Long, sizeof(char));
      strcat(Concat, mot_deb);
      strcat(Concat, Operation);
      strcat(Concat, mot_fin);
      //printf("1.C'est ça la taille de Concat: %ld.\n", strlen(Concat));
      //printf("%s\n",Concat);
      fputs(Concat, fic2);
      free(Concat);


      char *mot_deb2 = "      \"Date\": \"";
      char *mot_fin2 = "\",\n";
      int Long2 = (strlen(mot_deb2)+strlen(mot_fin2)+strlen(Datetmp)+1);
      Concat2 = calloc(Long2, sizeof(char));
      strcat(Concat2, mot_deb2);
      strcat(Concat2, Datetmp);
      strcat(Concat2, mot_fin2);
      //printf("2.C'est ça la taille de Concat2: %ld.\n", strlen(Concat2));
      //printf("%s\n",Concat2);
      fputs(Concat2, fic2);
      free(Concat2);


      char *mot_deb3 = "      \"Objet\": \"";
      char *mot_fin3 = "\"\n";
      int Long3 = (strlen(mot_deb3)+strlen(mot_fin3)+strlen(iD)+1);
      Concat3 = calloc(Long3, sizeof(char));
      strcat(Concat3, mot_deb3);
      strcat(Concat3, iD);
      strcat(Concat3, mot_fin3);
      //printf("3.C'est ça la taille de Concat3: %ld.\n", strlen(Concat3));
      //printf("%s\n",Concat3);
      fputs(Concat3, fic2);
      free(Concat3);

      fputs("    },\n", fic2);

    }
    fputs(line_buf, fic2);

    /* Get the next line */
    line_size = getline(&line_buf, &line_buf_size, fp);
  }

  /* Free the allocated line buffer and the one for the date */
  free(line_buf);
  free(Datetmp);


  /* Close files now that we are done with */
  fclose(fp);
  fclose(fic2);
  remove("./Tempo.txt");
  remove("./json/Historique.json");
  rename("./json/Historiquebis.json", "./json/Historique.json");
  }
//Exemple d'utilisation:
//int n = 24;
//char *obj = "Marteau";
//int ope = 1;
//add_hist(n, obj, ope);

/*-------------------------------------------------------------------------*/

void afficher_liste_historique(char *iD){
    struct json_object *o_obj, *o_array, *o_array_obj, *o_array_obj_name;
    int arraylen, j;
    static const char filename[] = "./json/Historique.json";
    o_obj = json_object_from_file(filename);
    o_array = json_object_object_get(o_obj, iD);

    // o_array is an array of objects
    arraylen = json_object_array_length(o_array);

    for (j = 0; j < arraylen; j++) {
      // get the i-th object in o_array
      o_array_obj = json_object_array_get_idx(o_array, j);
      // get the name attribute in the i-th object
      o_array_obj_name = json_object_object_get(o_array_obj, "Operation");
      // print out the name attribute
      printf("%d. %s: ",j+1,json_object_get_string(o_array_obj_name));
      o_array_obj_name = json_object_object_get(o_array_obj, "Date");
      printf(" %s,",json_object_get_string(o_array_obj_name));
      o_array_obj_name = json_object_object_get(o_array_obj, "Objet");
      printf(" %s\n",json_object_get_string(o_array_obj_name));
    }
  }
//Exemple d'utilisation:
//char *iD = "John";
//afficher_liste_historique(iD);

/*-------------------------------------------------------------------------*/

void stocker_id_hist_inscription(char *iD){
    FILE *fic = fopen("./json/Historique.json", "r+");

    fseek(fic, -3, SEEK_END);

    fputs(",\n  \"", fic);
    fputs(iD, fic);
    fputs("\": [\n  ]\n}\n", fic);

    fclose(fic);
  }
//Exemple d'utilisation:
//char *i = "New";
//stocker_id_hist_inscription(i);

/*-------------------------------------------------------------------------*/

int ligne_bonne_personne(char *iD){
    /* Open the file for reading and the other to write */
    bool in_categorie;
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    ssize_t line_size;
    FILE *fp = fopen("./json/Historique.json", "r");
    char *line_buf_check = NULL;
    int res;

    char *mot_deb = "  \"";
    char *mot_fin = "\": [\n";
    int Long = (strlen(mot_deb)+strlen(mot_fin)+strlen(iD)+1);
    line_buf_check = calloc(Long, sizeof(char));
    strcat(line_buf_check, mot_deb);
    strcat(line_buf_check, iD);
    strcat(line_buf_check, mot_fin);
    //printf("%s",line_buf_check);

    /* Get the first line of the file. */
    line_size = getline(&line_buf, &line_buf_size, fp);

    /* Loop through until we are done with the file. */
    while (line_size >= 0)
    {
      line_count++;
      /* Show the line details */
      //printf("Contents: %s", line_buf);
      in_categorie = true;
      for(int a = 0; line_buf_check[a]!='\0'; a++){
        if(line_buf[a]!=line_buf_check[a])
          in_categorie = false;
      }
      //printf("%d",line_count);
      if(in_categorie==true)
        res = line_count;

      /* Get the next line */
      line_size = getline(&line_buf, &line_buf_size, fp);
    }

    /* Free the allocated line buffer */
    free(line_buf);
    free(line_buf_check);

    /* Close files now that we are done with */
    fclose(fp);
    return res;
  }
//Exemple d'utilisation:
//char *ID = "KGB";
//int n = ligne_bonne_personne(ID);

/*-------------------------------------------------------------------------*/

void afficher_liste_historique_choix(char *iD, int J){
    struct json_object *o_obj, *o_array, *o_array_obj, *o_array_obj_name;
    int arraylen, j;
    static const char filename[] = "./json/Historique.json";
    o_obj = json_object_from_file(filename);
    o_array = json_object_object_get(o_obj, iD);

    // o_array is an array of objects
    arraylen = json_object_array_length(o_array);

    for (j = 0; j < arraylen; j++) {
      if(j<=J){
        // get the i-th object in o_array
        o_array_obj = json_object_array_get_idx(o_array, j);
        // get the name attribute in the i-th object
        o_array_obj_name = json_object_object_get(o_array_obj, "Operation");
        // print out the name attribute
        printf("%d. %s: ",j+1,json_object_get_string(o_array_obj_name));
        o_array_obj_name = json_object_object_get(o_array_obj, "Date");
        printf(" %s,",json_object_get_string(o_array_obj_name));
        o_array_obj_name = json_object_object_get(o_array_obj, "Objet");
        printf(" %s\n",json_object_get_string(o_array_obj_name));
      }
    }
  }
//Exemple d'utilisation:
//int k = 10;
//char *iD = "John";
//afficher_liste_historique_choix(iD, k);

/*-------------------------------------------------------------------------*/

int afficher_liste_obj_emprunte(char *obj, char *emprunteur){
  struct json_object *o_obj, *o_array, *o_array_obj, *o_array_obj_name;
  int arraylen, j;
  int count = 0;
  bool appartient = true;
  static const char filename[] = "./json/Json.json";
  o_obj = json_object_from_file(filename);
  o_array = json_object_object_get(o_obj, obj);

  // o_array is an array of objects
  arraylen = json_object_array_length(o_array);

  for (j = 0; j < arraylen; j++) {
    // get the i-th object in o_array
    o_array_obj = json_object_array_get_idx(o_array, j);
    // get the name attribute in the i-th object
    o_array_obj_name = json_object_object_get(o_array_obj, "En cours de pret");
    char *id_a_check = json_object_get_string(o_array_obj_name);
    appartient = true;
    for(int a = 0; emprunteur[a]!='\0'; a++){
      if(id_a_check[a]!=emprunteur[a])
        appartient = false;
    }
    if(appartient==true){
      o_array_obj_name = json_object_object_get(o_array_obj, "Name");
      printf("%d. %s\n",count+1,json_object_get_string(o_array_obj_name));
      count++;
    }
  }
  return count;
}
//Exemple d'utilisation:
//char *objet = "electronique";
//char *emprunteur ="Monsieur Durand";
//afficher_liste_obj_emprunte(objet, emprunteur);

/*-------------------------------------------------------------------------*/

void avoir_choix_obj_du_emprunteur(char *cat, char *emprunteur, int choix, char **sauv, char **sauv2){
  struct json_object *o_obj, *o_array, *o_array_obj, *o_array_obj_name;
  int arraylen, j;
  int count = 0;
  bool appartient = true;
  static const char filename[] = "./json/Json.json";
  o_obj = json_object_from_file(filename);
  o_array = json_object_object_get(o_obj, cat);

  // o_array is an array of objects
  arraylen = json_object_array_length(o_array);

  for (j = 0; j < arraylen; j++) {
    // get the i-th object in o_array
    o_array_obj = json_object_array_get_idx(o_array, j);
    // get the name attribute in the i-th object
    o_array_obj_name = json_object_object_get(o_array_obj, "En cours de pret");
    char *id_a_check = json_object_get_string(o_array_obj_name);
    appartient = true;
    for(int a = 0; emprunteur[a]!='\0'; a++){
      if(id_a_check[a]!=emprunteur[a])
        appartient = false;
    }
    if(appartient==true){
      if(count==choix-1){
        o_array_obj_name = json_object_object_get(o_array_obj, "Name");
        //printf("%s\n",json_object_get_string(o_array_obj_name));
        *sauv = json_object_get_string(o_array_obj_name);
        o_array_obj_name = json_object_object_get(o_array_obj, "Proprietaire");
        //printf("%s\n",json_object_get_string(o_array_obj_name));
        *sauv2 = json_object_get_string(o_array_obj_name);
      }
      count++;
    }
  }
}
//Exemple d'utilisation:
//char *sauv = "NAMEOBJ";     <--indication
//char *sauv2 = "PROPRIO";     <--indication
//char *categorie = "Livre";
//char *emprunteur ="Monsieur Durand";
//int choix = 2;
//avoir_choix_obj_du_emprunteur(categorie, emprunteur, choix, NAMEOBJ, PROPRIO);

/*-------------------------------------------------------------------------*/

int ligne_bonne_pers_hist(char *id){
    /* Open the file for reading and the other to write */
    bool in_categorie;
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    ssize_t line_size;
    FILE *fp = fopen("./json/Historique.json", "r");
    char *line_buf_check = NULL;
    int res;

    char *mot_deb = "  \"";
    char *mot_fin = "\": [\n";
    int Long = (strlen(mot_deb)+strlen(mot_fin)+strlen(id)+1);
    line_buf_check = calloc(Long, sizeof(char));
    strcat(line_buf_check, mot_deb);
    strcat(line_buf_check, id);
    strcat(line_buf_check, mot_fin);

    /* Get the first line of the file. */
    line_size = getline(&line_buf, &line_buf_size, fp);

    /* Loop through until we are done with the file. */
    while (line_size >= 0)
    {
      line_count++;
      /* Show the line details and printing them into the second file */
      //printf("Contents: %s", line_buf);
      in_categorie = true;
      for(int a = 0; line_buf_check[a]!='\0'; a++){
        if(line_buf[a]!=line_buf_check[a])
          in_categorie = false;
      }
      if(in_categorie==true)
        res = line_count;

      /* Get the next line */
      line_size = getline(&line_buf, &line_buf_size, fp);
    }

    /* Free the allocated line buffer */
    free(line_buf);
    free(line_buf_check);

    /* Close files now that we are done with */
    fclose(fp);
    return res;
  }
//Exemple d'utilisation:
//char *Id = "Durand";
//int a = ligne_bonne_pers_hist(Id);

/*-------------------------------------------------------------------------*/

void del_historique(int num_ligne){
    /* Open the file for reading and the other to write */
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    ssize_t line_size;
    FILE *fp = fopen("./json/Historique.json", "r");
    FILE *fic2 = fopen("./json/Historiquebis.json", "w");
    char *Test = "  ],\n";
    char *Test2 = "  ]\n";

    /* Get the first line of the file. */
    line_size = getline(&line_buf, &line_buf_size, fp);

    /* Loop through until we are done with the file. */
    while (line_size >= 0)
    {
      /* Increment our line count */
      line_count++;

      /* Show the line details and printing them into the second file */
      //printf("Contents: %s", line_buf);
      if(line_count!=(num_ligne))
          fputs(line_buf, fic2);
      else{
        while(strcmp(line_buf,Test)!=0 && strcmp(line_buf, Test2)!=0){
          line_size = getline(&line_buf, &line_buf_size, fp);
          line_count++;
        }
      }

      /* Get the next line */
      line_size = getline(&line_buf, &line_buf_size, fp);
    }

    /* Free the allocated line buffer */
    free(line_buf);

    /* Close files now that we are done with */
    fclose(fp);
    fclose(fic2);
    system("sh ./script/scriptVirgule.sh ./json/Historiquebis.json");
    remove("./json/Historique.json");
    rename("./json/Historiquebis.json", "./json/Historique.json");
    }
//Exemple d'utilisation:
//del_historique(a);
