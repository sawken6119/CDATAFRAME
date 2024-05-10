#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "column.h"
#define REALOC_SIZE 256


int main() {
    int REPONSE;
    char titre[100];
    int nombre_colonnes;

    printf("Combien de colonnes souhaitez-vous creer ? : ");
    scanf("%d", &nombre_colonnes);

    Cdataframe *df = create_cdataframe();

    for (int i = 0; i < nombre_colonnes; i++) {
        printf("Saisir le titre de la colonne %d : ", i+1);
        scanf("%s", titre);
        ajout_colonne(df, titre);
    }

    // Remplissage du Cdataframe avec des valeurs
    remplir_Cdata(df);

    // Affichage du nombre de colonnes et de lignes
    printf("Nombre de colonnes : %d\n", nb_col(df));
    printf("Nombre de lignes : %d\n", nb_ligne(df));

    // Exemple de comparaison de valeurs
    int value = 5;
    printf("Nombre de valeurs supérieures à %d : %d\n", value, nb_sup(df, value));

    // Affichage du contenu du Cdataframe
    afficher_Cdata(df);

    return 0;
}

