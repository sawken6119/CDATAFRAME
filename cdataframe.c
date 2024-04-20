#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "CDataframe.h"
#define MAX_STRING_LENGTH 20 // Longueur maximale des chaînes de caractères générées
int taille_logique_max;


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

void fill_empty_cells(COLUMN** CDataframe, int nombre_de_colonnes)
{
    size_t max_t_phy = 0; // Taille physique maximale parmi toutes les colonnes

    // Trouver la taille physique maximale
    for (int i = 0; i < nombre_de_colonnes; ++i) {
        if (CDataframe[i]->t_phy > max_t_phy) {
            max_t_phy = CDataframe[i]->t_phy;
        }
    }

    // Ajuster la taille physique de toutes les colonnes à la taille maximale
    for (int i = 0; i < nombre_de_colonnes; ++i) {
        if (CDataframe[i]->t_phy < max_t_phy) {
            CDataframe[i]->Tab = realloc(CDataframe[i]->Tab, max_t_phy * (CDataframe[i]->type == STRING ? sizeof(char*) : sizeof(int))); // Réallouer le tableau de données
            if (CDataframe[i]->Tab == NULL) {
                printf("Erreur lors de la réallocation de mémoire pour la colonne %s.\n", CDataframe[i]->title);
                exit(1);
            }
            CDataframe[i]->t_phy = max_t_phy; // Mettre à jour la taille physique
        }
    }

    // Remplir les cellules vides
    for (int i = 0; i < nombre_de_colonnes; ++i) {
        int* int_data = (int*)CDataframe[i]->Tab;
        float* float_data = (float*)CDataframe[i]->Tab;
        double* double_data = (double*)CDataframe[i]->Tab;
        char** str_data = (char**)CDataframe[i]->Tab;
        switch (CDataframe[i]->type) {
            case INT:
                for (size_t j = CDataframe[i]->t_log; j < max_t_phy; ++j) {
                    int_data[j] = INT_MAX; // Remplir avec INT_MAX
                }
                break;
            case FLOAT:
                for (size_t j = CDataframe[i]->t_log; j < max_t_phy; ++j) {
                    float_data[j] = FLT_MAX; // Remplir avec FLT_MAX (pour les flottants)
                }
                break;
            case DOUBLE:
                for (size_t j = CDataframe[i]->t_log; j < max_t_phy; ++j) {
                    double_data[j] = DBL_MAX; // Remplir avec DBL_MAX (pour les doubles)
                }
                break;
            case STRING:
                for (size_t j = CDataframe[i]->t_log; j < max_t_phy; ++j) {
                    str_data[j] = strdup(""); // Remplir avec une chaîne vide
                }
                break;
            default:
                printf("Type de données non pris en charge pour la colonne %s.\n", CDataframe[i]->title);
                exit(1);
        }
    }
}

void remplissage_utilisateur(COLUMN **CDataframe, int nombre_de_colonnes)
{
    // Demande à l'utilisateur de saisir les valeurs pour chaque colonne
    for (int i = 0; i < nombre_de_colonnes; ++i)
    {
        printf("Remplissage de la colonne %d avec des valeurs fournies par l'utilisateur :\n", i+1);
        CDataframe[i] = malloc(sizeof(COLUMN));

        // Saisie du titre de la colonne
        char titre[MAX_STRING_LENGTH];
        printf("Entrer le titre de la colonne %d : ", i + 1);
        scanf("%s", titre);
        // Allocation de mémoire pour le titre de la colonne
        CDataframe[i]->title = malloc((MAX_STRING_LENGTH + 1) * sizeof(char)); // +1 pour le caractère nul
        strcpy(CDataframe[i]->title, titre);

        char type_input[20]; // Définir un tableau de caractères pour stocker l'entrée de l'utilisateur
        DataType  d;

        printf("Entrer le type de ses données (INT, FLOAT, DOUBLE, STRING) : ");
        scanf("%s", type_input);

        // Convertir la chaîne en majuscules pour la comparaison
        for (int k = 0; type_input[k]; k++) {
            type_input[k] = toupper(type_input[k]);
        }

        // Comparer l'entrée avec les types attendus
        if (strcmp(type_input, "INT") == 0) {
            d = INT;
        } else if (strcmp(type_input, "FLOAT") == 0) {
            d = FLOAT;
        } else if (strcmp(type_input, "DOUBLE") == 0) {
            d = DOUBLE;
        } else if (strcmp(type_input, "STRING") == 0) {
            d = STRING;
        } else {
            printf("Type de données non pris en charge. Utiliser INT, FLOAT, DOUBLE ou STRING.\n");
            // Gérer le cas où le type n'est pas pris en charge
            return;
        }

        CDataframe[i]->type = d;

        int nb_valeurs;
        printf("Entrer le nombre de valeurs pour la colonne %d : ", i+1);
        scanf("%d", &nb_valeurs);

        printf("Entrer les valeurs pour la colonne %d :\n", i+1);
        for (int j = 0; j < nb_valeurs; ++j)
        {
            // Demander à l'utilisateur d'entrer une valeur en fonction du type de données
            switch (d) {
                case INT: {
                    int valeur;
                    printf("Valeur %d : ", j + 1);
                    scanf("%d", &valeur);
                    insert_value(CDataframe[i], &valeur, CDataframe[i]->t_log);
                    break;
                }
                case FLOAT: {
                    float valeur;
                    printf("Valeur %d : ", j + 1);
                    scanf("%f", &valeur);
                    insert_value(CDataframe[i], &valeur,CDataframe[i]->t_log);
                    break;
                }
                case DOUBLE: {
                    double valeur;
                    printf("Valeur %d : ", j + 1);
                    scanf("%lf", &valeur);
                    insert_value(CDataframe[i], &valeur,CDataframe[i]->t_log);
                    break;
                }
                case STRING: {
                    char* valeur = malloc(MAX_STRING_LENGTH + 1); // Allouer de la mémoire pour la chaîne de caractères
                    if (valeur != NULL)
                    {
                        printf("Valeur %d : ", j + 1);
                        scanf("%s", valeur);
                        insert_value(CDataframe[i], valeur, CDataframe[i]->t_log);
                    }
                    break;
                }
                default:
                    printf("Type de données non pris en charge pour la colonne %d.\n", i + 1);
                    return;
            }
        }
    }

    fill_empty_cells(CDataframe, nombre_de_colonnes);
}


void remplissage_dur(COLUMN **CDataframe, int nombre_de_colonnes)
{
    // Initialiser le générateur de nombres aléatoires avec le temps actuel
    srand(time(NULL));

    // Tableau de titres aléatoires possibles
    char *titres[] = {
            "Age",
            "Taille",
            "Poids",
            "Score",
            "Nom",
            "Prénom",
            "ID"};

    // Remplissage en dur des valeurs pour chaque colonne
    for (int i = 0; i < nombre_de_colonnes; ++i)
    {
        // Générer un titre aléatoire
        int random_index = rand() % (sizeof(titres) / sizeof(titres[0]));
        char *titre = titres[random_index];

        printf("Remplissage en dur de la colonne %d (%s) avec des valeurs aléatoires :\n", i + 1, titre);

        // Allouer de la mémoire et copier le titre dans la colonne
        CDataframe[i] = malloc(sizeof(COLUMN));
        CDataframe[i]->title = malloc(strlen(titre) + 1);
        strcpy(CDataframe[i]->title, titre);

        // Déterminer le type de données en fonction du titre de la colonne
        if (strcmp(titre, "Age") == 0 || strcmp(titre, "Taille") == 0 || strcmp(titre, "Poids") == 0 || strcmp(titre, "Score") == 0 || strcmp(titre, "ID") == 0)
        {
            CDataframe[i]->type = INT;
        }
        else if (strcmp(titre, "Nom") == 0 || strcmp(titre, "Prénom") == 0)
        {
            CDataframe[i]->type = STRING;
        }
        else
        {
            printf("Type de données non pris en charge pour la colonne %s.\n", titre);
            continue;
        }

        // Générer et insérer des valeurs aléatoires dans la colonne en fonction du type de données
        switch (CDataframe[i]->type)
        {
            case INT:
                for (int j = 0; j < 100; ++j) // Générer 100 valeurs aléatoires pour INT
                {
                    int valeur = rand() % 100;
                    insert_value(CDataframe[i], &valeur,CDataframe[i]->t_log); // Générer un nombre aléatoire entre 0 et 99 pour INT
                }
                break;
            case STRING:
                for (int j = 0; j < 100; ++j) // Générer 100 valeurs aléatoires pour STRING
                {
                    char *valeur = malloc(MAX_STRING_LENGTH + 1); // Allouer de la mémoire pour la chaîne de caractères
                    if (valeur != NULL)
                    {
                        // Générer une chaîne de caractères aléatoire avec une longueur maximale définie
                        for (int k = 0; k < MAX_STRING_LENGTH; ++k)
                        {
                            valeur[k] = 'a' + rand() % 26; // Générer un caractère aléatoire entre 'a' et 'z'
                        }
                        valeur[MAX_STRING_LENGTH] = '\0'; // Ajouter le caractère de fin de chaîne
                        insert_value(CDataframe[i], valeur,CDataframe[i]->t_log);
                    }
                }
                break;
            default:
                printf("Type de données non pris en charge pour la colonne %s.\n", CDataframe[i]->title);
                break;
        }
    }
}

void print_DataFrame(COLUMN **CDataframe, int nombre_de_colonnes)
{
    // Vérification si le DataFrame est NULL
    if (CDataframe == NULL)
    {
        printf("Le DataFrame est NULL.\n");
        return;
    }

    // Déterminer la largeur maximale de chaque colonne pour l'alignement
    int *max_width = malloc(nombre_de_colonnes * sizeof(int));
    for (int i = 0; i < nombre_de_colonnes; ++i)
    {
        max_width[i] = strlen(CDataframe[i]->title);
        for (int j = 0; j < CDataframe[i]->t_log; ++j)
        {
            int width = 0;
            switch (CDataframe[i]->type)
            {
                case INT:
                    width = snprintf(NULL, 0, "%d", *((int *)(CDataframe[i]->Tab) + j));
                    break;
                case FLOAT:
                    width = snprintf(NULL, 0, "%.2f", *((float *)(CDataframe[i]->Tab) + j));
                    break;
                case DOUBLE:
                    width = snprintf(NULL, 0, "%.2lf", *((double *)(CDataframe[i]->Tab) + j));
                    break;
                case STRING:
                    width = strlen(*((char **)(CDataframe[i]->Tab) + j));
                    break;
                default:
                    break;
            }
            if (width > max_width[i])
                max_width[i] = width;
        }
    }

    // Imprimer les bordures supérieures
    printf("+");
    for (int i = 0; i < nombre_de_colonnes; ++i)
    {
        for (int j = 0; j < max_width[i] + 2; ++j)
        {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    // Imprimer les titres des colonnes
    printf("|");
    for (int i = 0; i < nombre_de_colonnes; ++i)
    {
        printf(" %-*s |", max_width[i], CDataframe[i]->title);
    }
    printf("\n");

    // Imprimer les bordures intermédiaires
    printf("+");
    for (int i = 0; i < nombre_de_colonnes; ++i)
    {
        for (int j = 0; j < max_width[i] + 2; ++j)
        {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    int max_val = CDataframe[0]->t_log;
    for (int i = 1; i < nombre_de_colonnes; ++i)
    {
        if(max_val < CDataframe[i]->t_log)
            max_val = CDataframe[i]->t_log;
    }

    // Imprimer les valeurs
    for (int row = 0; row < max_val; ++row)
    {
        printf("|");
        for (int col = 0; col < nombre_de_colonnes; ++col)
        {
            char str[20];
            switch (CDataframe[col]->type)
            {
                case INT:
                    if (*((int*)(CDataframe[col]->Tab) + row) != INT_MAX)
                        printf(" %-*d |", max_width[col], *((int *)(CDataframe[col]->Tab) + row));
                    else
                        printf(" %-*s |", max_width[col], "null");
                    break;
                case FLOAT:
                    if (*((int*)(CDataframe[col]->Tab) + row) != FLT_MAX)
                        printf(" %-*.*f |", max_width[col], 2, *((float *)(CDataframe[col]->Tab) + row));
                    else
                        printf(" %-*s |", max_width[col], "null");
                    break;
                case DOUBLE:
                    if (*((int*)(CDataframe[col]->Tab) + row) != DBL_MAX)
                        printf(" %-*.*lf |", max_width[col], 2, *((double *)(CDataframe[col]->Tab) + row));
                    else
                        printf(" %-*s |", max_width[col], "null");
                    break;
                case STRING:
                    if (strlen(*((char **)(CDataframe[col]->Tab) + row)) == 0)
                        printf(" %-*s |", max_width[col], *((char **)(CDataframe[col]->Tab) + row));
                    else
                        printf(" %-*s |", max_width[col], "null");
                    break;
                default:
                    break;
            }
        }
        printf("\n");
    }

    // Imprimer les bordures inférieures
    printf("+");
    for (int i = 0; i < nombre_de_colonnes; ++i)
    {
        for (int j = 0; j < max_width[i] + 2; ++j)
        {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    // Libérer la mémoire allouée pour max_width
    free(max_width);
}


void print_partial_row_data(COLUMN** CDataframe, int nombre_de_colonnes, int start_index, int end_index)
{
    // Vérification si le DataFrame est NULL
    if (CDataframe == NULL)
    {
        printf("Le DataFrame est NULL.\n");
        return;
    }

    // Vérification des limites
    if (start_index < 0 || start_index >= end_index || end_index > CDataframe[0]->t_log)
    {
        printf("Limites invalides.\n");
        return;
    }

    // Déterminer la largeur maximale de chaque colonne pour l'alignement
    int *max_width = malloc(nombre_de_colonnes * sizeof(int));
    for (int i = 0; i < nombre_de_colonnes; ++i)
    {
        max_width[i] = strlen(CDataframe[i]->title);
        for (int j = start_index; j < end_index; ++j)
        {
            int width = 0;
            switch (CDataframe[i]->type)
            {
                case INT:
                    if (j < CDataframe[i]->t_log)
                        width = snprintf(NULL, 0, "%d", *((int *)(CDataframe[i]->Tab) + j));
                    break;
                case FLOAT:
                    if (j < CDataframe[i]->t_log)
                        width = snprintf(NULL, 0, "%.2f", *((float *)(CDataframe[i]->Tab) + j));
                    break;
                case DOUBLE:
                    if (j < CDataframe[i]->t_log)
                        width = snprintf(NULL, 0, "%.2lf", *((double *)(CDataframe[i]->Tab) + j));
                    break;
                case STRING:
                    if (j < CDataframe[i]->t_log)
                        width = strlen(*((char **)(CDataframe[i]->Tab) + j));
                    break;
                default:
                    break;
            }
            if (width > max_width[i])
                max_width[i] = width;
        }
    }

    // Imprimer les bordures supérieures
    printf("+");
    for (int i = 0; i < nombre_de_colonnes; ++i)
    {
        for (int j = 0; j < max_width[i] + 2; ++j)
        {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    // Imprimer les titres des colonnes
    printf("|");
    for (int i = 0; i < nombre_de_colonnes; ++i)
    {
        printf(" %-*s |", max_width[i], CDataframe[i]->title);
    }
    printf("\n");

    // Imprimer les bordures intermédiaires
    printf("+");
    for (int i = 0; i < nombre_de_colonnes; ++i)
    {
        for (int j = 0; j < max_width[i] + 2; ++j)
        {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    // Imprimer les valeurs
    for (int row = start_index; row < end_index; ++row)
    {
        printf("|");
        for (int col = 0; col < nombre_de_colonnes; ++col)
        {
            switch (CDataframe[col]->type)
            {
                case INT:
                    if (row < CDataframe[col]->t_log)
                        printf(" %-*d |", max_width[col], *((int *)(CDataframe[col]->Tab) + row));
                    else
                        printf(" %-*s |", max_width[col], "null");
                    break;
                case FLOAT:
                    if (row < CDataframe[col]->t_log)
                        printf(" %-*.*f |", max_width[col], 2, *((float *)(CDataframe[col]->Tab) + row));
                    else
                        printf(" %-*s |", max_width[col], "null");
                    break;
                case DOUBLE:
                    if (row < CDataframe[col]->t_log)
                        printf(" %-*.*lf |", max_width[col], 2, *((double *)(CDataframe[col]->Tab) + row));
                    else
                        printf(" %-*s |", max_width[col], "null");
                    break;
                case STRING:
                    if (row < CDataframe[col]->t_log)
                        printf(" %-*s |", max_width[col], *((char **)(CDataframe[col]->Tab) + row));
                    else
                        printf(" %-*s |", max_width[col], "null");
                    break;
                default:
                    break;
            }
        }
        printf("\n");
    }

    // Imprimer les bordures inférieures
    printf("+");
    for (int i = 0; i < nombre_de_colonnes; ++i)
    {
        for (int j = 0; j < max_width[i] + 2; ++j)
        {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    // Libérer la mémoire allouée pour max_width
    free(max_width);
}

void print_partial_column_data(COLUMN **CDataframe, int nombre_de_colonnes, int start_index, int end_index)
{
    // Vérification si le DataFrame est NULL
    if (CDataframe == NULL)
    {
        printf("Le DataFrame est NULL.\n");
        return;
    }

    // Vérification des limites
    if (start_index < 0 || start_index >= end_index || end_index > CDataframe[0]->t_log)
    {
        printf("Limites invalides.\n");
        return;
    }

    printf("Affichage des colonnes de %d à %d :\n", start_index, end_index - 1);

    // Calcul de la largeur de chaque colonne
    int *largeur_colonne = (int*)malloc(nombre_de_colonnes * sizeof(int));
    for (int j = start_index; j < end_index; ++j)
    {
        largeur_colonne[j] = strlen(CDataframe[j]->title) + 2; // Ajouter 2 pour l'espace autour du titre
        for (int i = 0; i < CDataframe[j]->t_log; ++i)
        {
            switch (CDataframe[j]->type)
            {
                case INT:
                    if (i < CDataframe[j]->t_log)
                        largeur_colonne[j] = fmax(largeur_colonne[j], snprintf(NULL, 0, "%d", *((int *)(CDataframe[j]->Tab) + i)) + 2);
                    break;
                case FLOAT:
                    if (i < CDataframe[j]->t_log)
                        largeur_colonne[j] = fmax(largeur_colonne[j], snprintf(NULL, 0, "%.2f", *((float *)(CDataframe[j]->Tab) + i)) + 2);
                    break;
                case DOUBLE:
                    if (i < CDataframe[j]->t_log)
                        largeur_colonne[j] = fmax(largeur_colonne[j], snprintf(NULL, 0, "%.2lf", *((double *)(CDataframe[j]->Tab) + i)) + 2);
                    break;
                case STRING:
                    if (i < CDataframe[j]->t_log)
                        largeur_colonne[j] = fmax(largeur_colonne[j], strlen(*((char **)(CDataframe[j]->Tab) + i)) + 2);
                    break;
                default:
                    break;
            }
        }
    }

    // Affichage de la bordure supérieure
    printf("+");
    for (int j = start_index; j < end_index; ++j)
    {
        for (int k = 0; k < largeur_colonne[j]; ++k)
        {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    // Affichage des titres des colonnes
    printf("|");
    for (int j = start_index; j < end_index; ++j)
    {
        printf(" %-*s|", largeur_colonne[j] - 2, CDataframe[j]->title);
    }
    printf("\n");

    // Affichage de la ligne de séparation
    printf("+");
    for (int j = start_index; j < end_index; ++j)
    {
        for (int k = 0; k < largeur_colonne[j]; ++k)
        {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    // Affichage des données des colonnes
    for (int i = 0; i < CDataframe[0]->t_log; ++i)
    {
        printf("|");
        for (int j = start_index; j < end_index; ++j)
        {
            // Vérification si la colonne ou ses données sont NULL
            if (CDataframe[j] == NULL || CDataframe[j]->Tab == NULL)
            {
                printf(" %-*s|", largeur_colonne[j] - 2, "La colonne est vide");
                continue;
            }

            switch (CDataframe[j]->type)
            {
                case INT:
                    if (i < CDataframe[j]->t_log)
                        printf(" %-*d|", largeur_colonne[j] - 2, *((int *)(CDataframe[j]->Tab) + i));
                    else
                        printf(" %-*s|", largeur_colonne[j] - 2, "null");
                    break;
                case FLOAT:
                    if (i < CDataframe[j]->t_log)
                        printf(" %-*.*f|", largeur_colonne[j] - 2, 2, *((float *)(CDataframe[j]->Tab) + i));
                    else
                        printf(" %-*s|", largeur_colonne[j] - 2, "null");
                    break;
                case DOUBLE:
                    if (i < CDataframe[j]->t_log)
                        printf(" %-*.*lf|", largeur_colonne[j] - 2, 2, *((double *)(CDataframe[j]->Tab) + i));
                    else
                        printf(" %-*s|", largeur_colonne[j] - 2, "null");
                    break;
                case STRING:
                    if (i < CDataframe[j]->t_log)
                        printf(" %-*s|", largeur_colonne[j] - 2, *((char **)(CDataframe[j]->Tab) + i));
                    else
                        printf(" %-*s|", largeur_colonne[j] - 2, "null");
                    break;
                default:
                    printf("Type de données non pris en charge |");
                    break;
            }
        }
        printf("\n");
    }

    // Affichage de la bordure inférieure
    printf("+");
    for (int j = start_index; j < end_index; ++j)
    {
        for (int k = 0; k < largeur_colonne[j]; ++k)
        {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    // Libération de la mémoire
    free(largeur_colonne);
}




void add_column(COLUMN*** CDataframe, int* nombre_de_colonnes, char* title, int type, void* values, int size)
{
    // Vérifier si CDataframe est NULL
    if (*CDataframe == NULL) {
        printf("Le CDataframe est NULL.\n");
        return;
    }

    // Allouer de la mémoire pour la nouvelle colonne
    COLUMN* new_column = (COLUMN*)malloc(sizeof(COLUMN));
    if (new_column == NULL) {
        printf("Erreur lors de l'allocation de mémoire pour la nouvelle colonne.\n");
        return;
    }

    // Initialiser la nouvelle colonne
    new_column->title = title;
    new_column->type = type;
    new_column->t_log = size; // Supposons que les valeurs sont déjà présentes dans le tableau values
    new_column->t_phy = size + REALOCSIZE; // Réserver de l'espace supplémentaire
    new_column->Tab = values;

    // Réallouer de la mémoire pour le tableau de pointeurs de colonnes
    *CDataframe = (COLUMN**)realloc(*CDataframe, (*nombre_de_colonnes + 1) * sizeof(COLUMN*));
    if (*CDataframe == NULL) {
        printf("Erreur lors de la réallocation de mémoire pour le CDataframe.\n");
        free(new_column); // Libérer la mémoire allouée pour la nouvelle colonne
        return;
    }

    // Ajouter la nouvelle colonne au CDataframe
    (*CDataframe)[*nombre_de_colonnes] = new_column;
    ++(*nombre_de_colonnes);

    printf("La colonne '%s' a été ajoutée avec succès.\n", title);
}



void delete_row(COLUMN** CDataframe, int nombre_de_colonnes, int index) {
    if (CDataframe == NULL || index < 0) {
        printf("Paramètres non valides.\n");
        return;
    }

    // Vérifier que l'index est valide pour toutes les colonnes
    for (int i = 0; i < nombre_de_colonnes; ++i) {
        if (CDataframe[i] == NULL) {
            printf("Indice de ligne invalide pour la colonne %s.\n", CDataframe[i]->title);
            return;
        }
    }

    // Supprimer la ligne pour chaque colonne
    for (int i = 0; i < nombre_de_colonnes; ++i) {
        // Supprimer la ligne en décalant les valeurs vers la gauche
        size_t s = get_type_size(CDataframe[i]->type);
        for (int j = index; j < CDataframe[i]->t_log - 1; ++j) {
            memcpy(((char*)(CDataframe[i]->Tab)) + j * s,
                   ((char*)(CDataframe[i]->Tab)) + (j + 1) * s,
                   s);
        }
        // Décrémenter le compteur de lignes
        --CDataframe[i]->t_log;

        // Réduire la taille physique du tableau si nécessaire
        if (CDataframe[i]->t_log < CDataframe[i]->t_phy - REALOCSIZE) {
            int new_size = CDataframe[i]->t_log + REALOCSIZE;
            void* new_tab = realloc(CDataframe[i]->Tab, new_size * s);
            if (new_tab == NULL) {
                printf("Erreur lors de la réallocation de mémoire pour la colonne %s.\n", CDataframe[i]->title);
                return;
            }
            CDataframe[i]->Tab = new_tab;
            CDataframe[i]->t_phy = new_size;
        }
    }
}


void add_row(COLUMN** CDataframe, int nombre_de_colonnes, void** values) {
    // Vérification des paramètres d'entrée
    if (CDataframe == NULL || values == NULL) {
        printf("Paramètres non valides.\n");
        return;
    }

    // Ajout des nouvelles valeurs à chaque colonne
    for (int i = 0; i < nombre_de_colonnes; ++i) {
        // Vérifier le type de la valeur
        if (values[i] == NULL) {
            printf("Valeur NULL pour la colonne %s.\n", CDataframe[i]->title);
            return;
        }

        taille_logique_max = max_logical_size(CDataframe, nombre_de_colonnes);
        // Insérer la valeur dans la colonne correspondante
        switch (CDataframe[i]->type) {
            case INT:
                if (!insert_value(CDataframe[i], (int*)values[i], taille_logique_max)) {
                    printf("Erreur lors de l'insertion de valeurs dans la colonne %s.\n", CDataframe[i]->title);
                    // Annuler les opérations précédentes en cas d'erreur
                    for (int j = i - 1; j >= 0; --j) {
                        delete_row(CDataframe,nombre_de_colonnes, CDataframe[j]->t_log - 1);
                    }
                    return;
                }
                break;
            case FLOAT:
                if (!insert_value(CDataframe[i], (float*)values[i], taille_logique_max)) {
                    printf("Erreur lors de l'insertion de valeurs dans la colonne %s.\n", CDataframe[i]->title);
                    // Annuler les opérations précédentes en cas d'erreur
                    for (int j = i - 1; j >= 0; --j) {
                        delete_row(CDataframe,nombre_de_colonnes, CDataframe[j]->t_log - 1);
                    }
                    return;
                }
                break;
            case DOUBLE:
                if (!insert_value(CDataframe[i], (double*)values[i], taille_logique_max)) {
                    printf("Erreur lors de l'insertion de valeurs dans la colonne %s.\n", CDataframe[i]->title);
                    // Annuler les opérations précédentes en cas d'erreur
                    for (int j = i - 1; j >= 0; --j) {
                        delete_row(CDataframe,nombre_de_colonnes, CDataframe[j]->t_log - 1);
                    }
                    return;
                }
                break;
            case STRING:
                if (!insert_value(CDataframe[i], (char*)values[i], taille_logique_max)) {
                    printf("Erreur lors de l'insertion de valeurs dans la colonne %s.\n", CDataframe[i]->title);
                    // Annuler les opérations précédentes en cas d'erreur
                    for (int j = i - 1; j >= 0; --j) {
                        delete_row(CDataframe,nombre_de_colonnes, CDataframe[j]->t_log - 1);
                    }
                    return;
                }
                break;
            default:
                printf("Type de données non pris en charge pour la colonne %s.\n", CDataframe[i]->title);
                return;
        }

    }
}

void delete_column_CDataframe(COLUMN*** CDataframe, int* nombre_de_colonnes, int index)
{
    // Vérification si CDataframe est NULL ou si l'index est hors limites
    if (*CDataframe == NULL || index < 0 || index >= *nombre_de_colonnes) {
        printf("Index invalide ou CDataframe est NULL.\n");
        return;
    }

    // Libérer la mémoire pour la colonne à supprimer
    free((*CDataframe)[index]->title);
    free((*CDataframe)[index]->Tab);
    free((*CDataframe)[index]);

    // Déplacer les colonnes suivantes pour remplir le trou
    for (int i = index; i < *nombre_de_colonnes - 1; ++i) {
        (*CDataframe)[i] = (*CDataframe)[i + 1];
    }

    // Réduire la taille du tableau de pointeurs de colonnes
    COLUMN** temp = (COLUMN**)realloc(*CDataframe, (*nombre_de_colonnes - 1) * sizeof(COLUMN*));
    if (temp == NULL && *nombre_de_colonnes > 1) {
        printf("Erreur lors de la réallocation de mémoire pour le CDataframe.\n");
        return;
    }

    *CDataframe = temp;
    --(*nombre_de_colonnes);

    printf("La colonne à l'index %d a été supprimée avec succès.\n", index);
}

void rename_column(COLUMN** CDataframe, int nombre_de_colonnes, int index, char* new_title)
{
    // Vérification si CDataframe est NULL ou si l'index est hors limites
    if (CDataframe == NULL || index < 0 || index >= nombre_de_colonnes) {
        printf("Index invalide ou CDataframe est NULL.\n");
        return;
    }

    // Libérer l'ancien titre de la colonne
    free(CDataframe[index]->title);

    // Allouer de la mémoire pour le nouveau titre
    CDataframe[index]->title = strdup(new_title);  // strdup alloue et copie la chaîne

    if (CDataframe[index]->title == NULL) {
        printf("Erreur lors de l'allocation de mémoire pour le nouveau titre.\n");
        return;
    }

    printf("La colonne à l'index %d a été renommée avec succès en '%s'.\n", index, new_title);
}

int value_exists_in_column(COLUMN* column, void* value)
{
    if (column == NULL || column->Tab == NULL) {
        return 0;  // La colonne est vide ou NULL
    }

    int size = column->t_log;  // Taille logique de la colonne

    switch (column->type) {
        case INT:
            for (int i = 0; i < size; ++i) {
                if (*((int*)column->Tab + i) == *((int*)value)) {
                    return 1;  // La valeur existe dans la colonne
                }
            }
            break;
        case FLOAT:
            for (int i = 0; i < size; ++i) {
                if (*((float*)column->Tab + i) == *((float*)value)) {
                    return 1;  // La valeur existe dans la colonne
                }
            }
            break;
        case DOUBLE:
            for (int i = 0; i < size; ++i) {
                if (*((double*)column->Tab + i) == *((double*)value)) {
                    return 1;  // La valeur existe dans la colonne
                }
            }
            break;
        case STRING:
            for (int i = 0; i < size; ++i) {
                if (strcmp(*((char**)column->Tab + i), (char*)value) == 0) {
                    return 1;  // La valeur existe dans la colonne
                }
            }
            break;
        default:
            printf("Type de données non pris en charge.\n");
            break;
    }

    return 0;  // La valeur n'existe pas dans la colonne
}

int value_exists_in_CDataframe(COLUMN** CDataframe, int nombre_de_colonnes, void* value)
{
    if (CDataframe == NULL || value == NULL) {
        printf("CDataframe est NULL ou la valeur est NULL.\n");
        return 0;
    }

    for (int i = 0; i < nombre_de_colonnes; ++i) {
        if (value_exists_in_column(CDataframe[i], value)) {
            return 1;  // La valeur existe dans au moins une colonne
        }
    }

    return 0;  // La valeur n'existe pas dans le CDataframe
}
