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

void remplissage_utilisateur(COLUMN **CDataframe, int nombre_de_colonnes);

void remplissage_dur(COLUMN **CDataframe, int nombre_de_colonnes);

void print_DataFrame(COLUMN **CDataframe, int nombre_de_colonnes);

void print_partial_row_data(COLUMN** CDataframe, int nombre_de_colonnes, int start_index, int end_index);

void print_partial_column_data(COLUMN **CDataframe, int nombre_de_colonnes, int start_index, int end_index);

void add_row(COLUMN** CDataframe, int nombre_de_colonnes, void** values);

void delete_row(COLUMN** CDataframe, int nombre_de_colonnes, int index);

void add_column(COLUMN*** CDataframe, int* nombre_de_colonnes, char* title, int type, void* values, int size);

void delete_column_CDataframe(COLUMN*** CDataframe, int* nombre_de_colonnes, int index);

void rename_column(COLUMN** CDataframe, int nombre_de_colonnes, int index, char* new_title);

int value_exists_in_column(COLUMN* column, void* value);

int value_exists_in_CDataframe(COLUMN** CDataframe, int nombre_de_colonnes, void* value);

size_t get_type_size(int type);

void replace_value(COLUMN* col, int row_index, int new_value);

void print_column_names(COLUMN** CDataframe, int nombre_de_colonnes);

int get_column_count(int nombre_de_colonnes);

int count_cells_equal_to(COLUMN** CDataframe, int nombre_de_colonnes, int x);

int count_cells_greater_than(COLUMN** CDataframe, int nombre_de_colonnes, int x);

int count_cells_less_than(COLUMN** CDataframe, int nombre_de_colonnes, int x);

#endif //CDATAFRAME_CDATAFRAME_H
