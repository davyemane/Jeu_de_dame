#include "jeu_de_dames.h"

// Fonction pour initialiser le jeu
void initialiserJeu(JeuDeDames *jeu) {
    // Initialiser le plateau avec des cases vides
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            jeu->plateau[i][j] = VIDE;
        }
    }
    
    // Placer les pions noirs (en haut)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < TAILLE; j++) {
            if ((i + j) % 2 == 1) {  // Cases noires uniquement
                jeu->plateau[i][j] = PION_NOIR;
            }
        }
    }
    
    // Placer les pions blancs (en bas)
    for (int i = TAILLE - 3; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            if ((i + j) % 2 == 1) {  // Cases noires uniquement
                jeu->plateau[i][j] = PION_BLANC;
            }
        }
    }
    
    // Blanc commence
    jeu->joueurActuel = 1;
    jeu->partieTerminee = false;
}