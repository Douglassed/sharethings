#ifndef __MODULE_H__
#define __MODULE_H__
#include <stdbool.h>

void afficher_liste_obj_raw(char *obj);
void afficher_detail_obj(char *obj, int choix);
void afficher_liste_obj(char *obj);
void chercher_mdp(char *iD, char **p);
bool existe_id(char *iD);
void stocker_id_mdp_inscription(char *iD, int mdp);
void modifier_fichier_base_proto(void);
void admin_del_someone(int choix);
bool check_n_id_existe(int choix);
void print_id(int choix);
void fprint_id(int choix);
int num_id(char* iD);
int ligne_bonne_categorie(int choix);
int ligne_bon_obj(int num_cat, char *iD, char *Obj);
void del_ressource(int num_ligne);
void add_ressource(int num_ligne_cat, char *iD, char *Descr, char *ObjName, char *nom_pret);
void sauvegarder_detail_obj(char *obj, int choix, int choix_modif, char **sauv);
int quel_n_eme_obj(int l,int l_c);
void modif_ressource_sauf_pret(int num_cat, char *iD, char *ObjName, int choix_modif);
int afficher_liste_obj_du_proprio(char *obj,char *proprio);
void afficher_choix_obj_du_proprio(char *obj,char *proprio, int choix, char **sauv);
void savoir_nom_pret(char *obj, int choix, char **sauv);
int savoir_si_en_pret(char *obj, int choix);
void mettre_en_pret_ou_finir_le_pret(int num_cat, char *iD, char *ObjName, char *iD2);
void savoir_nom_proprio(char *obj, int choix, char **sauv);
void afficher_choix_desc_du_proprio(char *obj,char *proprio, int choix, char **sauv);
void add_hist(int num_ligne_pers, char *iD, int ope);
void afficher_liste_historique(char *iD);
void stocker_id_hist_inscription(char *iD);
int ligne_bonne_personne(char *iD);
void afficher_liste_historique_choix(char *iD, int J);
int afficher_liste_obj_emprunte(char *obj,char *emprunteur);
void avoir_choix_obj_du_emprunteur(char *cat,char *emprunteur, int choix, char **sauv, char **sauv2);






#endif
