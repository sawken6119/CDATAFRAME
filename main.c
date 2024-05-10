#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "column.h"
#define REALOC_SIZE 256


int main() 
{
    int REPONSE;
    char titre[100];
    printf("Saisir un titre ? : ");
    scanf("%s",&titre);
    Cdataframe *df = create_cdataframe();
    ajout_colonne(df, titre);
    //int valeurs[] = {1, 2, 3 , 4, 5, 6}; // Exemple de valeurs pour une nouvelle ligne
    //ajout_ligne(df, valeurs);
    remplir_Cdata(df);
    printf("Nombre de colonnes : %d\n", nb_col(df));
    printf("Nombre de lignes : %d\n",nb_ligne(df));
    int value = 5; // Exemple de valeur à comparer
    printf("Nombre de valeurs supérieures à %d : %d\n", value, nb_sup(df, value));
    // Affichage du contenu du Cdataframe
    afficher_Cdata(df);
    return 0;
}
