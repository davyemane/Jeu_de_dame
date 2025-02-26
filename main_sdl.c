#include "jeu_de_dames.h"

int main(int argc, char *argv[]) {
    JeuDeDames jeu;
    RessourcesSDL ressources;
    bool continuer = true;
    SDL_Event event;
    
    // Initialiser le jeu
    initialiserJeu(&jeu);
    jeu.pieceSel.ligne = -1;
    jeu.pieceSel.colonne = -1;
    
    // Initialiser SDL
    if (!initialiserSDL(&ressources)) {
        printf("Erreur lors de l'initialisation de SDL!\n");
        return 1;
    }
    
    // Boucle principale
    while (continuer && !jeu.partieTerminee) {
        // Dessiner le plateau
        dessinerPlateau(&ressources, &jeu);
        
        // Gérer les événements
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    continuer = false;
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        Position pos = obtenirPositionClic(event.button.x, event.button.y);
                        
                        // Si aucune pièce n'est sélectionnée, essayer d'en sélectionner une
                        if (jeu.pieceSel.ligne == -1 || jeu.pieceSel.colonne == -1) {
                            selectionnerPiece(&jeu, pos);
                        } else {
                            // Sinon, déplacer la pièce sélectionnée
                            deplacerPiece(&jeu, pos);
                        }
                    }
                    break;
            }
        }
        
        // Limiter la fréquence d'images
        SDL_Delay(16);  // Environ 60 FPS
    }
    
    // Si la partie est terminée, afficher le résultat pendant quelques secondes
    if (jeu.partieTerminee) {
        // Afficher le message de fin de partie
        SDL_Color couleur = {255, 255, 255, 255};
        char texte[50];
        
        int compteurBlancs = 0, compteurNoirs = 0;
        
        // Compter les pions restants
        for (int i = 0; i < TAILLE; i++) {
            for (int j = 0; j < TAILLE; j++) {
                if (jeu.plateau[i][j] == PION_BLANC || jeu.plateau[i][j] == DAME_BLANCHE) {
                    compteurBlancs++;
                } else if (jeu.plateau[i][j] == PION_NOIR || jeu.plateau[i][j] == DAME_NOIRE) {
                    compteurNoirs++;
                }
            }
        }
        
        if (compteurBlancs == 0) {
            strcpy(texte, "Les noirs ont gagné!");
        } else if (compteurNoirs == 0) {
            strcpy(texte, "Les blancs ont gagné!");
        }
        
        SDL_Surface *surface = TTF_RenderText_Solid(ressources.police, texte, couleur);
        if (surface) {
            SDL_Texture *texture = SDL_CreateTextureFromSurface(ressources.rendu, surface);
            if (texture) {
                // Dessiner une dernière fois le plateau
                dessinerPlateau(&ressources, &jeu);
                
                // Dessiner le message au centre
                SDL_Rect rect = {
                    (LARGEUR_FENETRE - surface->w) / 2, 
                    (HAUTEUR_FENETRE - surface->h) / 2, 
                    surface->w, 
                    surface->h
                };
                SDL_RenderCopy(ressources.rendu, texture, NULL, &rect);
                SDL_RenderPresent(ressources.rendu);
                
                SDL_DestroyTexture(texture);
            }
            SDL_FreeSurface(surface);
        }
        
        // Attendre quelques secondes
        SDL_Delay(3000);
    }
    
    // Libérer les ressources
    libererSDL(&ressources);
    
    return 0;
}