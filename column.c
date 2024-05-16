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

