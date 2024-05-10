#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "column.h"
#define REALOC_SIZE 256

Column *create_column(char *title)
{
    Column *nouvelle_col = (Column*)malloc(sizeof(Column));
    if (nouvelle_col == NULL)
    {
        printf("Vide\n");
    }
    strcpy(nouvelle_col->titre, title);
    nouvelle_col->donne = NULL;
    nouvelle_col->TL = 0;
    nouvelle_col->TP = 0;
    return nouvelle_col;
}
int insert_value(Column* col, int value)
{
    if(col->TL >= col->TP)
    {
        if(col->TL == 0)
        {
            col->TP += REALOC_SIZE;
            col->donne = (int*)malloc(col->TL * sizeof(int));
        }
        else
        {
            col->TP += REALOC_SIZE;
            col->donne = (int *)realloc(col->donne, col->TP * sizeof(int));
        }
        if (col->donne == NULL)
        {
            printf("Vide\n");
        }
    }
    col->donne[col->TL++] = value;
    return 1;
}
void delete_column(Column **col)
{
    free((*col)->donne); // Libere le tableau de donées
    (*col)->donne = NULL;

    free(col); // Libere la structure de la colonne
}

void print_col(Column* col)
{
    if (col == NULL || col->donne == NULL)
    {
        printf("Vide");
    }
    for(int i = 0; i< col->TL;i++)
    {
        printf("[%d] %d\n",i,col->donne[i]);
    }
}
void nb_occurences(Column* col, int value)
{
    int occurences = 0;
    for (int i = 0; i < col->TL;i++)
    {
        if (col->donne[i] == value)
        {
            occurences++;
        }

    }
}
void value_present(Column* col, int x)
{
    printf("La valeur présente à la position %d est %d\n",x,col->donne[x]);
}
void value_sup(Column* col, int value)
{
    int nombre = 0;
    for (int i = 0; i< col->TL;i++)
    {
        if (col->donne[i] > value)
            nombre++;

    }
    printf("Le nombre de valeurs supérieures à %d est %d\n",value,nombre);
}
void value_inf(Column* col, int value)
{
    int nombre = 0;
    for (int i = 0; i< col->TL;i++)
    {
        if (col->donne[i] < value)
            nombre++;

    }
    printf("Le nombre de valeurs inférieures à %d est %d\n",value,nombre);
}
void value_egal(Column* col, int value)
{
    int nombre = 0;
    for (int i = 0; i< col->TL;i++)
    {
        if (col->donne[i] == value)
            nombre++;

    }
    printf("Le nombre de valeurs égales à %d est %d\n",value,nombre);
}
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
void afficher_Cdata(Cdataframe *df)
{
    printf("Contenu du Cdataframe : \n");

    // Détermination de la longueur maximale des titres de colonnes
    int maxLength = 0;
    for (int i = 0; i < df->nb_colone; i++)
    {
        int length = strlen(df->col[i]->titre);
        if (length > maxLength)
        {
            maxLength = length;
        }
    }

    // Affichage des titres de colonnes
    for (int i = 0; i < df->nb_colone; i++)
    {
        printf("%-*s     ", maxLength, df->col[i]->titre); // Utilisation de la largeur maximale pour l'alignement
    }
    printf("   \n   ");

    // Affichage des valeurs alignées sous les titres de colonnes
    for (int i = 0; i < df->nb_colone; i++)
    {
        for (int j = 0; j < maxLength; j++)
        {
            printf(" ");
        }
        printf(" "); // Espace entre le titre et les valeurs
    }
    printf("\n");

    // Trouver le nombre maximal de lignes parmi toutes les colonnes
    int maxLignes = 0;
    for (int i = 0; i < df->nb_colone; i++)
    {
        if (df->col[i]->TL > maxLignes)
        {
            maxLignes = df->col[i]->TL;
        }
    }

    // Affichage des valeurs des colonnes
    for (int j = 0; j < maxLignes; j++)
    {
        for (int i = 0; i < df->nb_colone; i++)
        {
            if (j < df->col[i]->TL)
            {
                printf("   %-*d", maxLength, df->col[i]->donne[j]); // Utilisation de la largeur maximale pour l'alignement
            }
            else
            {
                printf("%-*s ", maxLength, ""); // Affiche un espace pour les cellules manquantes
            }
        }
        printf("\n");
    }
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
