#ifndef C_DATA_FRAME_COLUMN_H
#define C_DATA_FRAME_COLUMN_H


//Structure de la colonne
typedef struct
{
    char titre[100]; // titre
    int TL;  // taille logique
    int TP; // taille physique
    int *donne; // Tableau des données ou valeurs
}Column;

Column *create_column(char *title);
int insert_value(Column* col, int value);
void delete_column(Column **col);
void print_col(Column* col);
void nb_occurences(Column* col, int value);
void value_present(Column* col, int x);
void value_sup(Column* col, int value);
void value_inf(Column* col, int value);
void value_egal(Column* col, int value);

