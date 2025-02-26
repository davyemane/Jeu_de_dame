#include "jeu_de_dames.h"

// Initialise SDL et crée les ressources nécessaires
bool initialiserSDL(RessourcesSDL *res) {
    // Initialiser SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur lors de l'initialisation de SDL: %s\n", SDL_GetError());
        return false;
    }
    
    // Initialiser SDL_ttf
    if (TTF_Init() < 0) {
        printf("Erreur lors de l'initialisation de SDL_ttf: %s\n", TTF_GetError());
        SDL_Quit();
        return false;
    }
    
    // Créer la fenêtre
    res->fenetre = SDL_CreateWindow("Jeu de Dames", 
                                    SDL_WINDOWPOS_UNDEFINED, 
                                    SDL_WINDOWPOS_UNDEFINED,
                                    LARGEUR_FENETRE, 
                                    HAUTEUR_FENETRE, 
                                    SDL_WINDOW_SHOWN);
    if (!res->fenetre) {
        printf("Erreur lors de la création de la fenêtre: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return false;
    }
    
    // Créer le renderer
    res->rendu = SDL_CreateRenderer(res->fenetre, -1, SDL_RENDERER_ACCELERATED);
    if (!res->rendu) {
        printf("Erreur lors de la création du renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(res->fenetre);
        TTF_Quit();
        SDL_Quit();
        return false;
    }
    
    // Charger la police
    res->police = TTF_OpenFont("arial.ttf", 24);
    if (!res->police) {
        printf("Erreur lors du chargement de la police: %s\n", TTF_GetError());
        // Continuer même sans police
    }
    
    // Créer les textures pour les pions
    SDL_Surface *surface;
    
    // Pour les textures, on crée des surfaces simples
    // Dans une vraie application, vous pourriez charger des images
    
    // Pion blanc
    surface = SDL_CreateRGBSurface(0, TAILLE_CASE - 20, TAILLE_CASE - 20, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 240, 240, 240));
    res->texturePionBlanc = SDL_CreateTextureFromSurface(res->rendu, surface);
    SDL_FreeSurface(surface);
    
    // Pion noir
    surface = SDL_CreateRGBSurface(0, TAILLE_CASE - 20, TAILLE_CASE - 20, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 30, 30, 30));
    res->texturePionNoir = SDL_CreateTextureFromSurface(res->rendu, surface);
    SDL_FreeSurface(surface);
    
    // Dame blanche (pion blanc avec couronne)
    surface = SDL_CreateRGBSurface(0, TAILLE_CASE - 20, TAILLE_CASE - 20, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 240, 240, 240));
    // Ajouter une "couronne" à la dame
    SDL_Rect couronne = {surface->w/4, surface->h/4, surface->w/2, surface->h/4};
    SDL_FillRect(surface, &couronne, SDL_MapRGB(surface->format, 200, 200, 50));
    res->textureDameBlanc = SDL_CreateTextureFromSurface(res->rendu, surface);
    SDL_FreeSurface(surface);
    
    // Dame noire (pion noir avec couronne)
    surface = SDL_CreateRGBSurface(0, TAILLE_CASE - 20, TAILLE_CASE - 20, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 30, 30, 30));
    // Ajouter une "couronne" à la dame
    SDL_FillRect(surface, &couronne, SDL_MapRGB(surface->format, 200, 200, 50));
    res->textureDameNoir = SDL_CreateTextureFromSurface(res->rendu, surface);
    SDL_FreeSurface(surface);
    
    return true;
}

// Libère les ressources SDL
void libererSDL(RessourcesSDL *res) {
    SDL_DestroyTexture(res->texturePionBlanc);
    SDL_DestroyTexture(res->texturePionNoir);
    SDL_DestroyTexture(res->textureDameBlanc);
    SDL_DestroyTexture(res->textureDameNoir);
    
    if (res->police) TTF_CloseFont(res->police);
    
    SDL_DestroyRenderer(res->rendu);
    SDL_DestroyWindow(res->fenetre);
    
    TTF_Quit();
    SDL_Quit();
}

// Dessine le plateau de jeu
void dessinerPlateau(RessourcesSDL *res, JeuDeDames *jeu) {
    // Effacer l'écran
    SDL_SetRenderDrawColor(res->rendu, 150, 100, 50, 255); // Couleur bois clair
    SDL_RenderClear(res->rendu);
    
    // Dessiner les cases
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            SDL_Rect rect = {j * TAILLE_CASE, i * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE};
            
            if ((i + j) % 2 == 0) {
                // Case blanche
                SDL_SetRenderDrawColor(res->rendu, 240, 217, 181, 255); // Beige clair
            } else {
                // Case noire
                SDL_SetRenderDrawColor(res->rendu, 100, 65, 23, 255); // Marron foncé
            }
            
            SDL_RenderFillRect(res->rendu, &rect);
            
            // Mettre en évidence la case sélectionnée
            if (jeu->pieceSel.ligne == i && jeu->pieceSel.colonne == j) {
                SDL_SetRenderDrawColor(res->rendu, 0, 255, 0, 100); // Vert transparent
                SDL_RenderFillRect(res->rendu, &rect);
            }
            
            // Dessiner les pièces
            if (jeu->plateau[i][j] != VIDE) {
                SDL_Texture *texture = NULL;
                switch (jeu->plateau[i][j]) {
                    case PION_BLANC:
                        texture = res->texturePionBlanc;
                        break;
                    case PION_NOIR:
                        texture = res->texturePionNoir;
                        break;
                    case DAME_BLANCHE:
                        texture = res->textureDameBlanc;
                        break;
                    case DAME_NOIRE:
                        texture = res->textureDameNoir;
                        break;
                }
                
                if (texture) {
                    SDL_Rect destRect = {
                        j * TAILLE_CASE + 10, 
                        i * TAILLE_CASE + 10, 
                        TAILLE_CASE - 20, 
                        TAILLE_CASE - 20
                    };
                    SDL_RenderCopy(res->rendu, texture, NULL, &destRect);
                }
            }
        }
    }
    
    // Dessiner texte du joueur actuel
    if (res->police) {
        SDL_Color couleur = {255, 255, 255, 255};
        char texte[50];
        sprintf(texte, "Joueur: %s", (jeu->joueurActuel == 1) ? "Blanc" : "Noir");
        SDL_Surface *surface = TTF_RenderText_Solid(res->police, texte, couleur);
        if (surface) {
            SDL_Texture *texture = SDL_CreateTextureFromSurface(res->rendu, surface);
            if (texture) {
                SDL_Rect rect = {10, 10, surface->w, surface->h};
                SDL_RenderCopy(res->rendu, texture, NULL, &rect);
                SDL_DestroyTexture(texture);
            }
            SDL_FreeSurface(surface);
        }
    }
    
    // Afficher le rendu
    SDL_RenderPresent(res->rendu);
}

// Convertit les coordonnées de la souris en position sur le plateau
Position obtenirPositionClic(int x, int y) {
    Position pos;
    pos.ligne = y / TAILLE_CASE;
    pos.colonne = x / TAILLE_CASE;
    return pos;
}

// Sélectionne une pièce à la position donnée
void selectionnerPiece(JeuDeDames *jeu, Position pos) {
    // Vérifier que la position est valide
    if (!estPositionValide(pos)) {
        return;
    }
    
    // Vérifier qu'une pièce du joueur actuel se trouve à cette position
    int piece = jeu->plateau[pos.ligne][pos.colonne];
    if ((jeu->joueurActuel == 1 && (piece == PION_BLANC || piece == DAME_BLANCHE)) ||
        (jeu->joueurActuel == 2 && (piece == PION_NOIR || piece == DAME_NOIRE))) {
        // Sélectionner la pièce
        jeu->pieceSel = pos;
    }
}

// Déplace la pièce sélectionnée vers la position donnée
void deplacerPiece(JeuDeDames *jeu, Position pos) {
    // Vérifier qu'une pièce est sélectionnée
    if (jeu->pieceSel.ligne == -1 || jeu->pieceSel.colonne == -1) {
        return;
    }
    
    // Créer un mouvement
    Mouvement mouv;
    mouv.debut = jeu->pieceSel;
    mouv.fin = pos;
    
    // Vérifier si le mouvement est valide
    if (estMouvementValide(jeu, mouv)) {
        // Effectuer le mouvement
        effectuerMouvement(jeu, mouv);
        
        // Vérifier si la partie est terminée
        jeu->partieTerminee = verifierFinPartie(jeu);
    }
    
    // Désélectionner la pièce
    jeu->pieceSel.ligne = -1;
    jeu->pieceSel.colonne = -1;
}