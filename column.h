#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <limits.h>
#define REALOCSIZE 256
#ifndef CDATAFRAME_CDATAFRAME_H
#define CDATAFRAME_CDATAFRAME_H
int taille_logique_max;


// Définir une énumération pour représenter les différents types de données
typedef enum {
    INT,
    FLOAT,
    DOUBLE,
    STRING,
} DataType;

// Structure pour représenter une colonne du DataFrame
typedef struct {
    char* title;
    int t_phy;
    int t_log;
    void* Tab; // Pointeur générique vers les données
    DataType type; // Type de données de la colonne
} COLUMN;

COLUMN *create_column(char* title, DataType type);

int insert_value(COLUMN* col, const void* value, int index);

void delete_column(COLUMN **col);

void print_col(COLUMN* col);

int occurences(void* x, COLUMN *col);

void * valeur_presente(int x, COLUMN *col);

int superieurs(void* x, COLUMN *col);

int inferieures(void* x, COLUMN *col);

int egales(void* x, COLUMN *col);

COLUMN* create_column(char* title, DataType type)
{
    COLUMN* new_column = malloc(sizeof(COLUMN));
    new_column->title = title;
    new_column->t_phy = 0;
    new_column->t_log = 0;
    new_column->Tab = NULL;
    new_column->type = type;

    return new_column;
}

int max_logical_size(COLUMN **CDataframe, int nombre_de_colonnes) {
    size_t max_size = 0;

    // Parcourir toutes les colonnes
    for (int i = 0; i < nombre_de_colonnes; ++i) {
        // Vérifier si la colonne est vide
        if (CDataframe[i]->t_log == 0) {
            return 0; // Si une colonne est vide, le DataFrame est vide
        }

        // Mettre à jour la taille logique maximale
        if (CDataframe[i]->t_log > max_size) {
            max_size = CDataframe[i]->t_log;
        }
    }

    return max_size;
}


int insert_value(COLUMN* col, const void* value, int index)
{
    if (col == NULL)
    {
        return 0;
    }

    // Allouer de l'espace mémoire si nécessaire
    if (col->t_log == col->t_phy || col->t_phy == 0)
    {
        int new_size = col->t_phy + REALOCSIZE;
        void* new_data = realloc(col->Tab, new_size * get_type_size(col->type));
        if (new_data == NULL)
        {
            return 0;
        }
        col->Tab = new_data;
        col->t_phy = new_size;
    }

    // Copier la valeur dans la colonne
    switch (col->type)
    {
        case INT:
            ((int*)(col->Tab))[index] = *((int*)value);
            break;
        case FLOAT:
            ((float*)(col->Tab))[index] = *((float*)value);
            break;
        case DOUBLE:
            ((double*)(col->Tab))[index] = *((double*)value);
            break;
        case STRING:
            ((char**)(col->Tab))[index] = strdup((char*)value);
            break;
        default:
            return 0; // Type non pris en charge
    }

    ++col->t_log;
    return 1;
}


void delete_column(COLUMN **col)
{
    if (col == NULL || *col == NULL)
    {
        return;
    }
    free((*col)->title);
    free((*col)->Tab);
    free(*col);
    *col = NULL; // Assurer que le pointeur passé en argument est mis à NULL après la suppression
}

void print_col(COLUMN* col)
{
    if (col == NULL || col->Tab == NULL)
    {
        printf("La colonne est vide ou non définie.");
        return;
    }
    switch (col->type)
    {
        case INT:
            for (int i = 0; i < col->t_log; i++)
            {
                printf("[%d]: %d\n", i, ((int*)(col->Tab))[i]);
            }
            break;
        case FLOAT:
            for (int i = 0; i < col->t_log; i++)
            {
                printf("[%d]: %.2f\n", i, ((float*)(col->Tab))[i]);
            }
            break;
        case DOUBLE:
            for (int i = 0; i < col->t_log; i++)
            {
                printf("[%d]: %.2lf\n", i, ((double*)(col->Tab))[i]);
            }
            break;
        default:
            printf("Type de données non pris en charge.\n");
            break;
    }
}

int occurences(void* x, COLUMN *col)
{
    int occurence = 0;
    if (col != NULL && col->Tab != NULL)
    {
        switch (col->type)
        {
            case INT:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (((int*)(col->Tab))[i] == *((int*)x))
                    {
                        ++occurence;
                    }
                }
                break;
            case FLOAT:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (((float*)(col->Tab))[i] == *((float*)x))
                    {
                        ++occurence;
                    }
                }
                break;
            case DOUBLE:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (((double*)(col->Tab))[i] == *((double*)x))
                    {
                        ++occurence;
                    }
                }
                break;
            case STRING:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (strcmp(((char**)(col->Tab))[i], (char*)x) == 0)
                    {
                        ++occurence;
                    }
                }
                break;
            default:
                break;
        }
    }
    return occurence;
}

void *valeur_presente(int x, COLUMN *col)
{
    if (col != NULL && col->Tab != NULL)
    {
        switch (col->type)
        {
            case INT:
                if (x >= 0 && x < col->t_log)
                    return &(((int*)(col->Tab))[x]);
                break;
            case FLOAT:
                if (x >= 0 && x < col->t_log)
                    return &(((float*)(col->Tab))[x]);
                break;
            case DOUBLE:
                if (x >= 0 && x < col->t_log)
                    return &(((double*)(col->Tab))[x]);
                break;
            case STRING:
                if (x >= 0 && x < col->t_log)
                    return ((char**)(col->Tab))[x];
                break;
            default:
                break;
        }
    }
    return NULL; // Retourner NULL si la colonne est NULL, si le tableau est NULL ou si l'index est invalide
}


int superieurs(void* x, COLUMN *col)
{
    int nombre = 0;
    if (col != NULL && col->Tab != NULL)
    {
        switch (col->type) {
            case INT:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (((int*)(col->Tab))[i] > *((int*)x))
                    {
                        ++nombre;
                    }
                }
                break;
            case FLOAT:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (((float*)(col->Tab))[i] > *((float*)x))
                    {
                        ++nombre;
                    }
                }
                break;
            case DOUBLE:
                for (int i = 0; i < col->t_log; ++i) {
                    if (((double*)(col->Tab))[i] > *((double*)x))
                    {
                        ++nombre;
                    }
                }
                break;
            case STRING:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (strcmp(((char**)(col->Tab))[i], (char*)x) > 0)
                    {
                        ++nombre;
                    }
                }
                break;
            default:
                break;
        }
    }
    return nombre;
}

int inferieures(void* x, COLUMN *col)
{
    int nombre = 0;
    if (col != NULL && col->Tab != NULL)
    {
        switch (col->type) {
            case INT:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (((int*)(col->Tab))[i] < *((int*)x))
                    {
                        ++nombre;
                    }
                }
                break;
            case FLOAT:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (((float*)(col->Tab))[i] < *((float*)x))
                    {
                        ++nombre;
                    }
                }
                break;
            case DOUBLE:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (((double*)(col->Tab))[i] < *((double*)x))
                    {
                        ++nombre;
                    }
                }
                break;
            case STRING:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (strcmp(((char**)(col->Tab))[i], (char*)x) < 0)
                    {
                        ++nombre;
                    }
                }
                break;
            default:
                break;
        }
    }
    return nombre;
}

int egales(void* x, COLUMN *col)
{
    int nombre = 0;
    if (col != NULL && col->Tab != NULL)
    {
        switch (col->type) {
            case INT:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (((int*)(col->Tab))[i] == *((int*)x))
                    {
                        ++nombre;
                    }
                }
                break;
            case FLOAT:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (((float*)(col->Tab))[i] == *((float*)x))
                    {
                        ++nombre;
                    }
                }
                break;
            case DOUBLE:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (((double*)(col->Tab))[i] == *((double*)x))
                    {
                        ++nombre;
                    }
                }
                break;
            case STRING:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (strcmp(((char**)(col->Tab))[i], (char*)x) == 0)
                    {
                        ++nombre;
                    }
                }
                break;
            default:
                break;
        }
    }
    return nombre;
}
