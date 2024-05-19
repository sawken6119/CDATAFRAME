#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "column.h"
#include "CDATA.h"
#define REALOC_SIZE 256
int main()
{
    int REPONSE;
    char titre[100];
    int nombre_colonnes;
    int arret;
    int choix;
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
    printf("Quelle colonne souhaitez-vous supprimer ? : ", nombre_colonnes);
    scanf("%d", &choix);
    if (choix < 1 || choix > nombre_colonnes)
    {
        printf("Invalide.\n");
    } else
    {
        // Supprimer la colonne choisie
        delete_column(&(df->col[choix - 1]));

        // Réorganiser les colonnes restantes
        for (int i = choix - 1; i < nombre_colonnes - 1; i++)
        {
            df->col[i] = df->col[i + 1];
        }
        df->nb_colone--;  // Mettre à jour le nombre de colonnes
    }
    // Exemple de comparaison de valeurs
    int value = 5;
    printf("Nombre de valeurs supérieures à %d : %d\n", value, nb_sup(df, value));
    // Affichage du contenu du Cdataframe
    afficher_Cdata(df);
    affiche_partie_col(df,arret);
    printf("Le nombre de valeur supérieur à 8 est %d ",nb_sup(df, 8));
    int choix_colonne;
    char nouveau_titre[100];
    printf("Voulez-vous renommer une colonne ? (1 pour Oui, 0 pour Non) : ");
    int choix_utilisateur;
    scanf("%d", &choix_utilisateur);
    if (choix_utilisateur == 1)
    {
        printf("Entrez l'indice de la colonne que vous voulez renommer : ");
        scanf("%d", &choix_colonne);
        printf("Entrez le nouveau titre de la colonne : ");
        scanf("%s", nouveau_titre);
        renommer_colonne(df, choix_colonne, nouveau_titre);
        printf("La colonne a été renommée avec succès.\n");
        // Afficher le dataframe après le renommage
        afficher_Cdata(df);
    }
    int ligne, colonne, nouvelle_valeur;
    printf("Entrez l'indice de la ligne : ");
    scanf("%d", &ligne);
    printf("Entrez l'indice de la colonne : ");
    scanf("%d", &colonne);
    printf("Entrez la nouvelle valeur : ");
    scanf("%d", &nouvelle_valeur);
    acces_valeur_cellule(df, ligne, colonne, nouvelle_valeur);
    printf("Après la modification :\n");
    afficher_Cdata(df);
    return 0;
}

