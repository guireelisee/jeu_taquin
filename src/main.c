#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"

int main(int argc, char const *argv[])
{

    int action, choice;
    char rep[50];

    Tab tabRef = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}}, tabDeuxDimensions = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    Arbre a;

    int *tabUneDimension = malloc(9 * sizeof(int)), *tmp_tab = malloc(9 * sizeof(int));

    do
    {
        Menu();
        printf("\t\t\t\tVotre choix: ");
        Couleur(TexteVert);
        scanf("%s", rep);
        Couleur(TexteBlanc);
        while (ControleEntier(rep) == 1)
        {
            Couleur(TexteRouge);
            printf("\n\n\t\t\t\a\aAttention: Choix non numérique!");
            Menu();
            printf("\n\t\t\t\tVotre choix: ");
            Couleur(TexteVert);
            scanf("%s", rep);
            Couleur(TexteBlanc);
        }
        action = atoi(rep);
        switch (action)
        {
        case 1:
            a = TaquinAutomatique(tabDeuxDimensions, tabRef);
            choice = Jouer(tabRef, a);
            break;
        case 2:
            Melange1D(tabUneDimension, tmp_tab);
            Afficher(tabUneDimension);
            choice = Deplacement(tabUneDimension);
            break;
        case 3:
            Aide();
            break;
        case 4:
            Licence();
            break;
        case 5:
            Quitter();
            break;
        default:
            Couleur(TexteRouge);
            printf("\n\t\t\t\a\a       Choix inexistant !\n\n");
            Couleur(TexteBlanc);
            break;
        }
        printf("\t\t      Appuyer sur ");
        Couleur(TexteVert);
        printf("Entrée ");
        Couleur(TexteBlanc);
        printf("pour revenir au menu ");
        getchar();
    } while (getchar() == '\n' || choice == 1);

    free(tabUneDimension);
    free(tmp_tab);
    exit(EXIT_SUCCESS);
}
