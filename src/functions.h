#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "functions.c"


/* Prototypes des fonctions */
void Couleur(char *param);
void Effacer();
int Sleep(long msec);
void AfficheJeu(Tab jeu);
void AfficheTab(Tab tab);
void AfficheJeuSucces(Tab tab);
void AfficheJeuErreur(Tab tab);
void *Melange2D(Tab tab);
void InverserValeur(unsigned int *a, unsigned int *b);
void RechercherValJeu(unsigned int val, Tab ref, int *x, int *y);
int Distance(Tab jeu, Tab ref);
void ActionJeu(Arbre a, Noeud *noeud, Tab jeu, Tab ref);
Arbre AjoutFilsArbre(Arbre a, Tab jeu, Tab ref, int numeroCaseFils);
int PasDansArbre(Arbre a, Tab jeu);
Noeud *RechercheMeilleurConfig(Arbre a);
int Jouer(Tab ref, Arbre a);
Arbre TaquinAutomatique(Tab tab, Tab tabRef);
void AfficherSucces(int *tab);
void AfficherErreur(int *tab);
int ControleEntier(char *mot);
void Menu();
void Quitter();
void Aide();
void Licence();
int Deplacement(int *tab);
void *Melange1D(int *tab, int *tmp_tab);
void Afficher(int *tab);

#endif /* FUNCTIONS_H */
