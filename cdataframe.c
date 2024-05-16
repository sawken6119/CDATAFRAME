#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CDataframe.h"

//Cdata
Cdataframe *create_cdataframe()
{
    Cdataframe *df = (Cdataframe*)malloc(sizeof(Cdataframe));
    if (df == NULL)
    {
        printf("Vide\n");
    }
    df->col = NULL;
    df->nb_colone = 0;
    return df;
}
void inser_value(Cdataframe *df, Column* col)
{
    df->nb_colone++;
    df->col = realloc(df->col, df->nb_colone * sizeof(Column *));
    if (df->col == NULL) {
        fprintf(stderr, "Erreur lors de la réallocation mémoire pour le CDataframe.\n");
    }
    df->col[df->nb_colone - 1] = col;
}

void remplir_col(Column *col)
{
    int value;
    while (value >= 0 )
    {
        printf("Saisir une valeur : ");
        scanf("%d", &value);
        if (value >= 0)
        {
            if (col->TL >= col->TP)
            {
                col->TP += REALOC_SIZE;
                col->donne = (int *)realloc(col->donne, col->TP * sizeof(int));
                if (col->donne == NULL)
                {
                    printf("Vide\n");
                }
            }
            col->donne[col->TL++] = value;
        }
    }
}

void remplir_Cdata(Cdataframe *df)
{
    for(int i = 0; i< df->nb_colone;i++)
    {
        remplir_col(df->col[i]);
    }
}
void remplir_Cdata_dur(Cdataframe *df)
{
    Column *col1 = create_column("Colonne 1");
    Column *col2 = create_column("Colonne 2");
    remplir_Cdata(col1);
    remplir_Cdata(col2);
}
void afficher_Cdata(Cdataframe *df) {
    printf("Contenu du Cdataframe : \n");

    // Détermination de la largeur maximale pour chaque colonne
    int *colWidths = malloc(df->nb_colone * sizeof(int));
    for (int i = 0; i < df->nb_colone; i++) {
        int maxLength = strlen(df->col[i]->titre);
        for (int j = 0; j < df->col[i]->TL; j++) {
            int length = snprintf(NULL, 0, "%d", df->col[i]->donne[j]);
            if (length > maxLength) {
                maxLength = length;
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

    free(colWidths);
}
void affiche_partie_ligne(Cdataframe *df,int arret)
{
    printf("Affichage d'une partie des lignes de Cdataframe(limite : %d",arret);
    for (int i = 0; i< df->nb_colone;i++)
    {
        printf("Colonne '%s : \n",df->col[i]->titre);
        printf("Valeurs :");
    }
    for (int i,j = 0 ; j < arret && j < df->col[i]->TL;j++)
    {
        printf("%d",df->col[i]->donne[j]);
    }
    printf("\n");
}
void affiche_partie_col(Cdataframe *df,int arret)
{
    printf("Affichage d'une partie des colonnes de Cdataframe(limite : %d",arret);
    for (int i = 0; i< df->nb_colone && i< arret ;i++)
    {
        printf("Colonne '%s : \n",df->col[i]->titre);
        printf("Valeurs :");
    }
    for (int i,j = 0 ; j < df->col[i]->TL;j++)
    {
        printf("%d",df->col[i]->donne[j]);
    }
    printf("\n");
}
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
            col->TP += REALOC_SIZE;
            col->donne = realloc(col->donne, col->TP * sizeof(int));
            if (col->donne == NULL)
            {
                printf("Vide\n");
                return;
            }
        }
        col->donne[col->TL++] = value[i];
    }
}
void del_ligne(Cdataframe *df,int choix)
{
    if(df->nb_colone == 0)
    {
        printf("Colonne vide\n");
    }
    for (int i = 0; i<df->nb_colone;i++)
    {
        Column* col = df->col[i];
        if (choix >= 0 && choix < col->TL )
        {
            for(int j = choix; j < col->TL-1;j++)
            {
                col->donne[j]=col->donne[j+1];
            }
            col->TL--;
        }
    }
}
void ajout_colonne(Cdataframe *df, char *titre)
{
    Column *new_column = create_column(titre);
    inser_value(df, new_column);
    remplir_col(new_column);
}
void del_col(Cdataframe *df, int choix)
{
    if (choix >= 0 && choix < df->nb_colone)
    {
        free(df->col[choix]);
        for (int i =choix; i < df->nb_colone - 1; i++)
        {
            df->col[i] = df->col[i + 1];
        }
        df->nb_colone--;
    }
}
void renommer_colonne(Cdataframe *df, int choix, char *nouveau_titre)
{
    if (choix >= 0 && choix < df->nb_colone)
    {
        strcpy(df->col[choix]->titre, nouveau_titre);
    }
}

int valeur_existante(Cdataframe *df, int value)
{
    for (int i = 0; i < df->nb_colone; i++)
    {
        for (int j = 0; j < df->col[i]->TL; j++)
        {
            if (df->col[i]->donne[j] == value)
            {
                return 1;
            }
        }
    }
    return 0;
}
void acces_valeur_cellule(Cdataframe *df, int choix_ligne, int choix_colonne, int new_value)
{
    if (choix_colonne >= 0 && choix_colonne < df->nb_colone && choix_ligne >= 0)
    {
        Column *col = df->col[choix_colonne];
        if (choix_ligne < col->TL)
        {
            col->donne[choix_ligne] = new_value;
        }
    }
}
void afficher_noms_colonnes(Cdataframe *df)
{
    printf("Noms des colonnes du CDataframe :\n");
    for (int i = 0; i < df->nb_colone; i++) {
        printf("%s\n", df->col[i]->titre);
    }
}
int nb_ligne(Cdataframe *df)
{
    if(df->nb_colone == 0)
    {
        return 0;
    }
    return df->col[0]->TL;
}
int nb_col(Cdataframe *df)
{
    return df->nb_colone;
}
int nb_egal(Cdataframe *df, int value)
{
    int nombre = 0;
    for(int i = 0; i < df-> nb_colone;i++)
    {
        for(int j =0; j < df->col[i]->TL;j++)
        {
            if(df->col[i]->donne[j]==value)
            {
                nombre ++;
            }
        }
    }
    return nombre;
}
int nb_sup(Cdataframe *df, int value)
{
    int nombre = 0;
    for(int i = 0; i < df-> nb_colone;i++)
    {
        for(int j =0; j < df->col[i]->TL;j++)
        {
            if(df->col[i]->donne[j] > value)
            {
                nombre ++;
            }
        }
    }
    return nombre;
}
int nb_inf(Cdataframe *df, int value)
{
    int nombre = 0;
    for(int i = 0; i < df-> nb_colone;i++)
    {
        for(int j =0; j < df->col[i]->TL;j++)
        {
            if(df->col[i]->donne[j] < value)
            {
                nombre ++;
            }
        }
    }
    return nombre;
}
