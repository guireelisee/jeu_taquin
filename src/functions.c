#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>


/* Constantes pour la couleur du texte */
#define TexteNoir "30"
#define TexteRouge "31"
#define TexteVert "32"
#define TexteJaune "33"
#define TexteBleu "34"
#define TexteMagenta "35"
#define TexteCyan "36"
#define TexteBlanc "37"

/* Constantes pour la couleur du fond de la console */
#define FondNoir "40"
#define FondRouge "41"
#define FondJaune "42"
#define FondVert "43"
#define FondBleu "44"
#define FondMagenta "45"
#define FondCyan "46"
#define FondBlanc "47"

/* Constantes pour la police */
#define NORMAL "\033[0;0m"
#define BOLD "\033[01;37m"
#define GREEN "\033[00;32m"
#define GREEN_BOLD "\033[01;32m"

#define TAILLEMAX 4
#define MAXINT TAILLEMAX *TAILLEMAX *TAILLEMAX *TAILLEMAX

//On a comme convention de définir le trou comme étant 0.
#define TROU 0

/* Définition des structures */
typedef unsigned int Tab[TAILLEMAX][TAILLEMAX];

typedef struct t_arbre
{
   Tab tab;
   int Distance;
   int mt, nt;
   int marque;
   struct t_arbre *fils[4];
} Noeud, *Arbre;

int nombreAction = 0;
unsigned char afficherProgression;

//////////////////////
// Fonctions utiles //
//////////////////////

void Couleur(char *param)
{
   printf("\033[%sm", param);
}

void Effacer()
{
   system("clear");
}

int Sleep(long msec)
{
   struct timespec ts;
   int res;

   if (msec < 0)
   {
      errno = EINVAL;
      return -1;
   }

   ts.tv_sec = msec / 1000;
   ts.tv_nsec = (msec % 1000) * 1000000;

   do
   {
      res = nanosleep(&ts, &ts);
   } while (res && errno == EINTR);

   return res;
}

int ControleEntier(char *mot)
{
   char *ptr = mot; // ptr pointe sur l'adresse du premier caractère de 'mot' c'est-à-dire ->&mot[0]
   int i = 0, trouver = 0, count = 0;
   while (*ptr != '\0')
   {
      count++; // Taille du mot. Pareil que count = strlen(mot);
      ptr++;
   }
   ptr = mot;           // ->&mot[0]
   while (*ptr != '\0') // Tant qu'on n'est pas à la fin du mot
   {
      if (*ptr == '0' || *ptr == '1' || *ptr == '2' || *ptr == '3' || *ptr == '4' || *ptr == '5' || *ptr == '6' || *ptr == '7' || *ptr == '8' || *ptr == '9')
      {
         trouver++; // On incrémente trouver si le caractère correspond
      }
      ptr++; // Et on avance au caractère suivant
   }
   if (count == trouver) // Si c'est la même taille alors il y a correspondance
   {
      return 0;
   }
   else
   {
      return 1;
   }
}

void Menu()
{
   Effacer();
   printf("\n\n");
   Couleur(TexteMagenta);
   printf("\t\t    .+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+++. \n");
   printf("\t\t    | .*********************************. |\n");
   printf("\t\t    | |                                 | |\n");
   printf("%s\t\t    | |    BIENVENUE AU JEU DE TAQUIN   | |\n",BOLD);
   Couleur(TexteMagenta);
   printf("\t\t    | |                                 | |\n");
   Couleur(TexteCyan);
   printf("\t\t    * *    1- RESOLUTION AUTOMATIQUE    * *\n");
   Couleur(TexteMagenta);
   printf("\t\t    | |                                 | |\n");
   Couleur(TexteCyan);
   printf("\t\t    * *    2-   JOUER MANUELLEMENT      * *\n");
   Couleur(TexteMagenta);
   printf("\t\t    | |                                 | |\n");
   Couleur(TexteCyan);
   printf("\t\t    * *    3-         AIDE              * *\n");
   Couleur(TexteMagenta);
   printf("\t\t    | |                                 | |\n");
   Couleur(TexteCyan);
   printf("\t\t    * *    4-        LICENCE            * *\n");
   Couleur(TexteMagenta);
   printf("\t\t    | |                                 | |\n");
   Couleur(TexteCyan);
   printf("\t\t    * *    5-        QUITTER            * *\n");
   Couleur(TexteMagenta);
   printf("\t\t    | |                                 | |\n");
   printf("\t\t    | '*********************************' |\n");
   printf("\t\t    '-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+' \n");
   printf("\n");
   printf("\n");
   Couleur(TexteBlanc);
}

void Quitter()
{
   Effacer();
   Couleur(TexteBleu);
   ;
   printf("\n\t\t o o o      o           o     o o o o o      ");
   printf("\n\t\t o     o      o       o       o              ");
   printf("\n\t\t o     o        o   o         o              ");
   printf("\n\t\t oo o o           o           o o o o o      ");
   printf("\n\t\t o     o          o           o              ");
   printf("\n\t\t o     o          o           o              ");
   printf("\n\t\t o o o            o           o o o o o      ");
   printf("\n\n\n");
   Couleur(TexteBlanc);
   exit(EXIT_SUCCESS);
}

void Aide()
{

   Effacer();
   printf("\n\n");
   Couleur(TexteMagenta);
   printf("\t\t      .+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+++. \n");
   printf("\t\t      | .*********************************. |\n");
   printf("\t\t      | |                                 | |\n");
   printf("\t\t      | |                                 | |\n");
   printf("%s\t\t      | |              AIDE               | |\n", BOLD);
   Couleur(TexteMagenta);
   printf("\t\t      | |                                 | |\n");
   Couleur(TexteCyan);
   printf("\t\t      * *  Le but du jeu est de remettre  * *\n");
   printf("\t\t      * *   tous les numéros du tableau   * *\n");
   printf("\t\t      * *   dans le bon ordre en partant  * *\n");
   printf("\t\t      * *    d'une disposition initiale   * *\n");
   printf("\t\t      * *       où ils sont mélangés.     * *\n");
   Couleur(TexteMagenta);
   printf("\t\t      | |                                 | |\n");
   printf("%s\t\t      | |        Amusez-vous bien !       | |\n",GREEN_BOLD);
   Couleur(TexteMagenta);
   printf("\t\t      | |                                 | |\n");
   printf("\t\t      | |                                 | |\n");
   printf("\t\t      | '*********************************' |\n");
   printf("\t\t      '-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+' \n");
   printf("\n");
   printf("\n");
   Couleur(TexteBlanc);
}

void Licence()
{
   Effacer();
   printf("\n\n");
   Couleur(TexteMagenta);
   printf("\t\t      .+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+++. \n");
   printf("\t\t      | .*********************************. |\n");
   printf("\t\t      | |                                 | |\n");
   printf("\t\t      | |                                 | |\n");
   printf("%s\t\t      | |            LICENCE              | |\n", BOLD);
   Couleur(TexteMagenta);
   printf("\t\t      | |                                 | |\n");
   printf("%s\t\t      * *        Copyright (c) 2021       * *\n", GREEN_BOLD);
   Couleur(TexteMagenta);
   printf("\t\t      | |                                 | |\n");
   printf("%s\t\t      * *     GUIRE Elisée Aimé Enoch     * *\n",GREEN_BOLD);
   Couleur(TexteMagenta);
   printf("\t\t      | |                                 | |\n");
   printf("%s\t\t      * *       Etudiant en MIAGE L2      * *\n",GREEN_BOLD);
   Couleur(TexteMagenta);
   printf("\t\t      | |                                 | |\n");
   printf("\t\t      | |                                 | |\n");
   printf("\t\t      | '*********************************' |\n");
   printf("\t\t      '-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+' \n");
   printf("\n");
   printf("\n");
   Couleur(TexteBlanc);
}

////////////////////////////
// Résolution automatique //
////////////////////////////

void AfficheJeu(Tab tab)
{
   int i, j;
   Sleep(100);
   Effacer();
   for (i = 0; i < 3; i++)
   {
      printf("\n\t\t\t");
      Couleur(TexteBleu);
      printf("        +-----+-----+-----+\n\t\t\t");
      printf("\t| ");
      Couleur(TexteBlanc);
      for (j = 0; j < 3; j++)
      {
         Couleur(TexteVert);
         if (tab[i][j] == 0)
         {
            printf("  ");
         }
         else
         {
            printf("%2d", tab[i][j]);
         }
         Couleur(TexteBlanc);
         Couleur(TexteBleu);
         printf("  | ");
         Couleur(TexteBlanc);
      }
   }
   printf("\n\t\t\t");

   Couleur(TexteBleu);
   printf("        +-----+-----+-----+\n\t");
   Couleur(TexteBlanc);
}

void AfficheJeuSucces(Tab tab)
{
   int i, j;
   Sleep(100);
   Effacer();
   Couleur(TexteVert);
   for (i = 0; i < 3; i++)
   {
      printf("\n\t\t\t");
      printf("        +-----+-----+-----+\n\t\t\t");
      printf("\t| ");
      for (j = 0; j < 3; j++)
      {
         if (tab[i][j] == 0)
         {
            printf("  ");
         }
         else
         {
            printf("%2d", tab[i][j]);
         }
         printf("  | ");
      }
   }
   printf("\n\t\t\t");

   printf("        +-----+-----+-----+\n\t");
   Couleur(TexteBlanc);
}

void AfficheJeuErreur(Tab tab)
{
   int i, j;
   Sleep(100);
   Effacer();
   for (i = 0; i < 3; i++)
   {
      printf("\n\t\t\t");
      Couleur(TexteRouge);
      printf("        +-----+-----+-----+\n\t\t\t");
      printf("\t| ");
      for (j = 0; j < 3; j++)
      {
         if (tab[i][j] == 0)
         {
            printf("  ");
         }
         else
         {
            printf("%2d", tab[i][j]);
         }
         printf("  | ");
      }
   }
   printf("\n\t\t\t");

   printf("        +-----+-----+-----+\n\t");
   Couleur(TexteBlanc);
}

void AfficheTab(Tab tab)
{
   int i, j;
   for (i = 0; i < 3; i++)
   {
      printf("\n\t\t\t");
      Couleur(TexteBleu);
      printf("        +-----+-----+-----+\n\t\t\t");
      printf("\t| ");
      Couleur(TexteBlanc);
      for (j = 0; j < 3; j++)
      {
         Couleur(TexteVert);
         if (tab[i][j] == 0)
         {
            printf("  ");
         }
         else
         {
            printf("%2d", tab[i][j]);
         }
         Couleur(TexteBlanc);
         Couleur(TexteBleu);
         printf("  | ");
         Couleur(TexteBlanc);
      }
   }
   printf("\n\t\t\t");

   Couleur(TexteBleu);
   printf("        +-----+-----+-----+\n\t");
   Couleur(TexteBlanc);
}

void *Melange2D(Tab tab2D)
{
   int i, j, n, nb_changements, x, tmp, similitude;
   int *tab = malloc(9 * sizeof(int)), *tmp_tab = malloc(9 * sizeof(int));

   srand(time(NULL));

   // Transformation du tableau 2D en 1D
   for (i = 0; i < 3; i++)
   {
      for (j = 0; j < 3; j++)
      {
         tab[i * 3 + j] = tab2D[i][j];
      }
   }

   do
   {
      nb_changements = 0;
      for (i = 0; i < 9; i++)
      {
         tab[i] = i;
      }
      for (i = 0; i < 9; i++)
      {
         x = i + (rand() % (9 - i));
         tmp = tab[i];
         tab[i] = tab[x];
         tab[x] = tmp;
      }

      // cherche les similitudes
      for (i = 0; tab[i] != 0; i++)
      {
         ;
      }
      similitude = (2) + (2) - ((i / 3) + (i % 3));

      // copie du tableau pour comptage
      memcpy(tmp_tab, tab, 9 * sizeof(int));

      // On positionne 0 en fin
      if (i < 8)
      {
         tmp = tmp_tab[8];
         tmp_tab[8] = tmp_tab[i];
         tmp_tab[i] = tmp;
         nb_changements++;
      }

      // comptage des changements restants
      for (i = 8; i > 0; i--)
      {
         if (tmp_tab[i - 1] < i)
         {
            for (n = i - 1; n >= 0; n--)
            {
               if (tmp_tab[n] == i)
               {
                  tmp = tmp_tab[n];
                  tmp_tab[n] = tmp_tab[i - 1];
                  tmp_tab[i - 1] = tmp;
                  nb_changements++;
               }
            }
         }
      }
   } while (((nb_changements % 2) ^ (similitude % 2)));

   // Transformation du tableau 1D en 2D
   for (int i = 0; i < 3; i++)
   {
      for (int j = 0; j < 3; j++)
      {
         tab2D[i][j] = tab[i * 3 + j];
      }
   }
}

// On inverse le contenu de deux variables en utilisant une variable temporaire. (Passage par adresse)
void InverserValeur(unsigned int *a, unsigned int *b)
{
   unsigned int tmp;

   tmp = *a;
   *a = *b;
   *b = tmp;
}

// Recherche les coordonnées de la lettre val dans le tab de référance.
void RechercherValJeu(unsigned int val, Tab ref, int *x, int *y)
{
   int i, j;

   for (i = 0; i < 3; i++)
   {
      for (j = 0; j < 3; j++)
      {
         if (ref[i][j] == val)
         {
            *x = i;
            *y = j;
         }
      }
   }
}

// Calcul la somme des distances des caractères entre le tab et le tab de référance.
int Distance(Tab tab, Tab ref)
{

   int i, j, Distance, sommeDistance = 0, x, y;

   for (i = 0; i < 3; i++)
   {
      for (j = 0; j < 3; j++)
      {
         if (tab[i][j] != TROU)
         {
            if (tab[i][j] != ref[i][j])
            {
               RechercherValJeu(tab[i][j], ref, &x, &y);
               Distance = abs(x - i) + abs(y - j);
               sommeDistance = sommeDistance + Distance;
            }
         }
      }
   }
   return sommeDistance;
}

// Si le tab est déjà dans l'arbre alors res = 0, sinon res = 1;
int PasDansArbre(Arbre a, Tab tab)
{
   int res = 1, i;

   if (a == NULL)
   {
      res = 1;
   }
   else if (Distance(tab, a->tab) == 0)
   {
      res = 0;
   }
   else
   {
      for (i = 0; i < 4; i++)
      {
         if (a->fils[i] != NULL)
         {
            if (res != 0)
            {
               if (PasDansArbre(a->fils[i], tab) == 0)
               {
                  res = 0;
               }
            }
         }
      }
   }
   return res;
}

Arbre AjoutFilsArbre(Arbre a, Tab tab, Tab ref, int numeroCaseFils)
{
   Noeud *noeud;
   noeud = (Noeud *)malloc(sizeof(Noeud));
   int i, j;

   if (noeud == NULL)
   {
      printf("Erreur lors de l'allocation de la mémoire.\n");
      exit(1);
   }

   for (i = 0; i < 3; i++)
   {
      for (j = 0; j < 3; j++)
      {
         noeud->tab[i][j] = tab[i][j];
      }
   }
   noeud->Distance = Distance(tab, ref);
   noeud->marque = 0;

   // Création des fils NULL
   for (i = 0; i < 4; i++)
   {
      noeud->fils[i] = NULL;
   }

   // Ajout du Noeud dans l'arbre à la position du Fils défini et si arbre vide alors création d'un nouveau.
   if (a != NULL)
   {
      a->fils[numeroCaseFils] = noeud;
   }
   else
   {
      a = noeud;
   }

   return a;
}

// Recherche de la meilleure config, càd la somme des distances la plus courte en parcourant tout l'arbre.
Noeud *RechercheMeilleurConfig(Arbre a)
{
   int i, aDesFils = 0, distanceMinimum = MAXINT;
   Noeud *n[4], *res = NULL;

   for (i = 0; i < 4; i++)
   {
      if (a->fils[i] != NULL)
      {
         aDesFils = 1;
      }
   }
   if (aDesFils)
   {
      for (i = 0; i < 4; i++)
      {
         if (a->fils[i] != NULL)
         {
            n[i] = RechercheMeilleurConfig(a->fils[i]);
            if (n[i] != NULL)
            {
               if (n[i]->Distance < distanceMinimum)
               {
                  distanceMinimum = n[i]->Distance;
                  res = n[i];
               }
            }
         }
      }
   }
   else
   {
      if (a->marque == 0)
      {
         res = a;
      }
   }
   return res;
}

// Change la place du trou en fonction du mouvement possible.
void ActionJeu(Arbre a, Noeud *noeud, Tab tab, Tab ref)
{
   int x, y;
   Noeud *n;

   // On commence par detecter la position du trou (x et y).
   RechercherValJeu(TROU, tab, &x, &y);

   // En fonction des coordonnées du trou on effectue les mouvements possibles.
   if (x > 0)
   {
      // On échange le trou avec le caractère du dessus.
      InverserValeur(&tab[x][y], &tab[x - 1][y]);
      if (PasDansArbre(a, tab))
      {
         n = AjoutFilsArbre(noeud, tab, ref, 0);
      }
      InverserValeur(&tab[x][y], &tab[x - 1][y]);
   }
   if (x < 2)
   {
      // On échange le trou avec le caractère du dessous.
      InverserValeur(&tab[x][y], &tab[x + 1][y]);
      if (PasDansArbre(a, tab))
      {
         n = AjoutFilsArbre(noeud, tab, ref, 1);
      }
      InverserValeur(&tab[x][y], &tab[x + 1][y]);
   }
   if (y > 0)
   {
      // On échange le trou avec le caractère de gauche.
      InverserValeur(&tab[x][y], &tab[x][y - 1]);
      if (PasDansArbre(a, tab))
      {
         n = AjoutFilsArbre(noeud, tab, ref, 2);
      }
      InverserValeur(&tab[x][y], &tab[x][y - 1]);
   }
   if (y < 2)
   {
      // On échange le trou avec le caractère de droite.
      InverserValeur(&tab[x][y], &tab[x][y + 1]);
      if (PasDansArbre(a, tab))
      {
         n = AjoutFilsArbre(noeud, tab, ref, 3);
      }
      InverserValeur(&tab[x][y], &tab[x][y + 1]);
   }
}

int Jouer(Tab ref, Arbre a)
{
   Tab tab;
   Noeud *noeud;
   int i, j, Distance;

   // On cherche la meilleure configuration
   noeud = RechercheMeilleurConfig(a);
   if (noeud == NULL)
   {
      Couleur(TexteRouge);
      printf("\t\t\tTaquin insoluble\n");
      fprintf(stdout, "\t\t\tNombre d'actions = %d\n", nombreAction);
      Couleur(TexteBlanc);
      exit(EXIT_FAILURE);
   }

   noeud->marque = 1;
   nombreAction = nombreAction + 1;

   for (i = 0; i < 3; i++)
   {

      for (j = 0; j < 3; j++)
      {

         tab[i][j] = noeud->tab[i][j];
      }
   }

   Distance = noeud->Distance;
   if (nombreAction % 100 == 0)
   {
      fprintf(stderr, "(%d) %d\r", Distance, nombreAction);
   }
   if (Distance == 0)
   {
      AfficheJeuSucces(tab);
      Couleur(TexteVert);
      printf("\n\t\t\t\t   Taquin résolu !\n\n");
      fprintf(stdout, "\t\t\t     Nombre total de coups : %d\n\n\n", nombreAction);
      Couleur(TexteBlanc);
      return 1;
   }

   //On recherche tous les mouvements possible et on les effectues.
   ActionJeu(a, noeud, tab, ref);
   if (afficherProgression == 'O' || afficherProgression== 'o')
   {
      printf("\n\t\t\t   Taquin en cours de résolution...\n");
      AfficheJeu(tab);
   }
   Jouer(ref, a);
}

Arbre TaquinAutomatique(Tab tab,Tab tabRef)
{
   Arbre a;
   Melange2D(tab);
   Effacer();
   printf("\n\t\t\t          Tableau initial");
   AfficheTab(tab);
   printf("\n\t\t\t          Tableau solution");
   AfficheTab(tabRef);
   printf("\n\t\tVoulez vous afficher la progression ? ");
   Couleur(TexteVert);
   printf("(O)");
   Couleur(TexteBlanc);
   printf("ui / ");
   Couleur(TexteVert);
   printf("(N)");
   Couleur(TexteBlanc);
   printf("on\n\n");
   printf("\t\tVotre choix: ");
   Couleur(TexteVert);
   scanf("%s", &afficherProgression);
   Couleur(TexteBlanc);
   a = AjoutFilsArbre(NULL, tab, tabRef, 0);
   return a;
}

//////////////////////////
// Résolution manuelle //
/////////////////////////

void AfficherSucces(int *tab)
{
   Effacer();
   printf("\n\n\t\t(H)aut, (B)as, (G)auche, (D)roite), (Q)uitter\n\n");
   printf("\t\t\t  ou touches directionnelles\n");
   for (int i = 0; i < 9; i++)
   {
      if ((i % 3) == 0)
      {
         printf("\n\t\t\t");
         Couleur(TexteVert);
         printf("     +-----+-----+-----+\n\t\t\t");
         printf("     |");
      }
      if (tab[i] != 0)
      {
         printf(" %2i", tab[i]);
         printf("  |");
      }
      else
      {
         printf("     ");
         printf("|");
      }
   }
   printf("\n\t\t\t");
   printf("     +-----+-----+-----+\n\n");
   Couleur(TexteBlanc);
}

void AfficherErreur(int *tab)
{
   Effacer();
   Couleur(TexteRouge);
   printf("\n\n\t\t(H)aut, (B)as, (G)auche, (D)roite), (Q)uitter\n\n");
   printf("\t\t\t  ou touches directionnelles\n");
   for (int i = 0; i < 9; i++)
   {
      if ((i % 3) == 0)
      {
         printf("\n\t\t\t");
         printf("     +-----+-----+-----+\n\t\t\t");
         printf("     |");
      }
      if (tab[i] != 0)
      {
         printf(" %2i", tab[i]);
         printf("  |");
      }
      else
      {
         printf("     ");
         printf("|");
      }
   }
   printf("\n\t\t\t");
   printf("     +-----+-----+-----+\n\n");
   Couleur(TexteBlanc);
}

void Afficher(int *tab)
{
   Effacer();
   Couleur(TexteVert);
   printf("\n\n\t\t(H)");
   Couleur(TexteBlanc);
   printf("aut, ");
   Couleur(TexteVert);
   printf("(B)");
   Couleur(TexteBlanc);
   printf("as, ");
   Couleur(TexteVert);
   printf("(G)");
   Couleur(TexteBlanc);
   printf("auche, ");
   Couleur(TexteVert);
   printf("(D)");
   Couleur(TexteBlanc);
   printf("roite, ");
   Couleur(TexteVert);
   printf("(R)");
   Couleur(TexteBlanc);
   printf("etour, ");
   Couleur(TexteVert);
   printf("(Q)");
   Couleur(TexteBlanc);
   printf("uitter\n\n");
   printf("\t\t\t  ou touches directionnelles\n");
   for (int i = 0; i < 9; i++)
   {
      if ((i % 3) == 0)
      {
         printf("\n\t\t\t");
         Couleur(TexteBleu);
         printf("     +-----+-----+-----+\n\t\t\t");
         printf("     |");
         Couleur(TexteBlanc);
      }
      if (tab[i] != 0)
      {
         Couleur(TexteVert);
         printf(" %2i", tab[i]);
         Couleur(TexteBleu);
         printf("  |");
         Couleur(TexteBlanc);
      }
      else
      {
         printf("     ");
         Couleur(TexteBleu);
         printf("|");
         Couleur(TexteBlanc);
      }
   }
   printf("\n\t\t\t");
   Couleur(TexteBleu);
   printf("     +-----+-----+-----+\n\n");
   Couleur(TexteBlanc);
}

int Deplacement(int *tab)
{
   int i;
   char touche[5];
   bool sortie = false;

   do
   {
      for (i = 0; i < 9; i++)
      {
         if (tab[i] == 0)
         {
            printf("\t\t\t\tVotre coup: ");
            Couleur(TexteVert);
            scanf("%s", touche);
            Couleur(TexteBlanc);
            while (touche[0] != 'G' && touche[0] != 'g' && touche[2] != 'D' && touche[0] != 'H' && touche[0] != 'h' && touche[2] != 'A' && touche[0] != 'd' && touche[0] != 'd' && touche[2] != 'C' && touche[0] != 'B' && touche[0] != 'b' && touche[2] != 'B' && touche[0] != 'R' && touche[0] != 'r' && touche[0] != 'Q' && touche[0] != 'q')
            {
               Effacer();
               Couleur(TexteRouge);
               printf("\n\t\t\t\a\a Attention: Touche incorrecte!");
               Afficher(tab);
               printf("\t\t\t\tVotre coup: ");
               Couleur(TexteVert);
               scanf("%s", touche);
               Couleur(TexteBlanc);
            }
            if (touche[0] == 'R' || touche[0] == 'r')
            {
               printf("\n\n");
               return 1;
            }
            if (touche[0] == 'G' || touche[0] == 'g' || touche[2] == 'D')
            {
               if (i == 0 || i == 3 || i == 6)
               {
                  Couleur(TexteRouge);
                  printf("\n\t\t\a\aAttention: Déplacment vers la gauche impossible!");
                  Couleur(TexteBlanc);
                  AfficherErreur(tab);
               }
               else
               {
                  tab[i] = tab[i - 1];
                  tab[i - 1] = 0;
                  Afficher(tab);
               }
            }
            if (touche[0] == 'H' || touche[0] == 'h' || touche[2] == 'A')
            {
               if (i == 0 || i == 1 || i == 2)
               {
                  Couleur(TexteRouge);
                  printf("\n\t\t\a\aAttention: Déplacment vers le haut impossible!");
                  Couleur(TexteBlanc);
                  AfficherErreur(tab);
               }
               else
               {
                  tab[i] = tab[i - 3];
                  tab[i - 3] = 0;
                  Afficher(tab);
               }
            }
            if (touche[0] == 'D' || touche[0] == 'd' || touche[2] == 'C')
            {
               if (i == 2 || i == 5 || i == 8)
               {
                  Couleur(TexteRouge);
                  printf("\n\t\t\a\aAttention: Déplacment vers la droite impossible!");
                  Couleur(TexteBlanc);
                  AfficherErreur(tab);
               }
               else
               {
                  tab[i] = tab[i + 1];
                  tab[i + 1] = 0;
                  Afficher(tab);
               }
            }
            if (touche[0] == 'B' || touche[0] == 'b' || touche[2] == 'B')
            {
               if (i == 6 || i == 7 || i == 8)
               {
                  Couleur(TexteRouge);
                  printf("\n\t\t\a\aAttention: Déplacment vers le bas impossible!");
                  Couleur(TexteBlanc);
                  AfficherErreur(tab);
               }
               else
               {
                  tab[i] = tab[i + 3];
                  tab[i + 3] = 0;
                  Afficher(tab);
               }
            }
            if (touche[0] == 'Q' || touche[0] == 'q')
            {
               Quitter();
            }
            // Position gagnante
            if (tab[8] == 0 && tab[7] == 8 && tab[6] == 7 && tab[5] == 6 && tab[4] == 5 && tab[3] == 4 && tab[2] == 3 && tab[1] == 2 && tab[0] == 1)
            {
               AfficherSucces(tab);
               Couleur(TexteVert);
               printf("\n\n\t\t\tTaquin résolu !!!! Bien joué !\n\n\n");
               Couleur(TexteBlanc);
               sortie = true;
               return 1;
            }
         }
      }
   } while (!sortie);
}

void *Melange1D(int *tab, int *tmp_tab)
{
   int i, n, nb_changements, x, tmp, similitude;
   srand(time(NULL));
   do
   {
      nb_changements = 0;
      for (i = 0; i < 9; i++)
      {
         tab[i] = i;
      }
      for (i = 0; i < 9; i++)
      {
         x = i + (rand() % (9 - i));
         tmp = tab[i];
         tab[i] = tab[x];
         tab[x] = tmp;
      }

      // cherche les similitudes
      for (i = 0; tab[i] != 0; i++)
      {
         ;
      }
      similitude = (2) + (2) - ((i / 3) + (i % 3));

      // copie du tableau pour comptage
      memcpy(tmp_tab, tab, 9 * sizeof(int));

      // On positionne 0 en fin
      if (i < 8)
      {
         tmp = tmp_tab[8];
         tmp_tab[8] = tmp_tab[i];
         tmp_tab[i] = tmp;
         nb_changements++;
      }

      // comptage des changements restants
      for (i = 8; i > 0; i--)
      {
         if (tmp_tab[i - 1] < i)
         {
            for (n = i - 1; n >= 0; n--)
            {
               if (tmp_tab[n] == i)
               {
                  tmp = tmp_tab[n];
                  tmp_tab[n] = tmp_tab[i - 1];
                  tmp_tab[i - 1] = tmp;
                  nb_changements++;
               }
            }
         }
      }
   } while (((nb_changements % 2) ^ (similitude % 2)));
}
