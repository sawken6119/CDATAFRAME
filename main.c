#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "column.h"
#define REALOC_SIZE 256


int main() {
    // Création d'un Cdataframe
    Cdataframe *df = create_cdataframe();
    ajout_colonne(df, "Alexandre");
    ajout_colonne(df, "Armand");
    ajout_colonne(df, "Jules");
    ajout_colonne(df, "Kassav");
    ajout_colonne(df, "Rencard");
    ajout_colonne(df, "Tuvol");
    int valeurs[] = {1, 2, 3 , 4, 5, 6}; // Exemple de valeurs pour une nouvelle ligne
    ajout_ligne(df, valeurs);
    remplir_Cdata(df);
    printf("Nombre de colonnes : %d\n", nb_col(df));
    printf("Nombre de lignes : %d\n",nb_ligne(df));
    int value = 5; // Exemple de valeur à comparer
    printf("Nombre de valeurs supérieures à %d : %d\n", value, nb_sup(df, value));
    // Affichage du contenu du Cdataframe
    afficher_Cdata(df);

    // Libération de la mémoire allouée pour le Cdataframe
    // (À faire à la fin du programme pour éviter les fuites de mémoire)
    // ...
    // free(df);

    return 0;
}
