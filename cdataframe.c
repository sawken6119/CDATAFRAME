#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CDataframe.h"
#define REALOCSIZE 256

COLUMN* create_column(char* title)
{
    COLUMN* new_column = malloc(sizeof(COLUMN));
    new_column->title = title;
    new_column->t_phy = 0;
    new_column->t_log = 0;
    new_column->Tab = NULL;

    return new_column;
}

int insert_value(COLUMN* col, int value)
{
    if (col->t_log == col->t_phy || col->t_phy == 0)
    {
        int new_size = col->t_phy + REALOCSIZE;
        void* new_data = realloc(col->Tab, new_size * sizeof(int));
        if (new_data == NULL) {
            return 0;
        }
        col->Tab = new_data;
        col->t_phy = new_size;
    }
    ((int*)(col->Tab))[col->t_log] = value;
    ++col->t_log;

    return 1;
}

void delete_column(COLUMN* col)
{
    if (col == NULL)
    {
        return;
    }
    free(col->title);
    free(col->Tab);
    free(col);
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

int occurences(int x, COLUMN *col)
{
    int occurence = 0;
    if (col != NULL && col->Tab != NULL)
    {
        switch (col->type)
        {
            case INT:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (((int*)(col->Tab))[i] == x)
                    {
                        ++occurence;
                    }
                }
                break;
            case FLOAT:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (((float*)(col->Tab))[i] == (float)x)
                    {
                        ++occurence;
                    }
                }
                break;
            case DOUBLE:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (((double*)(col->Tab))[i] == (double)x)
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


int valeur_presente(int x, COLUMN *col)
{
    if (col != NULL && col->Tab != NULL && x >= 0 && x < col->t_log)
    {
        switch (col->type)
        {
            case INT:
                return ((int*)(col->Tab))[x];
            case FLOAT:
                return (int)(((float*)(col->Tab))[x]);
            case DOUBLE:
                return (int)(((double*)(col->Tab))[x]);
            default:
                break;
        }
    }
    return -1; // Retourner une valeur par défaut si la valeur n'est pas présente ou si l'index est invalide
}



int superieurs(int x, COLUMN *col)
{
    int nombre = 0;
    if (col != NULL && col->Tab != NULL)
    {
        switch (col->type) {
            case INT:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (((int*)(col->Tab))[i] > x)
                    {
                        ++nombre;
                    }
                }
                break;
            case FLOAT:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (((float*)(col->Tab))[i] > (float)x)
                    {
                        ++nombre;
                    }
                }
                break;
            case DOUBLE:
                for (int i = 0; i < col->t_log; ++i) {
                    if (((double*)(col->Tab))[i] > (double)x) {
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

int inferieures(int x, COLUMN *col)
{
    int nombre = 0;
    if (col != NULL && col->Tab != NULL)
    {
        switch (col->type) {
            case INT:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (((int*)(col->Tab))[i] < x)
                    {
                        ++nombre;
                    }
                }
                break;
            case FLOAT:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (((float*)(col->Tab))[i] < (float)x)
                    {
                        ++nombre;
                    }
                }
                break;
            case DOUBLE:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (((double*)(col->Tab))[i] < (double)x)
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

int egales(int x, COLUMN *col)
{
    int nombre = 0;
    if (col != NULL && col->Tab != NULL)
    {
        switch (col->type) {
            case INT:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (((int*)(col->Tab))[i] == x)
                    {
                        ++nombre;
                    }
                }
                break;
            case FLOAT:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (((float*)(col->Tab))[i] == (float)x)
                    {
                        ++nombre;
                    }
                }
                break;
            case DOUBLE:
                for (int i = 0; i < col->t_log; ++i)
                {
                    if (((double*)(col->Tab))[i] == (double)x)
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

void remplissage_utilisateur(COLUMN **CDataframe, int nombre_de_colonnes)
{
    // Demande à l'utilisateur de saisir les valeurs pour chaque colonne
    for (int i = 0; i < nombre_de_colonnes; ++i)
    {
        printf("Remplissage de la colonne %d avec des valeurs fournies par l'utilisateur :\n", i+1);

        int nb_valeurs;
        printf("Entrer le nombre de valeurs pour la colonne %d : ", i+1);
        scanf("%d", &nb_valeurs);

        printf("Entrer les valeurs pour la colonne %d :\n", i+1);
        for (int j = 0; j < nb_valeurs; ++j)
        {
            int valeur;
            printf("Valeur %d : ", j + 1);
            scanf("%d", &valeur);
            insert_value(CDataframe[i], valeur);
        }
    }
}

void remplissage_dur(COLUMN **CDataframe, int nombre_de_colonnes)
{
    // Initialiser le générateur de nombres aléatoires avec le temps actuel
    srand(time(NULL));

    // Remplissage en dur des valeurs pour chaque colonne
    for (int i = 0; i < nombre_de_colonnes; ++i)
    {
        printf("Remplissage en dur de la colonne %d avec des valeurs aléatoires :\n", i+1);

        // Générer et insérer des valeurs aléatoires dans la colonne
        int nb_valeurs = rand() % 100 + 1; // Générer un nombre aléatoire entre 1 et 100
        for (int j = 0; j < nb_valeurs; ++j)
        {
            int valeur = rand() % 100; // Générer un nombre aléatoire entre 0 et 99
            insert_value(CDataframe[i], valeur);
        }
    }
}

void print_DataFrame(COLUMN **CDataframe, int nombre_de_colonnes)
{
    if (CDataframe == NULL)
    {
        printf("Le DataFrame est NULL\n");
        return;
    }

    for (int i = 0; i < nombre_de_colonnes; ++i)
    {
        printf("%s\n", CDataframe[i]->title);
        switch (CDataframe[i]->type)
        {
            case INT:
                for (int j = 0; j < CDataframe[i]->t_log; ++j)
                    printf("%d ", ((int*)(CDataframe[i]->Tab))[j]); // Cast et accès aux valeurs comme des entiers
                break;
            case FLOAT:
                for (int j = 0; j < CDataframe[i]->t_log; ++j)
                    printf("%f ", ((float*)(CDataframe[i]->Tab))[j]); // Cast et accès aux valeurs comme des flottants
                break;
            case DOUBLE:
                for (int j = 0; j < CDataframe[i]->t_log; ++j)
                    printf("%lf ", ((double*)(CDataframe[i]->Tab))[j]); // Cast et accès aux valeurs comme des doubles
                break;
            case STRING:
                for (int j = 0; j < CDataframe[i]->t_log; ++j)
                    printf("%s ", ((char*)(CDataframe[i]->Tab))[j]); // Cast et accès aux valeurs comme des doubles
                break;
            default:
                printf("Type de données non pris en charge.\n");
        }
        printf("\n");
    }
}

void print_partial_data(COLUMN** CDataframe, int nombre_de_colonnes, int start_index, int end_index)
{
    if (CDataframe == NULL)
    {
        printf("Le DataFrame est NULL.\n");
        return;
    }

    // Vérification des limites
    if (start_index < 0 || start_index >= end_index || end_index > CDataframe[0]->t_phy)
    {
        printf("Limites invalides.\n");
        return;
    }

    printf("Affichage des lignes de %d à %d :\n", start_index, end_index - 1);
    for (int i = start_index; i < end_index; ++i)
    {
        printf("Ligne %d :\n", i);
        for (int j = 0; j < nombre_de_colonnes; ++j)
        {
            printf("%s: ", CDataframe[j]->title);
            switch (CDataframe[j]->type)
            {
                case INT:
                    printf("%d\n", *((int*)(CDataframe[j]->Tab) + i));
                    break;
                case FLOAT:
                    printf("%.2f\n", *((float*)(CDataframe[j]->Tab) + i));
                    break;
                case DOUBLE:
                    printf("%.2lf\n", *((double*)(CDataframe[j]->Tab) + i));
                    break;
                default:
                    printf("Type de données non pris en charge.\n");
                    break;
            }
        }
        printf("\n");
    }
}

void add_column(COLUMN*** CDataframe, int* nombre_de_colonnes, char* title, DataType type)
{
    // Réallocation de mémoire pour ajouter une nouvelle colonne
    COLUMN** new_CDataframe = realloc(*CDataframe, (*nombre_de_colonnes + 1) * sizeof(COLUMN*));
    if (new_CDataframe == NULL)
    {
        printf("Erreur lors de l'ajout de la colonne.\n");
        return;
    }
    *CDataframe = new_CDataframe;

    // Création de la nouvelle colonne
    (*CDataframe)[*nombre_de_colonnes] = create_column(title);
    if ((*CDataframe)[*nombre_de_colonnes] == NULL)
    {
        printf("Erreur lors de la création de la colonne.\n");
        return;
    }

    // Incrémentation du nombre de colonnes
    (*nombre_de_colonnes)++;
}

size_t get_type_size(int type)
{
    switch (type)
    {
        case INT:
            return sizeof(int);
        case FLOAT:
            return sizeof(float);
        case DOUBLE:
            return sizeof(double);
        case STRING:
            return sizeof(char*);
            // Ajoutez d'autres types si nécessaire
        default:
            return 0; // Type non pris en charge
    }
}

void delete_row(COLUMN* col, int index, int type)
{
    if (col == NULL || col->Tab == NULL || index < 0 || index >= col->t_log)
    {
        printf("Indice de ligne invalide.\n");
        return;
    }

    // Suppression en fonction du type de données de la colonne
    switch (type) {
        case INT:
            // Suppression d'une valeur entière
            for (int i = index; i < col->t_log - 1; ++i)
            {
                ((int*)(col->Tab))[i] = ((int*)(col->Tab))[i + 1];
            }
            break;
        case FLOAT:
            // Suppression d'une valeur flottante
            for (int i = index; i < col->t_log - 1; ++i)
            {
                ((float*)(col->Tab))[i] = ((float*)(col->Tab))[i + 1];
            }
            break;
        case DOUBLE:
            // Suppression d'une valeur double
            for (int i = index; i < col->t_log - 1; ++i)
            {
                ((double*)(col->Tab))[i] = ((double*)(col->Tab))[i + 1];
            }
            break;
        case STRING:
            // Ici, vous devez implémenter la logique pour supprimer une chaîne de caractères de la colonne
            break;
            // Ajoutez d'autres cas pour d'autres types si nécessaire
        default:
            printf("Type de données non pris en charge pour la colonne.\n");
            return;
    }

    // Décrémentation du compteur de lignes
    --col->t_log;

    // Réduction de la taille physique du tableau si nécessaire
    if (col->t_log < col->t_phy - REALOCSIZE)
    {
        int new_size = col->t_log + REALOCSIZE;
        void* new_tab = realloc(col->Tab, new_size * get_type_size(type));
        if (new_tab == NULL)
        {
            printf("Erreur lors de la réallocation de mémoire.\n");
            return;
        }
        col->Tab = new_tab;
        col->t_phy = new_size;
    }
}

void add_row(COLUMN** CDataframe, int nombre_de_colonnes, void** values, int* types)
{
    // Vérification des paramètres d'entrée
    if (CDataframe == NULL || values == NULL || types == NULL)
    {
        printf("Paramètres non valides.\n");
        return;
    }

    // Ajout des nouvelles valeurs à chaque colonne
    for (int i = 0; i < nombre_de_colonnes; ++i)
    {
        // Convertir le pointeur void * en un type approprié en fonction du type de la colonne
        switch (types[i]) {
            case INT:
                if (!insert_value(CDataframe[i], *(int*)values[i]))
                {
                    printf("Erreur lors de l'insertion de valeurs dans la colonne %s.\n", CDataframe[i]->title);
                    // Annuler les opérations précédentes en cas d'erreur
                    for (int j = i - 1; j >= 0; --j) {
                        delete_row(CDataframe[j], CDataframe[j]->t_log - 1,CDataframe[i]->type);
                    }
                    return;
                }
                break;
            case FLOAT:
                if (!insert_value(CDataframe[i], *(float*)values[i])) {
                    printf("Erreur lors de l'insertion de valeurs dans la colonne %s.\n", CDataframe[i]->title);
                    // Annuler les opérations précédentes en cas d'erreur
                    for (int j = i - 1; j >= 0; --j) {
                        delete_row(CDataframe[j], CDataframe[j]->t_log - 1,CDataframe[i]->type);
                    }
                    return;
                }
                break;
            case DOUBLE:
                if (!insert_value(CDataframe[i], *(double*)values[i])) {
                    printf("Erreur lors de l'insertion de valeurs dans la colonne %s.\n", CDataframe[i]->title);
                    // Annuler les opérations précédentes en cas d'erreur
                    for (int j = i - 1; j >= 0; --j) {
                        delete_row(CDataframe[j], CDataframe[j]->t_log - 1,CDataframe[i]->type);
                    }
                    return;
                }
                break;
            case STRING:
                // Insérer une chaîne de caractères dans la colonne
                if (!insert_value(CDataframe[i], *(char*)values[i])) {
                    printf("Erreur lors de l'insertion de valeurs dans la colonne %s.\n", CDataframe[i]->title);
                    // Annuler les opérations précédentes en cas d'erreur
                    for (int j = i - 1; j >= 0; --j) {
                        delete_row(CDataframe[j], CDataframe[j]->t_log - 1, CDataframe[i]->type);
                    }
                    return;
                }
                break;
                // Ajoutez d'autres cas pour d'autres types si nécessaire
            default:
                printf("Type de données non pris en charge pour la colonne %s.\n", CDataframe[i]->title);
                return;
        }
    }
}

void delete_colum(COLUMN*** CDataframe, int* nombre_de_colonnes, int index)
{
    if (CDataframe == NULL || *CDataframe == NULL || index < 0 || index >= *nombre_de_colonnes)
    {
        printf("Index de colonne invalide.\n");
        return;
    }

    // Libérer la mémoire utilisée par la colonne
    delete_column((*CDataframe)[index]);

    // Décaler les colonnes restantes dans le tableau
    for (int i = index; i < *nombre_de_colonnes - 1; ++i)
    {
        (*CDataframe)[i] = (*CDataframe)[i + 1];
    }

    // Réallouer la mémoire pour le tableau de colonnes
    COLUMN** new_CDataframe = realloc(*CDataframe, (*nombre_de_colonnes - 1) * sizeof(COLUMN*));
    if (new_CDataframe == NULL)
    {
        printf("Erreur lors de la suppression de la colonne.\n");
        return;
    }
    *CDataframe = new_CDataframe;

    // Décrémenter le nombre de colonnes
    (*nombre_de_colonnes)--;
}

void rename_column(COLUMN* col, char* new_title)
{
    if (col == NULL || new_title == NULL)
    {
        printf("Colonne ou titre invalide.\n");
        return;
    }
    free(col->title);
    col->title = strcpy(new_title,col->title );
    if (col->title == NULL)
    {
        printf("Donner un nom.\n");
        return;
    }
}

int value_exist(COLUMN* col, int x)
{
    if (col == NULL || col->Tab == NULL)
    {
        printf("Vide ou Pas défini.\n");
        return 0;
    }

    for (int i = 0; i < col->t_log; ++i)
    {
        if (col->Tab == x)
        {
            printf("%d est dans le tableau",x);
        }
        else
        {
            printf("%d n'est pas dans le tableau\n",x);
        }
    }
    return 0;
}

int acces(COLUMN* col, int row_index)
{
    if (col == NULL || col->Tab == NULL || row_index < 0 || row_index >= col->t_log)
    {
        printf("Index de ligne invalide.\n");
        return 1;
    }
    return col->Tab[row_index];
}

void replace_value(COLUMN* col, int row_index, int new_value)
{
    if (col == NULL || col->Tab == NULL || row_index < 0 || row_index >= col->t_log)
    {
        printf("Index de ligne invalide.\n");
        return;
    }

    col->Tab[row_index] = new_value;
}

void print_column_names(COLUMN** CDataframe, int nombre_de_colonnes)
{
    if (CDataframe == NULL)
    {
        printf("Le DataFrame est NULL.\n");
        return;
    }

    printf("Noms des colonnes :\n");
    for (int i = 0; i < nombre_de_colonnes; ++i)
    {
        printf("%d. %s\n", i + 1, CDataframe[i]->title);
    }
}

int get_row_count(COLUMN* col)
{
    if (col == NULL)
    {
        printf("Colonne non définie.\n");
        return 0;
    }
    return col->t_log;
}

int get_row_coun(COLUMN* col)
{
    if (col == NULL)
    {
        printf("Colonne non définie.\n");
        return 0;
    }
    return col->t_log;
}

int get_column_count(int nombre_de_colonnes)
{
    return nombre_de_colonnes;
}

int count_cells_equal_to(COLUMN** CDataframe, int nombre_de_colonnes, int x)
{
    int count = 0;
    for (int i = 0; i < nombre_de_colonnes; ++i)
    {
        count += egales(x, CDataframe[i]);
    }
    return count;
}

int count_cells_greater_than(COLUMN** CDataframe, int nombre_de_colonnes, int x)
{
    int count = 0;
    for (int i = 0; i < nombre_de_colonnes; ++i)
    {
        count += superieurs(x, CDataframe[i]);
    }
    return count;
}

int count_cells_less_than(COLUMN** CDataframe, int nombre_de_colonnes, int x)
{
    int count = 0;
    for (int i = 0; i < nombre_de_colonnes; ++i)
    {
        count += inferieures(x, CDataframe[i]);
    }
    return count;
}
