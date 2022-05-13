#include <stdio.h>



/* ------------------------------ */

/* ----- Prototyping ----- */

/* ------------------------------ */
void nouvelle_partie();
int collision(int carte[20][20], int joueur[2], int statut[3]);
int deplace_personnage(int carte[20][20], int joueur[2], int statut[3]);
void affiche_statut(int statut[3]);
void affiche_carte(int carte[20][20], int joueur[2]);
int init_carte(int carte[20][20]);



/* ------------------------------ */

/* ----- Main Functions ----- */

/* ------------------------------ */
int main()
{
    /* Tableau: 2 Dimensions - Carte 20x20*/
    int carte[20][20];
    init_carte(carte);

    /* Tableau: 1 Dimension - Position x et y*/
    int joueur[2] = {0, 0};

    /* Tableau: 1 Dimension - Pièce, clé et point de vie*/
    int statut[3] = {10, 0, 0};

    /* Boucle du jeu */
    int run = 0;
    while (!run)
    {
        affiche_carte(carte, joueur); // Affiche la carte après chaque mouvement du joueur
        affiche_statut(statut);
        run = deplace_personnage(carte, joueur, statut); // Déplace le personnage
        if (statut[1] >= 10)
        {
            printf("Vous avez gagne! Game Over!\n", statut[1]);
            run = !run;
            nouvelle_partie();
        }

        if (statut[0] <= 0)
        {
            printf("Vous etes mort... Game Over!\n");
            run = !run;
            nouvelle_partie();
        }
    }

    return 0;

}



/* ------------------------------ */

/* ----- Initialization Functions ----- */

/* ------------------------------ */
int init_carte(int carte[20][20])
{
    int carte_001[20][20] =
        {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 5},
        {0, 1, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 8, 0, 0, 0, 0, 0, 3, 0, 0, 3},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 8, 8, 0, 0},
        {0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 3, 3, 3},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 5, 5},
        {0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 3, 3, 3},
        {5, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0},
        {0, 0, 3, 0, 0, 8, 8, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 5}
        };

    /* Charge la carte */
    int i; int j;
    for (i=0; i<20; i++)
    {
        for (j=0; j<20; j++)
        {
            carte[i][j] = carte_001[i][j];
        }
    }
}



/* ------------------------------ */

/* ----- Initialization Functions ----- */

/* ------------------------------ */
void affiche_carte(int carte[20][20], int joueur[2])
{
    int i; int j;
    for (i=0; i<20; i++) // Ligne / X (Joueur)
    {
        for (j=0; j<20; j++) // Colonne / Y (Joueur)
        {
            /* Affiche la position du joueur */
            if (i == joueur[0] && j == joueur[1])
            {
                printf("X ");
            }

            /* Affiche les éléments de la carte à la position [i][j]*/
            else
            {
                printf("%d ", carte[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void affiche_statut(int statut[3])
{
    printf("Point de vie: %d / 10\n", statut[0]);
    printf("Pieces: %d / 10\n", statut[1]);
    printf("Cle: %d / 1\n", statut[2]);
    printf("\n");
}



/* ------------------------------ */

/* ----- Events Functions ----- */

/* ------------------------------ */
int deplace_personnage(int carte[20][20], int joueur[2], int statut[3])
{
    int mouvement;
    printf("Entrez une commande [8/2/4/6/0] = [Haut/Bas/Gauche/Droite/Fermeture]: ");
    scanf("%d", &mouvement);

    switch (mouvement)
    {
        /* Haut */
        case 8:
            joueur[0]--;
            if (collision(carte, joueur, statut) == 0)
            {
                joueur[0]++;
                printf("Vous ne pouvez pas allez en haut.\n");
            }
            break;

        /* Bas */
        case 2:
            joueur[0]++;
            if (collision(carte, joueur, statut) == 0)
            {
                joueur[0]--;
                printf("Vous ne pouvez pas allez en bas.\n");
            }
            break;

        /* Gauche */
        case 4:
            joueur[1]--;
            if (collision(carte, joueur, statut) == 0)
            {
                joueur[1]++;
                printf("Vous ne pouvez pas allez à gauche.\n");
            }
            break;

        /* Droite */
        case 6:
            joueur[1]++;
            if (collision(carte, joueur, statut) == 0)
            {
                joueur[1]--;
                printf("Vous ne pouvez pas allez à droite.\n");
            }
            break;

        /* Fermeture */
        case 0:
            printf("Fermeture du jeu...\n");
            return 1;
            break;

        /* Invalide */
        default:
            printf("Commande invalide...\n");
    }
    printf("\n");

    return 0;
}



int collision(int carte[20][20], int joueur[2], int statut[3])
{
    /* Sortie de la carte */
    if (joueur[0] < 0 || joueur[0] >= 20 || joueur[1] < 0 || joueur[1] >= 20) return 0;

    /* Element sur la position du joueur */
    int element = carte[joueur[0]][joueur[1]];
    if (element == 0)
    {
        printf("Vous marchez sur de l'herbe.\n");
        return 1;
    }

    if (element == 1)
    {
        printf("Vous marchez sur des fleurs.\n");
        return 1;
    }

    if (element == 2)
    {
        printf("Vous ne pouvez pas marcher à travers un arbre!\n");
        return 0;
    }

    if (element == 3)
    {
        printf("Vous ne pouvez pas marcher à travers un rocher!\n");
        return 0;
    }

    if (element == 4)
    {
        carte[joueur[0]][joueur[1]]= 0;
        statut[2]++;
        printf("Vous avez trouver une cle sur le sol!\n");
        return 1;
    }

    if (element == 5)
    {
        carte[joueur[0]][joueur[1]]= 0;
        statut[1]++;
        printf("Vous avez trouver une piece sur le sol!\n");
        return 1;
    }

    if (element == 6)
    {
        printf("Vous avez rencontre une serrure sur votre chemin!\n");
        if (statut[2] >= 1)
        {
            carte[joueur[0]][joueur[1]]= 0;
            statut[2]--;
            printf("Vous avez utilise une cle pour ouvrir la serrure!\n");
            return 1;
        }
        else
        {
            printf("Vous n'avez pas de cle pour avoir la serrure!\n");
            return 0;
        }
    }

    if (element == 7)
    {
        statut[0]--;
        printf("Vous avez marchez sur un piege!\nVous avez perdu 1 point de vie!\n");
        return 1;
    }

    if (element == 8)
    {
        carte[joueur[0]][joueur[1]]= 0;
        statut[0]--;
        printf("Vous avez rencontrez une monstre sur votre chemin!\n Vous avez perdu 1 point de vie en le combattant!\n");
        return 1;
    }
}



void nouvelle_partie()
{
    /* Nouvelle partie? */
    int partie;
    printf("Tapez 0 pour relancer la partie ou un autre chiffre pour quitter le jeu!\n");
    scanf("%d", &partie);
    if (partie == 0)
    {
        main();
    }
}
