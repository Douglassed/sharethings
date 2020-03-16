#include "../include/json.h"
#include <stdio.h>
#include <json-c/json.h>

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
