#include <stdio.h>
#include <stdlib.h>
#include "../include/json.h"
#include <json-c/json.h>
#include <string.h>
#include <stdbool.h>


void afficher_liste_obj_raw(char *obj){
  //char *field = "consoles";    Le mot a noter comme cela avec les guillemets
  //afficher_liste_obj(field);   Appel de la fonction
  FILE *fic;
  char buffer[2048];//buffer à allouer dynamiquement???

  struct json_object *parsed_json;
  struct json_object *liste_objet;
  struct json_object *objet;
  size_t n_obj;
  size_t i;

  fic = fopen("./json/Json.json","r");
  fread(buffer, 2048, 1, fic);
  fclose(fic);

  parsed_json = json_tokener_parse(buffer);

  json_object_object_get_ex(parsed_json, obj, &liste_objet);//changer "vert" en variable à choisir

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
  struct json_object *med_obj, *medi_array, *medi_array_obj, *medi_array_obj_name;
  int arraylen, j;
  static const char filename[] = "./json/Json.json";
  med_obj = json_object_from_file(filename);
  medi_array = json_object_object_get(med_obj, obj);//changer "vert" en objet à choisir

  // medi_array is an array of objects
  arraylen = json_object_array_length(medi_array);

  choix = choix-1;

  for (j = 0; j < arraylen; j++) {
    if(choix==j){
      // get the i-th object in medi_array
      medi_array_obj = json_object_array_get_idx(medi_array, j);
      // get the name attribute in the i-th object
      medi_array_obj_name = json_object_object_get(medi_array_obj, "Name");//changer "vert" en détail à choisir
      // print out the name attribute
      printf("Name : %s\n",json_object_get_string(medi_array_obj_name));
      medi_array_obj_name = json_object_object_get(medi_array_obj, "Description");//changer "vert" en détail à choisir
      printf("Description : %s\n",json_object_get_string(medi_array_obj_name));
      medi_array_obj_name = json_object_object_get(medi_array_obj, "En cours de pret");//changer "vert" en détail à choisir
      printf("En cours de pret : %s\n",json_object_get_string(medi_array_obj_name));
      medi_array_obj_name = json_object_object_get(medi_array_obj, "Proprietaire");//changer "vert" en détail à choisir
      printf("Proprietaire : %s\n",json_object_get_string(medi_array_obj_name));
    }
  }
}
//Exemple d'utilisation:
//char *objet = "livre";
//int choix = 3;
//afficher_liste_obj(objet);
//afficher_detail_obj(objet, choix);

/*-------------------------------------------------------------------------*/

void afficher_liste_obj(char *obj){
  struct json_object *med_obj, *medi_array, *medi_array_obj, *medi_array_obj_name;
  int arraylen, j;
  static const char filename[] = "./json/Json.json";
  med_obj = json_object_from_file(filename);
  medi_array = json_object_object_get(med_obj, obj);//changer "vert" en objet à choisir

  // medi_array is an array of objects
  arraylen = json_object_array_length(medi_array);

  for (j = 0; j < arraylen; j++) {
    // get the i-th object in medi_array
    medi_array_obj = json_object_array_get_idx(medi_array, j);
    // get the name attribute in the i-th object
    medi_array_obj_name = json_object_object_get(medi_array_obj, "Name");//changer "vert" en détail à choisir
    // print out the name attribute
    printf("%d. %s\n",j+1,json_object_get_string(medi_array_obj_name));
  }
}
//Exemple d'utilisation:
//char *objet = "livre";
//afficher_liste_obj(objet);

/*-------------------------------------------------------------------------*/

void chercher_mdp(char *iD, char ** p){
    FILE *fic;
	  char buffer[2048];
	  struct json_object *parsed_json;
	  struct json_object *mdp;

	  fic = fopen("./json/Client.json","r");
	  fread(buffer, 2048, 1, fic);
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
	  char buffer[2048];
	  struct json_object *parsed_json;
	  struct json_object *mdp;

	  fic = fopen("./json/Client.json","r");
	  fread(buffer, 2048, 1, fic);
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

void stocker_id_mdp_inscription(char *iD, char* mdp){
    FILE *fic = fopen("./json/Client.json", "r+");

    fseek(fic, -3, SEEK_END);

    fputs(",\n  \"", fic);
    fputs(iD, fic);
    fputs("\": \"", fic);
    fputs(mdp, fic);
    fputs("\"\n}\n", fic);

    fclose(fic);
  }
//Exemple d'utilisation:
//char *i = "New";
//char *m = "koikoi";
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
  if (!fp)
  {
    fprintf(stderr, "Error opening file '%s'\n", "./json/Client.json");
    return EXIT_FAILURE;
  }

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
  line_buf = NULL;

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
  if (!fp)
  {
    fprintf(stderr, "Error opening file '%s'\n", "./json/Client.json");
    return EXIT_FAILURE;
  }

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
  line_buf = NULL;

  /* Close files now that we are done with */
  fclose(fp);
  fclose(fic2);
  system("sh ./script/scriptVirgule.sh ./json/Client2.json");
  remove("./json/Client.json");
  rename("./json/Client2.json", "./json/Client.json");
  //return 1;
}
//Exemple d'utilisation:
//admin_del_someone(7);

/*-------------------------------------------------------------------------*/

bool check_n_id_existe(int choix){
    /* Open the file for reading and the other to write */
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    ssize_t line_size;
    FILE *fp = fopen("./json/Client.json", "r");
    if (!fp)
    {
      fprintf(stderr, "Error opening file '%s'\n", "./json/Client.json");
      return EXIT_FAILURE;
    }

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
    line_buf = NULL;

    /* Close files now that we are done with */
    fclose(fp);
  }
//check_n_id_existe(6);

/*-------------------------------------------------------------------------*/

void print_id(int choix){
  /* Open the file for reading and the other to write */
  char *line_buf = NULL;
  size_t line_buf_size = 0;
  int line_count = 0;
  ssize_t line_size;
  FILE *fp = fopen("./json/Client.json", "r");
  if (!fp)
  {
    fprintf(stderr, "Error opening file '%s'\n", "./json/Client.json");
    return EXIT_FAILURE;
  }

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
  line_buf = NULL;

  /* Close files now that we are done with */
  fclose(fp);
}
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
    if (!fp)
    {
      fprintf(stderr, "Error opening file '%s'\n", "./json/Client.json");
      return EXIT_FAILURE;
    }

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
    line_buf = NULL;

    /* Close files now that we are done with */
    fclose(fp);
    fclose(ft);
  }
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
    return(i-1);
  }
//char *nom = "Lou";
//int a = num_id(nom);
//printf("%d\n", a);

/*-------------------------------------------------------------------------*/

int ligne_bonne_categorie(int choix){
    /* Open the file for reading and the other to write */
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
        line_buf_check = "  \"livre\": [";
        break;
      case 2:
        line_buf_check = "  \"electronique\": [";
        break;
      case 3:
        line_buf_check = "  \"outil\": [";
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
    line_buf = NULL;

    /* Close files now that we are done with */
    fclose(fp);
    return res;
  }
//int a = ligne_bonne_categorie(2);
//printf("%d\n",a); --> 16

/*-------------------------------------------------------------------------*/

int ligne_bon_obj(int num_cat, char *iD, char *Obj){
    /* Open the file for reading and the other to write */
    bool in_categorie;
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    ssize_t line_size;
    FILE *fp = fopen("./json/Json.json", "r");
    char *line_buf_check;
    int bombe;
    int res;

    char mot_vide_obj[17] = "      \"Name\": \"";
    char mot_vide_fin[3] = "\",";
    char *line_buf_check_tmp_obj = strcat(mot_vide_obj, Obj);
    char *line_buf_check_obj = strcat(line_buf_check_tmp_obj, mot_vide_fin);


    char mot_vide[25] = "      \"Proprietaire\": \"";
    char mot_vide_fin2[2] = "\"";
    char *line_buf_check_tmp = strcat(mot_vide, iD);
    //printf("%s\n\n", line_buf_check_tmp);
    char *line_buf_check_iD = strcat(line_buf_check_tmp, mot_vide_fin2);
    //printf("%s\n\n", line_buf_check_iD);


    switch (num_cat) {
      case 1:
        line_buf_check = "  \"livre\": [";
        break;
      case 2:
        line_buf_check = "  \"electronique\": [";
        break;
      case 3:
        line_buf_check = "  \"outil\": [";
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
      /* Show the line details and printing them into the second file */
      //printf("Contents: %s", line_buf);
      in_categorie = true;
      for(int a = 0; line_buf_check[a]!='\0'; a++){
        if(line_buf[a]!=line_buf_check[a])
          in_categorie = false;
      }
      if(in_categorie==true)
        goto N;

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
      /* Show the line details and printing them into the second file */
      //printf("Contents: %s", line_buf);
      in_categorie = true;
      for(int a = 0; line_buf_check_obj[a]!='\0'; a++){
        if(line_buf[a]!=line_buf_check_obj[a])
          in_categorie = false;
      }
      if(in_categorie==true)
        goto ID;

      /* Get the next line */
      line_size = getline(&line_buf, &line_buf_size, fp);
    }
/*----------*//*----------*//*----------*//*----------*//*----------*/
    ID:
    bombe = 0;
    line_size = getline(&line_buf, &line_buf_size, fp);

    /* Loop through until we are done with the file. */
    while (line_size >= 0)
    {
      line_count++;
      /* Show the line details and printing them into the second file */
      //printf("Contents: %s", line_buf);
      in_categorie = true;
      for(int a = 0; line_buf_check_iD[a]!='\0'; a++){
        if(line_buf[a]!=line_buf_check_iD[a])
          in_categorie = false;
      }
      if(in_categorie==true){
        //printf("  On est ici");
        res = line_count;
        //printf(" \n---%d---\n\n",line_count);
      }
      bombe++;
      if(bombe == 3)
        goto N;

      /* Get the next line */
      line_size = getline(&line_buf, &line_buf_size, fp);
    }

    /* Free the allocated line buffer */
    free(line_buf);
    line_buf = NULL;

    /* Close files now that we are done with */
    fclose(fp);
    //printf("\n\n---%d---\n\n",line_count);
    return res;
  }
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
  line_buf = NULL;

  /* Close files now that we are done with */
  fclose(fp);
  fclose(fic2);
  remove("./json/Json.json");
  rename("./json/Jsonbis.json", "./json/Json.json");
  }
//del_ressource(a);

/*-------------------------------------------------------------------------*/

void add_ressource(int num_ligne_cat, char *iD, char *Descr, char *ObjName){
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
    if(line_count==num_ligne_cat-1){
      fputs("    {\n", fic2);

      char mot_vide_obj[17] = "      \"Name\": \"";
      char mot_vide_fin[6] = "\",\n";
      char *nom_stock_tmp = strcat(mot_vide_obj, ObjName);
      char *nom_stock = strcat(nom_stock_tmp, mot_vide_fin);

      fputs(nom_stock, fic2);

      char mot_vide_obj2[24] = "      \"Description\": \"";
      char *desc_stock_tmp = strcat(mot_vide_obj2, Descr);
      char *desc_stock = strcat(desc_stock_tmp, mot_vide_fin);

      fputs(desc_stock, fic2);
      fputs("      \"En cours de pret\": \"oui\",\n", fic2);

      char mot_vide_obj3[25] = "      \"Proprietaire\": \"";
      char mot_vide_fin2[5] = "\"\n";
      char *proprio_stock_tmp = strcat(mot_vide_obj3, iD);
      char *proprio_stock = strcat(proprio_stock_tmp, mot_vide_fin2);

      fputs(proprio_stock, fic2);
      fputs("    },\n", fic2);
    }
    fputs(line_buf, fic2);

    /* Get the next line */
    line_size = getline(&line_buf, &line_buf_size, fp);
  }

  /* Free the allocated line buffer */
  free(line_buf);
  line_buf = NULL;

  /* Close files now that we are done with */
  fclose(fp);
  fclose(fic2);
  remove("./json/Json.json");
  rename("./json/Jsonbis.json", "./json/Json.json");
  }
//int n = 16;
//char *id = "John";
//char *des = "Voici un super livre, je vous le recommande";
//char *obj = "Le voyage de Tima";
//add_ressource(n, id, des, obj);

/*-------------------------------------------------------------------------*/

void sauvegarder_detail_obj(char *obj, int choix, int choix_modif, char **sauv){
    struct json_object *med_obj, *medi_array, *medi_array_obj, *medi_array_obj_name;
    int arraylen, j;
    static const char filename[] = "./json/Json.json";
    med_obj = json_object_from_file(filename);
    medi_array = json_object_object_get(med_obj, obj);

    // medi_array is an array of objects
    arraylen = json_object_array_length(medi_array);

    choix = choix-1;

    for (j = 0; j < arraylen; j++) {
      if(choix==j){
        // get the i-th object in medi_array
        medi_array_obj = json_object_array_get_idx(medi_array, j);
        switch (choix_modif) {
          case 1:
            medi_array_obj_name = json_object_object_get(medi_array_obj, "Name");
            *sauv = json_object_get_string(medi_array_obj_name);
            break;
          case 2:
            medi_array_obj_name = json_object_object_get(medi_array_obj, "Description");
            *sauv = json_object_get_string(medi_array_obj_name);
            break;
          default:
            break;
        }
      }
    }
  }
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
//int i = quel_n_eme_obj(19, 2);
//printf("%d", i);

/*-------------------------------------------------------------------------*/

void modif_ressource_sauf_pret(int num_cat, char *iD, char *ObjName, int choix_modif){
    FILE *fp = fopen("./json/Json.json", "r+");
    int l = ligne_bon_obj(num_cat,iD,ObjName);
    int l_c = ligne_bonne_categorie(num_cat+1);
    int l_c_toknow_n_eme_obj = ligne_bonne_categorie(num_cat);
    //printf("%d %d\n",l,l_c_toknow_n_eme_obj);
    char *Nom;//malloc
    char *Desc;//malloc
    char *categorie;
    int i;
    char ch;
    switch (num_cat) {
      case 1:
        categorie = "livre";
        break;
      case 2:
        categorie = "electronique";
        break;
      case 3:
        categorie = "outil";
        break;
      default:
        break;
    }
    int n_eme_obj = quel_n_eme_obj(l, l_c_toknow_n_eme_obj);
    sauvegarder_detail_obj(categorie,n_eme_obj,1,&Nom);
    sauvegarder_detail_obj(categorie,n_eme_obj,2,&Desc);
    if(choix_modif==1){
      printf("Actuel nom : %s\n", Nom);
      printf("Nouveau nom: ");

      //remplace scanf :
      i=0;
      ch = getchar();
      while ( ch != 10 ){
          Nom[i] = ch;
          ch = getchar();
          i++;
          Nom[i] = '\0';
      }
      //scanf("%s\n", Nom);
      printf("N: %s\n", Nom);
    }
    else{
      printf("Actuelle description : %s\n", Desc);
      printf("Nouvelle description: ");
      //scanf("%s\n", Desc);
      //remplace scanf :
      i=0;
      ch = getchar();
      while ( ch != 10 ){
          Desc[i] = ch;
          ch = getchar();
          i++;
          Desc[i] = '\0';
      }
      //printf("N: %s\n", Desc);
    }
    add_ressource(l_c, iD, Desc, Nom);
    del_ressource(l);
    fclose(fp);
  }
//char *Name = "RussiaIsAHeaven";
//char *iD = "KGB";
//int choix_modif = 2;  //choisir un ou deux suivant modif nom ou description
//modif_ressource_sauf_pret(1,iD,Name,choix_modif);

/*-------------------------------------------------------------------------*/
void afficher_liste_obj_du_proprio(char *obj,char *proprio){
  struct json_object *med_obj, *medi_array, *medi_array_obj, *medi_array_obj_name;
  int arraylen, j;
  int count = 0;
  bool appartient = true;
  static const char filename[] = "./json/Json.json";
  med_obj = json_object_from_file(filename);
  medi_array = json_object_object_get(med_obj, obj);

  // medi_array is an array of objects
  arraylen = json_object_array_length(medi_array);

  for (j = 0; j < arraylen; j++) {
    // get the i-th object in medi_array
    medi_array_obj = json_object_array_get_idx(medi_array, j);
    // get the name attribute in the i-th object
    medi_array_obj_name = json_object_object_get(medi_array_obj, "Proprietaire");
    char *id_a_check = json_object_get_string(medi_array_obj_name);
    appartient = true;
    for(int a = 0; proprio[a]!='\0'; a++){
      if(id_a_check[a]!=proprio[a])
        appartient = false;
    }
    if(appartient==true){
      medi_array_obj_name = json_object_object_get(medi_array_obj, "Name");
      printf("%d. %s\n",count+1,json_object_get_string(medi_array_obj_name));
      count++;
    }
  }
}
//char *objet = "electronique";
//char *proprio ="Monsieur Durand";
//afficher_liste_obj_du_proprio(objet, proprio);

/*-------------------------------------------------------------------------*/

void afficher_choix_obj_du_proprio(char *obj,char *proprio, int choix, char **sauv){
  struct json_object *med_obj, *medi_array, *medi_array_obj, *medi_array_obj_name;
  int arraylen, j;
  int count = 0;
  bool appartient = true;
  static const char filename[] = "./json/Json.json";
  med_obj = json_object_from_file(filename);
  medi_array = json_object_object_get(med_obj, obj);

  // medi_array is an array of objects
  arraylen = json_object_array_length(medi_array);

  for (j = 0; j < arraylen; j++) {
    // get the i-th object in medi_array
    medi_array_obj = json_object_array_get_idx(medi_array, j);
    // get the name attribute in the i-th object
    medi_array_obj_name = json_object_object_get(medi_array_obj, "Proprietaire");
    char *id_a_check = json_object_get_string(medi_array_obj_name);
    appartient = true;
    for(int a = 0; proprio[a]!='\0'; a++){
      if(id_a_check[a]!=proprio[a])
        appartient = false;
    }
    if(appartient==true){
      if(count==choix-1){
        medi_array_obj_name = json_object_object_get(medi_array_obj, "Name");
        //printf("%s\n",json_object_get_string(medi_array_obj_name));
        *sauv = json_object_get_string(medi_array_obj_name);
      }
      count++;
    }
  }
}
//char *objet = "electronique";
//char *proprio ="Monsieur Durand";
//int choix = 2;
//char *sauvegarde_detail;
//afficher_choix_obj_du_proprio(objet, proprio, choix, &sauvegarde_detail);
//printf("%s\n", sauvegarde_detail);
