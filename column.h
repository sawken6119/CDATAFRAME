#ifndef C_DATA_FRAME_COLUMN_H
#define C_DATA_FRAME_COLUMN_H


// Structure de la colonne
typedef struct
{
    char titre[100]; // titre de la colonne
    int TL;  // taille logique (nombre d'éléments effectivement présents)
    int TP; // taille physique (capacité du tableau)
    int *donne; // pointeur vers le tableau des données ou valeurs
} Column;

// Crée une nouvelle colonne avec le titre donné
Column *create_column(char *title);

// Insère une valeur dans la colonne donnée
int insert_value(Column* col, int value);

// Supprime la colonne et libère la mémoire associée
void delete_column(Column **col);

// Affiche les valeurs de la colonne
void print_col(Column* col);

// Compte le nombre d'occurrences d'une valeur donnée dans la colonne
void nb_occurences(Column* col, int value);

// Vérifie si une valeur donnée est présente dans la colonne
void value_present(Column* col, int x);

// Affiche les valeurs de la colonne qui sont supérieures à une valeur donnée
void value_sup(Column* col, int value);

// Affiche les valeurs de la colonne qui sont inférieures à une valeur donnée
void value_inf(Column* col, int value);

// Affiche les valeurs de la colonne qui sont égales à une valeur donnée
void value_egal(Column* col, int value);



#endif //C_DATA_FRAME_COLUMN_H

