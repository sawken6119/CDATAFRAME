#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CDataframe.h"
#define OUI 0
#define NON 1

int main()
{
    COLUMN **CDataframe = NULL;

    int *nombre_de_colonnes = malloc(sizeof(int));
    printf("Entrer le nombre de colonnes du DataFrame ");
    scanf("%d",nombre_de_colonnes);

    CDataframe = malloc(*nombre_de_colonnes*sizeof (COLUMN*));

    printf("\n");
    int choix;
    printf("Voulez vous un remplissage avec vos valeurs (1) ou un remplissage automatique(2) ? ");
    scanf("%d",&choix);
    while(choix!=1 && choix!=2)
    {
        printf("Choisissez (1) ou (2) ? ");
        scanf("%d",&choix);
    }
    if(choix == 1)
        remplissage_utilisateur(CDataframe,*nombre_de_colonnes);
    else
        remplissage_dur(CDataframe,*nombre_de_colonnes);
    printf("\n");
    printf("Voici le tableau rempli :");
    printf("\n");
    print_DataFrame(CDataframe,*nombre_de_colonnes);
    printf("\n");
    print_partial_row_data(CDataframe, *nombre_de_colonnes, 2, 4);
    printf("\n");
    print_partial_column_data(CDataframe, *nombre_de_colonnes, 1, 2);
    printf("\n");

    // Exemple d'ajout d'une ligne de valeurs au DataFrame
    void* values[*nombre_de_colonnes];

    for(int i=0;i<*nombre_de_colonnes;++i)
    {
        if(CDataframe[i]->type!= STRING)
        {
            values[i] = &(CDataframe[i]->Tab[0]); // Tableau de valeurs à ajouter correspondant aux valeurs
        }

        else
            values[i] = ((char**)(CDataframe[i]->Tab))[0]; // Tableau de valeurs à ajouter correspondant aux valeurs

    }

    add_row(CDataframe, *nombre_de_colonnes, values);
    print_DataFrame(CDataframe,*nombre_de_colonnes);
    int max_val = CDataframe[0]->t_log;
    for (int i = 1; i < *nombre_de_colonnes; ++i)
    {
        if(max_val < CDataframe[i]->t_log)
            max_val = CDataframe[i]->t_log;
    }
    delete_row(CDataframe, *nombre_de_colonnes, max_val);
    printf("\n");
    print_DataFrame(CDataframe,*nombre_de_colonnes);

}
