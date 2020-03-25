#ifndef __MODULE_H__
#define __MODULE_H__
#include <stdbool.h>

void afficher_liste_obj_raw(char *obj);
void afficher_detail_obj(char *obj, int choix);
void afficher_liste_obj(char *obj);
void chercher_mdp(char *iD, char **p);
bool existe_id(char *iD);
void stocker_id_mdp_inscription(char *iD, char *mdp);
void modifier_fichier_base_proto(void);
void admin_del_someone(int choix);
bool check_n_id_existe(int choix);
void print_id(int choix);
void fprint_id(int choix);
int num_id(char* iD);

#endif
