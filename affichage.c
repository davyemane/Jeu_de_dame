#include "jeu_de_dames.h"

// Fonction pour afficher le plateau
void afficherPlateau(JeuDeDames *jeu) {
    printf("  ");
    for (int j = 0; j < TAILLE; j++) {
        printf(" %d ", j);
    }
    printf("\n");
    
    for (int i = 0; i < TAILLE; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAILLE; j++) {
            if ((i + j) % 2 == 0) {
                printf("[ ]");  // Case blanche
            } else {
                switch (jeu->plateau[i][j]) {
                    case VIDE:
                        printf("[.]");
                        break;
                    case PION_BLANC:
                        printf("[o]");
                        break;
                    case PION_NOIR:
                        printf("[x]");
                        break;
                    case DAME_BLANCHE:
                        printf("[O]");
                        break;
                    case DAME_NOIRE:
                        printf("[X]");
                        break;
                }
            }
        }
        printf("\n");
    }
    
    printf("Joueur actuel: %s\n", (jeu->joueurActuel == 1) ? "Blanc (o)" : "Noir (x)");
}