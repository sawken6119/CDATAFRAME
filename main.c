#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CDataframe.h"
#define OUI 0
#define NON 1
int main(void)
{
    char titre[100];
    int t_log,t_log1;
    int Reponse;
    printf("Donner un titre à la colonne : ");
    scanf("%s", titre);
    COLUMN *col = create_column(titre);
    printf("Nombre de valeurs à saisir : ");
    scanf("%d", &t_log);
    for (int i = 0; i < t_log; i++)
    {
        int value;
        printf("Saisir la valeur %d : ", i+1);
        scanf("%d", &value);
        insert_value(col, value);
    }

    printf("Titre de la colonne : %s\n", col->title);
    printf("Valeurs de la colonne : ");
    for (int i = 0; i < col->t_log; i++) {
        printf("%d ", col->Tab[i]);
    }
    printf("\n");
    return 0;
}
