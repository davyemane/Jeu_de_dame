#include "jeu_de_dames.h"
#include <stdlib.h>

// Vérifie si une position est dans les limites du plateau
bool estPositionValide(Position pos) {
    return pos.ligne >= 0 && pos.ligne < TAILLE && pos.colonne >= 0 && pos.colonne < TAILLE;
}

// Vérifie si un mouvement est valide
bool estMouvementValide(JeuDeDames *jeu, Mouvement mouv) {
    // Vérifier que les positions sont valides
    if (!estPositionValide(mouv.debut) || !estPositionValide(mouv.fin)) {
        return false;
    }
    
    // Vérifier que la case de départ contient un pion du joueur actuel
    int pieceDepart = jeu->plateau[mouv.debut.ligne][mouv.debut.colonne];
    if (jeu->joueurActuel == 1 && (pieceDepart != PION_BLANC && pieceDepart != DAME_BLANCHE)) {
        return false;
    }
    if (jeu->joueurActuel == 2 && (pieceDepart != PION_NOIR && pieceDepart != DAME_NOIRE)) {
        return false;
    }
    
    // Vérifier que la case d'arrivée est vide
    if (jeu->plateau[mouv.fin.ligne][mouv.fin.colonne] != VIDE) {
        return false;
    }
    
    // Vérifier que la case d'arrivée est une case noire
    if ((mouv.fin.ligne + mouv.fin.colonne) % 2 == 0) {
        return false;
    }
    
    // Calculer la différence entre les positions
    int diffLigne = mouv.fin.ligne - mouv.debut.ligne;
    int diffColonne = mouv.fin.colonne - mouv.debut.colonne;
    
    // Vérifier le sens du mouvement selon le joueur (pour les pions)
    if (pieceDepart == PION_BLANC && diffLigne >= 0) {
        return false;  // Les pions blancs ne peuvent aller que vers le haut
    }
    if (pieceDepart == PION_NOIR && diffLigne <= 0) {
        return false;  // Les pions noirs ne peuvent aller que vers le bas
    }
    
    // Mouvement simple (diagonale de 1 case)
    if (abs(diffLigne) == 1 && abs(diffColonne) == 1) {
        return true;
    }
    
    // Mouvement de prise (diagonale de 2 cases)
    if (abs(diffLigne) == 2 && abs(diffColonne) == 2) {
        // Calculer la position du pion à prendre
        Position positionPrise;
        positionPrise.ligne = mouv.debut.ligne + diffLigne / 2;
        positionPrise.colonne = mouv.debut.colonne + diffColonne / 2;
        
        // Vérifier qu'il y a bien un pion adverse à prendre
        int piecePrise = jeu->plateau[positionPrise.ligne][positionPrise.colonne];
        if (jeu->joueurActuel == 1 && (piecePrise == PION_NOIR || piecePrise == DAME_NOIRE)) {
            return true;
        }
        if (jeu->joueurActuel == 2 && (piecePrise == PION_BLANC || piecePrise == DAME_BLANCHE)) {
            return true;
        }
    }
    
    // Dans tous les autres cas, le mouvement est invalide
    return false;
}