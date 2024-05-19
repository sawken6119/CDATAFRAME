#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "column.h"
#define REALOC_SIZE 256


// Crée une nouvelle colonne avec le titre donné
Column *create_column(char *title)
{
    Column *nouvelle_col = (Column*)malloc(sizeof(Column)); // Alloue de la mémoire pour une nouvelle colonne
    if (nouvelle_col == NULL)
    {
        printf("Vide\n"); // Affiche un message si l'allocation de mémoire échoue
    }
    strcpy(nouvelle_col->titre, title); // Copie le titre dans la nouvelle colonne
    nouvelle_col->donne = NULL; // Initialise le tableau des données à NULL
    nouvelle_col->TL = 0; // Initialise la taille logique à 0
    nouvelle_col->TP = 0; // Initialise la taille physique à 0
    return nouvelle_col; // Retourne un pointeur vers la nouvelle colonne
}

// Insère une valeur dans la colonne donnée
int insert_value(Column* col, int value)
{
    // Vérifie si la taille logique dépasse ou égale à la taille physique
    if(col->TL >= col->TP)
    {
        if(col->TL == 0)
        {
            col->TP += REALOC_SIZE; // Augmente la taille physique de REALOC_SIZE
            col->donne = (int*)malloc(col->TP * sizeof(int)); // Alloue de la mémoire pour le tableau des données
        }
        else
        {
            col->TP += REALOC_SIZE; // Augmente la taille physique de REALOC_SIZE
            col->donne = (int *)realloc(col->donne, col->TP * sizeof(int)); // Réalloue de la mémoire pour le tableau des données
        }
        if (col->donne == NULL)
        {
            printf("Vide\n"); // Affiche un message si l'allocation de mémoire échoue
        }
    }
    col->donne[col->TL++] = value; // Ajoute la nouvelle valeur et incrémente la taille logique
    return 1; // Retourne 1 pour indiquer le succès de l'insertion
}

// Supprime la colonne et libère la mémoire associée
void delete_column(Column **col)
{
    free((*col)->donne); // Libère la mémoire du tableau des données
    (*col)->donne = NULL; // Met le pointeur du tableau de données à NULL

    free(*col); // Libère la mémoire de la structure de la colonne
    *col = NULL; // Met le pointeur de la colonne à NULL
}

// Affiche les valeurs de la colonne
void print_col(Column* col)
{
    if (col == NULL || col->donne == NULL)
    {
        printf("Vide"); // Affiche un message si la colonne ou le tableau de données est vide
    }
    for(int i = 0; i < col->TL; i++)
    {
        printf("[%d] %d\n", i, col->donne[i]); // Affiche chaque valeur avec son indice
    }
}

// Compte le nombre d'occurrences d'une valeur donnée dans la colonne
void nb_occurences(Column* col, int value)
{
    int occurences = 0; // Initialise le compteur d'occurrences à 0
    for (int i = 0; i < col->TL; i++)
    {
        if (col->donne[i] == value)
        {
            occurences++; // Incrémente le compteur si la valeur est trouvée
        }
    }
    printf("Le nombre d'occurrences de %d est %d\n", value, occurences); // Affiche le nombre d'occurrences
}

// Vérifie si une valeur donnée est présente à une position donnée dans la colonne
void value_present(Column* col, int x)
{
    if (x < col->TL && x >= 0)
    {
        printf("La valeur présente à la position %d est %d\n", x, col->donne[x]); // Affiche la valeur à la position donnée
    }
    else
    {
        printf("Position invalide\n"); // Affiche un message si la position est invalide
    }
}

// Affiche le nombre de valeurs de la colonne qui sont supérieures à une valeur donnée
void value_sup(Column* col, int value)
{
    int nombre = 0; // Initialise le compteur de valeurs à 0
    for (int i = 0; i < col->TL; i++)
    {
        if (col->donne[i] > value)
            nombre++; // Incrémente le compteur si la valeur est supérieure à celle donnée
    }
    printf("Le nombre de valeurs supérieures à %d est %d\n", value, nombre); // Affiche le nombre de valeurs supérieures
}

// Affiche le nombre de valeurs de la colonne qui sont inférieures à une valeur donnée
void value_inf(Column* col, int value)
{
    int nombre = 0; // Initialise le compteur de valeurs à 0
    for (int i = 0; i < col->TL; i++)
    {
        if (col->donne[i] < value)
            nombre++; // Incrémente le compteur si la valeur est inférieure à celle donnée
    }
    printf("Le nombre de valeurs inférieures à %d est %d\n", value, nombre); // Affiche le nombre de valeurs inférieures
}

// Affiche le nombre de valeurs de la colonne qui sont égales à une valeur donnée
void value_egal(Column* col, int value)
{
    int nombre = 0; // Initialise le compteur de valeurs à 0
    for (int i = 0; i < col->TL; i++)
    {
        if (col->donne[i] == value)
            nombre++; // Incrémente le compteur si la valeur est égale à celle donnée
    }
    printf("Le nombre de valeurs égales à %d est %d\n", value, nombre); // Affiche le nombre de valeurs égales
}

