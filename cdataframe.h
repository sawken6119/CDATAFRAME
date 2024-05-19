#ifndef CDATAFRAM_E_CDATA_H
#define CDATAFRAM_E_CDATA_H
#include "column.h"
// Structure pour représenter un dataframe de colonnes
typedef struct
{
    int nb_colone; // Nombre de colonnes dans le dataframe
    Column **col; // Tableau de pointeurs vers des colonnes
} Cdataframe;

// Crée un nouveau dataframe de colonnes
Cdataframe *create_cdataframe();

// Insère une colonne dans le dataframe
void inser_value(Cdataframe *df, Column* col);

// Remplit une colonne avec des valeurs
void remplir_col(Column *col);

// Remplit le dataframe avec des colonnes et des valeurs
void remplir_Cdata(Cdataframe *df);

// Remplit le dataframe avec des valeurs dures (prédéfinies)
void remplir_Cdata_dur(Cdataframe *df);

// Affiche le contenu du dataframe
void afficher_Cdata(Cdataframe *df);

// Affiche une partie des lignes du dataframe jusqu'à l'indice 'arret'
void affiche_partie_ligne(Cdataframe *df, int arret);

// Affiche une partie des colonnes du dataframe jusqu'à l'indice 'arret'
void affiche_partie_col(Cdataframe *df, int arret);

// Ajoute une ligne de valeurs au dataframe
void ajout_ligne(Cdataframe *df, int *value);

// Supprime une ligne du dataframe à l'indice 'choix'
void del_ligne(Cdataframe *df, int choix);

// Ajoute une nouvelle colonne au dataframe avec le titre donné
void ajout_colonne(Cdataframe *df, char *titre);

// Supprime une colonne du dataframe à l'indice 'choix'
void del_col(Cdataframe *df, int choix);

// Renomme une colonne du dataframe à l'indice 'choix' avec un nouveau titre
void renommer_colonne(Cdataframe *df, int choix, char *nouveau_titre);

// Vérifie si une valeur existe dans le dataframe
int valeur_existante(Cdataframe *df, int value);

// Accède et modifie la valeur d'une cellule du dataframe (ligne et colonne spécifiées)
void acces_valeur_cellule(Cdataframe *df, int choix_ligne, int choix_colonne, int new_value);

// Affiche les noms des colonnes du dataframe
void afficher_noms_colonnes(Cdataframe *df);

// Retourne le nombre de lignes dans le dataframe
int nb_ligne(Cdataframe *df);

// Retourne le nombre de colonnes dans le dataframe
int nb_col(Cdataframe *df);

// Retourne le nombre de valeurs égales à une valeur donnée dans le dataframe
int nb_egal(Cdataframe *df, int value);

// Retourne le nombre de valeurs supérieures à une valeur donnée dans le dataframe
int nb_sup(Cdataframe *df, int value);

// Retourne le nombre de valeurs inférieures à une valeur donnée dans le dataframe
int nb_inf(Cdataframe *df, int value);


#endif //CDATAFRAM_E_CDATA_H
