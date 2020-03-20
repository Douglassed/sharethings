#ifndef __MODULE_H__
#define __MODULE_H__
#include <stdbool.h>

void afficher_liste_obj_raw(char *);
void afficher_detail_obj(char *, int);
void afficher_liste_obj(char *);
void chercher_mdp(char *, char **);
bool existe_id(char *);
void stocker_id_mdp_inscription(char *, char *);
void modifier_fichier_base_proto(void);
void admin_del_someone(int);
bool check_n_id_existe(int);
void print_id(int);

#endif
