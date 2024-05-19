#ifndef CDATAFRAM_E_CDATA_H
#define CDATAFRAM_E_CDATA_H
#include "column.h"
//Cdata
typedef struct
{
    int nb_colone;
    Column **col;
}Cdataframe;

Cdataframe *create_cdataframe();
void inser_value(Cdataframe *df, Column* col);
void remplir_col(Column *col);
void remplir_Cdata(Cdataframe *df);
void remplir_Cdata_dur(Cdataframe *df);
void afficher_Cdata(Cdataframe *df);
void affiche_partie_ligne(Cdataframe *df,int arret);
void affiche_partie_col(Cdataframe *df,int arret);
void ajout_ligne(Cdataframe *df,int *value);
void del_ligne(Cdataframe *df,int choix);
void ajout_colonne(Cdataframe *df, char *titre);
void del_col(Cdataframe *df, int choix);
void renommer_colonne(Cdataframe *df, int choix, char *nouveau_titre);
int valeur_existante(Cdataframe *df, int value);
void acces_valeur_cellule(Cdataframe *df, int choix_ligne, int choix_colonne, int new_value);
void afficher_noms_colonnes(Cdataframe *df);
int nb_ligne(Cdataframe *df);
int nb_col(Cdataframe *df);
int nb_egal(Cdataframe *df, int value);
int nb_sup(Cdataframe *df, int value);
int nb_inf(Cdataframe *df, int value);

#endif //CDATAFRAM_E_CDATA_H
