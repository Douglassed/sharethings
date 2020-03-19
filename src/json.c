#include <stdio.h>
#include <stdlib.h>
#include "../include/personnes.h"
#include "../include/ressources.h"
#include "../include/menus.h"
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
      medi_array_obj_name = json_object_object_get(medi_array_obj, "Description");//changer "vert" en détail à choisir
      // print out the name attribute
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
    int line_count_check = 0;
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

    /* Check choix autorisé */

    /*while (line_size >= 0)
      line_count_check++;
    if(choix>=line_count_check-2){
      printf("Choix invalide");
      //return 0;
    }*/

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
