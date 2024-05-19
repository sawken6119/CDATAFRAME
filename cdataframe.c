#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "column.h"
#include "CDATA.h"
#define REALOC_SIZE 256
// Crée un nouveau dataframe de colonnes
Cdataframe *create_cdataframe()
{
    Cdataframe *df = (Cdataframe*)malloc(sizeof(Cdataframe)); // Alloue de la mémoire pour un nouveau dataframe
    if (df == NULL)
    {
        printf("Vide\n"); // Affiche un message si l'allocation de mémoire échoue
    }
    df->col = NULL; // Initialise le tableau des colonnes à NULL
    df->nb_colone = 0; // Initialise le nombre de colonnes à 0
    return df; // Retourne un pointeur vers le nouveau dataframe
}

// Insère une colonne dans le dataframe
void inser_value(Cdataframe *df, Column* col)
{
    df->nb_colone++; // Incrémente le nombre de colonnes
    df->col = realloc(df->col, df->nb_colone * sizeof(Column *)); // Réalloue de la mémoire pour le tableau des colonnes
    if (df->col == NULL) {
        fprintf(stderr, "Erreur lors de la réallocation mémoire pour le CDataframe.\n"); // Affiche un message si la réallocation échoue
    }
    df->col[df->nb_colone - 1] = col; // Ajoute la nouvelle colonne à la fin du tableau des colonnes
}

// Remplit une colonne avec des valeurs saisies par l'utilisateur
void remplir_col(Column *col)
{
    int value;
    while (value >= 0)
    {
        printf("Saisir une valeur : ");
        scanf("%d", &value); // Lit une valeur saisie par l'utilisateur
        if (value >= 0)
        {
            if (col->TL >= col->TP)
            {
                col->TP += REALOC_SIZE; // Augmente la taille physique de la colonne
                col->donne = (int *)realloc(col->donne, col->TP * sizeof(int)); // Réalloue de la mémoire pour le tableau des données
                if (col->donne == NULL)
                {
                    printf("Vide\n"); // Affiche un message si la réallocation échoue
                }
            }
            col->donne[col->TL++] = value; // Ajoute la nouvelle valeur et incrémente la taille logique
        }
    }
}

// Remplit le dataframe avec des valeurs saisies par l'utilisateur
void remplir_Cdata(Cdataframe *df)
{
    for(int i = 0; i < df->nb_colone; i++)
    {
        remplir_col(df->col[i]); // Remplit chaque colonne du dataframe
    }
}

// Remplit le dataframe avec des valeurs prédéfinies (données dures)
void remplir_Cdata_dur(Cdataframe *df)
{
    Column *col1 = create_column("Colonne 1");
    Column *col2 = create_column("Colonne 2");
    inser_value(df, col1);
    inser_value(df, col2);
    remplir_col(col1);
    remplir_col(col2);
}

// Affiche le contenu du dataframe
void afficher_Cdata(Cdataframe *df) {
    printf("Contenu du Cdataframe : \n");

    // Détermination de la largeur maximale pour chaque colonne
    int *colWidths = malloc(df->nb_colone * sizeof(int));
    for (int i = 0; i < df->nb_colone; i++) {
        int maxLength = strlen(df->col[i]->titre); // Longueur du titre de la colonne
        for (int j = 0; j < df->col[i]->TL; j++) {
            int length = snprintf(NULL, 0, "%d", df->col[i]->donne[j]); // Longueur de la représentation de la valeur
            if (length > maxLength) {
                maxLength = length; // Mise à jour de la longueur maximale
            }
        }
        colWidths[i] = maxLength;
    }

    // Affichage de la ligne supérieure
    printf("+");
    for (int i = 0; i < df->nb_colone; i++) {
        for (int k = 0; k < colWidths[i] + 2; k++) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    // Affichage des titres de colonnes
    printf("|");
    for (int i = 0; i < df->nb_colone; i++) {
        printf(" %-*s |", colWidths[i], df->col[i]->titre);
    }
    printf("\n");

    // Affichage de la ligne de séparation entre les titres et les valeurs
    printf("+");
    for (int i = 0; i < df->nb_colone; i++) {
        for (int k = 0; k < colWidths[i] + 2; k++) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    // Trouver le nombre maximal de lignes parmi toutes les colonnes
    int maxLignes = 0;
    for (int i = 0; i < df->nb_colone; i++) {
        if (df->col[i]->TL > maxLignes) {
            maxLignes = df->col[i]->TL;
        }
    }

    // Affichage des valeurs des colonnes
    for (int j = 0; j < maxLignes; j++) {
        printf("|");
        for (int i = 0; i < df->nb_colone; i++) {
            if (j < df->col[i]->TL) {
                printf(" %-*d |", colWidths[i], df->col[i]->donne[j]);
            } else {
                printf(" %-*s |", colWidths[i], "");
            }
        }
        printf("\n");
    }

    // Affichage de la ligne inférieure
    printf("+");
    for (int i = 0; i < df->nb_colone; i++) {
        for (int k = 0; k < colWidths[i] + 2; k++) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    free(colWidths); // Libère la mémoire allouée pour les largeurs de colonnes
}

// Affiche une partie des lignes du dataframe jusqu'à l'indice 'arret'
void affiche_partie_ligne(Cdataframe *df, int arret)
{
    printf("Affichage d'une partie des lignes de Cdataframe (limite : %d)\n", arret);
    for (int i = 0; i < df->nb_colone; i++)
    {
        printf("Colonne '%s' : \n", df->col[i]->titre);
        printf("Valeurs : ");
        for (int j = 0; j < arret && j < df->col[i]->TL; j++)
        {
            printf("%d ", df->col[i]->donne[j]);
        }
        printf("\n");
    }
}

// Affiche une partie des colonnes du dataframe jusqu'à l'indice 'arret'
void affiche_partie_col(Cdataframe *df, int arret)
{
    printf("Affichage d'une partie des colonnes de Cdataframe (limite : %d)\n", arret);
    for (int i = 0; i < df->nb_colone && i < arret; i++)
    {
        printf("Colonne '%s' : \n", df->col[i]->titre);
        printf("Valeurs : ");
        for (int j = 0; j < df->col[i]->TL; j++)
        {
            printf("%d ", df->col[i]->donne[j]);
        }
        printf("\n");
    }
}

// Ajoute une ligne de valeurs au dataframe
void ajout_ligne(Cdataframe *df, int *value)
{
    if (df->nb_colone == 0)
    {
        printf("Colonne vide\n");
        return;
    }
    for (int i = 0; i < df->nb_colone; i++)
    {
        Column *col = df->col[i];
        if (col->TL >= col->TP)
        {
            col->TP += REALOC_SIZE; // Augmente la taille physique de la colonne
            col->donne = realloc(col->donne, col->TP * sizeof(int)); // Réalloue de la mémoire pour le tableau des données
            if (col->donne == NULL)
            {
                printf("Vide\n"); // Affiche un message si la réallocation échoue
                return;
            }
        }
        col->donne[col->TL++] = value[i]; // Ajoute la nouvelle valeur et incrémente la taille logique
    }
}

// Supprime une ligne du dataframe à l'indice 'choix'
void del_ligne(Cdataframe *df, int choix)
{
    if (df->nb_colone == 0)
    {
        printf("Colonne vide\n");
        return;
    }
    for (int i = 0; i < df->nb_colone; i++)
    {
        Column* col = df->col[i];
        if (choix >= 0 && choix < col->TL)
        {
            for (int j = choix; j < col->TL - 1; j++)
            {
                col->donne[j] = col->donne[j + 1]; // Décale les éléments pour supprimer l'élément à 'choix'
            }
            col->TL--; // Décrémente la taille logique
        }
    }
}

// Ajoute une nouvelle colonne au dataframe avec le titre donné
void ajout_colonne(Cdataframe *df, char *titre)
{
    Column *new_column = create_column(titre); // Crée une nouvelle colonne
    inser_value(df, new_column); // Insère la nouvelle colonne dans le dataframe
    remplir_col(new_column); // Remplit la nouvelle colonne avec des valeurs saisies par l'utilisateur
}

// Supprime une colonne du dataframe à l'indice 'choix'
void del_col(Cdataframe *df, int choix)
{
    if (choix >= 0 && choix < df->nb_colone)
    {
        free(df->col[choix]); // Libère la mémoire de la colonne à supprimer
        for (int i = choix; i < df->nb_colone - 1; i++)
        {
            df->col[i] = df->col[i + 1]; // Décale les colonnes pour combler le trou
        }
        df->nb_colone--; // Décrémente le nombre de colonnes
    }
}

// Renomme une colonne du dataframe à l'indice 'choix' avec un nouveau titre
void renommer_colonne(Cdataframe *df, int choix, char *nouveau_titre)
{
    if (choix >= 0 && choix < df->nb_colone)
    {
        strcpy(df->col[choix]->titre, nouveau_titre); // Copie le nouveau titre dans le champ 'titre' de la colonne
    }
}

// Vérifie si une valeur existe dans le dataframe
int valeur_existante(Cdataframe *df, int value)
{
    for (int i = 0; i < df->nb_colone; i++)
    {
        for (int j = 0; j < df->col[i]->TL; j++)
        {
            if (df->col[i]->donne[j] == value)
            {
                return 1; // Retourne 1 si la valeur est trouvée
            }
        }
    }
    return 0; // Retourne 0 si la valeur n'est pas trouvée
}

// Accède et modifie la valeur d'une cellule du dataframe (ligne et colonne spécifiées)
void acces_valeur_cellule(Cdataframe *df, int choix_ligne, int choix_colonne, int new_value)
{
    if (choix_colonne >= 0 && choix_colonne < df->nb_colone && choix_ligne >= 0)
    {
        Column *col = df->col[choix_colonne];
        if (choix_ligne < col->TL)
        {
            col->donne[choix_ligne] = new_value; // Modifie la valeur de la cellule spécifiée
        }
    }
}

// Affiche les noms des colonnes du dataframe
void afficher_noms_colonnes(Cdataframe *df)
{
    printf("Noms des colonnes du CDataframe :\n");
    for (int i = 0; i < df->nb_colone; i++) {
        printf("%s\n", df->col[i]->titre); // Affiche le titre de chaque colonne
    }
}

// Retourne le nombre de lignes dans le dataframe
int nb_ligne(Cdataframe *df)
{
    if (df->nb_colone == 0)
    {
        return 0; // Retourne 0 si le dataframe n'a pas de colonnes
    }
    return df->col[0]->TL; // Retourne la taille logique de la première colonne
}

// Retourne le nombre de colonnes dans le dataframe
int nb_col(Cdataframe *df)
{
    return df->nb_colone; // Retourne le nombre de colonnes
}

// Retourne le nombre de valeurs égales à une valeur donnée dans le dataframe
int nb_egal(Cdataframe *df, int value)
{
    int nombre = 0;
    for (int i = 0; i < df->nb_colone; i++)
    {
        for (int j = 0; j < df->col[i]->TL; j++)
        {
            if (df->col[i]->donne[j] == value)
            {
                nombre++; // Incrémente le compteur si la valeur est trouvée
            }
        }
    }
    return nombre; // Retourne le nombre de valeurs égales à 'value'
}

// Retourne le nombre de valeurs supérieures à une valeur donnée dans le dataframe
int nb_sup(Cdataframe *df, int value)
{
    int nombre = 0;
    for (int i = 0; i < df->nb_colone; i++)
    {
        for (int j = 0; j < df->col[i]->TL; j++)
        {
            if (df->col[i]->donne[j] > value)
            {
                nombre++; // Incrémente le compteur si la valeur est supérieure à 'value'
            }
        }
    }
    return nombre; // Retourne le nombre de valeurs supérieures à 'value'
}

// Retourne le nombre de valeurs inférieures à une valeur donnée dans le dataframe
int nb_inf(Cdataframe *df, int value)
{
    int nombre = 0;
    for (int i = 0; i < df->nb_colone; i++)
    {
        for (int j = 0; j < df->col[i]->TL; j++)
        {
            if (df->col[i]->donne[j] < value)
            {
                nombre++; // Incrémente le compteur si la valeur est inférieure à 'value'
            }
        }
    }
    return nombre; // Retourne le nombre de valeurs inférieures à 'value'
}

