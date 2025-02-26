#include "jeu_de_dames.h"
#include <stdlib.h>

// Effectue un mouvement
void effectuerMouvement(JeuDeDames *jeu, Mouvement mouv) {
    // Déplacer le pion
    jeu->plateau[mouv.fin.ligne][mouv.fin.colonne] = jeu->plateau[mouv.debut.ligne][mouv.debut.colonne];
    jeu->plateau[mouv.debut.ligne][mouv.debut.colonne] = VIDE;
    
    // Vérifier si c'est une prise
    if (abs(mouv.fin.ligne - mouv.debut.ligne) == 2) {
        // Calculer la position du pion pris
        int ligneIntermediaire = (mouv.debut.ligne + mouv.fin.ligne) / 2;
        int colonneIntermediaire = (mouv.debut.colonne + mouv.fin.colonne) / 2;
        
        // Enlever le pion pris
        jeu->plateau[ligneIntermediaire][colonneIntermediaire] = VIDE;
    }
    
    // Vérifier si un pion doit être transformé en dame
    if (jeu->plateau[mouv.fin.ligne][mouv.fin.colonne] == PION_BLANC && mouv.fin.ligne == 0) {
        jeu->plateau[mouv.fin.ligne][mouv.fin.colonne] = DAME_BLANCHE;
    }
    if (jeu->plateau[mouv.fin.ligne][mouv.fin.colonne] == PION_NOIR && mouv.fin.ligne == TAILLE - 1) {
        jeu->plateau[mouv.fin.ligne][mouv.fin.colonne] = DAME_NOIRE;
    }
    
    // Changer de joueur
    jeu->joueurActuel = (jeu->joueurActuel == 1) ? 2 : 1;
}

// Fonction pour lire un mouvement depuis l'entrée utilisateur
Mouvement lireMouvement() {
    Mouvement mouv;
    printf("Entrez la position de départ (ligne colonne): ");
    scanf("%d %d", &mouv.debut.ligne, &mouv.debut.colonne);
    printf("Entrez la position d'arrivée (ligne colonne): ");
    scanf("%d %d", &mouv.fin.ligne, &mouv.fin.colonne);
    return mouv;
}