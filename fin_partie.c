#include "jeu_de_dames.h"

// Vérifie si la partie est terminée
bool verifierFinPartie(JeuDeDames *jeu) {
    int compteurBlancs = 0, compteurNoirs = 0;
    
    // Compter les pions restants
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            if (jeu->plateau[i][j] == PION_BLANC || jeu->plateau[i][j] == DAME_BLANCHE) {
                compteurBlancs++;
            } else if (jeu->plateau[i][j] == PION_NOIR || jeu->plateau[i][j] == DAME_NOIRE) {
                compteurNoirs++;
            }
        }
    }
    
    // Si un joueur n'a plus de pions, la partie est terminée
    if (compteurBlancs == 0) {
        printf("Les noirs ont gagné!\n");
        return true;
    } else if (compteurNoirs == 0) {
        printf("Les blancs ont gagné!\n");
        return true;
    }
    
    return false;
}