#ifndef JEU_DE_DAMES_H
#define JEU_DE_DAMES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Constantes du jeu
#define TAILLE 8  // Taille du damier (8x8)
#define TAILLE_CASE 80  // Taille d'une case en pixels
#define LARGEUR_FENETRE (TAILLE * TAILLE_CASE)
#define HAUTEUR_FENETRE (TAILLE * TAILLE_CASE)

// Définition des pièces
#define VIDE 0
#define PION_BLANC 1
#define PION_NOIR 2
#define DAME_BLANCHE 3
#define DAME_NOIRE 4

// Structure pour représenter une position sur le damier
typedef struct {
    int ligne;
    int colonne;
} Position;

// Structure pour représenter un mouvement
typedef struct {
    Position debut;
    Position fin;
} Mouvement;

// Structure pour le jeu
typedef struct {
    int plateau[TAILLE][TAILLE];
    int joueurActuel;  // 1 pour blanc, 2 pour noir
    bool partieTerminee;
    Position pieceSel;  // Position de la pièce sélectionnée (-1,-1 si aucune)
} JeuDeDames;

// Structure pour les ressources SDL
typedef struct {
    SDL_Window *fenetre;
    SDL_Renderer *rendu;
    TTF_Font *police;
    SDL_Texture *texturePionBlanc;
    SDL_Texture *texturePionNoir;
    SDL_Texture *textureDameBlanc;
    SDL_Texture *textureDameNoir;
} RessourcesSDL;

// Prototypes des fonctions
void initialiserJeu(JeuDeDames *jeu);
bool estPositionValide(Position pos);
bool estMouvementValide(JeuDeDames *jeu, Mouvement mouv);
void effectuerMouvement(JeuDeDames *jeu, Mouvement mouv);
bool verifierFinPartie(JeuDeDames *jeu);

// Fonctions liées à SDL
bool initialiserSDL(RessourcesSDL *res);
void libererSDL(RessourcesSDL *res);
void dessinerPlateau(RessourcesSDL *res, JeuDeDames *jeu);
Position obtenirPositionClic(int x, int y);
void selectionnerPiece(JeuDeDames *jeu, Position pos);
void deplacerPiece(JeuDeDames *jeu, Position pos);

#endif // JEU_DE_DAMES_H