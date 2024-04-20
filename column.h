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
