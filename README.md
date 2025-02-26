# Jeu_de_dame
# Jeu de Dames en C avec SDL2

Un jeu de dames classique implémenté en C utilisant la bibliothèque SDL2 pour l'interface graphique.

![Jeu de Dames](https://github.com/votre-username/jeu-de-dames/raw/main/screenshots/game.png)

## Fonctionnalités

- Implémentation des règles classiques des dames françaises
- Plateau de jeu 8x8
- Interface graphique conviviale avec SDL2
- Déplacement des pions en diagonale
- Transformation en dame lorsqu'un pion atteint le bord opposé
- Gestion de la prise des pions adverses

## Prérequis

Pour compiler et exécuter ce jeu, vous aurez besoin de :

- Un compilateur C (GCC recommandé)
- Les bibliothèques SDL2 et SDL2_ttf
- Make (optionnel, pour utiliser le Makefile)

### Installation des dépendances

#### Sur Ubuntu/Debian :
```bash
sudo apt-get install gcc make libsdl2-dev libsdl2-ttf-dev
```

#### Sur Fedora :
```bash
sudo dnf install gcc make SDL2-devel SDL2_ttf-devel
```

#### Sur macOS (avec Homebrew) :
```bash
brew install sdl2 sdl2_ttf
```

#### Sur Windows :
Il est recommandé d'utiliser [MSYS2](https://www.msys2.org/) pour installer les dépendances nécessaires.

## Compilation

### Avec Make :
```bash
make
```

### Manuellement :
```bash
gcc -o jeu_de_dames *.c -lSDL2 -lSDL2_ttf -lm
```

## Exécution

```bash
./jeu_de_dames
```

## Structure du projet

- `jeu_de_dames.h` : Définitions et prototypes des fonctions
- Fichiers d'implémentation contenant :
  - Fonctions d'initialisation du jeu
  - Fonctions d'affichage du plateau
  - Fonctions pour vérifier les mouvements valides
  - Fonctions pour effectuer les mouvements
  - Fonctions pour vérifier la fin de la partie
  - Fonctions d'interface graphique avec SDL2
  - Programme principal (main)

## Comment jouer

1. Lancez le jeu
2. Cliquez sur un pion de votre couleur pour le sélectionner
3. Cliquez sur une case de destination valide pour déplacer le pion
4. Les prises sont effectuées en sautant par-dessus un pion adverse
5. Lorsqu'un pion atteint la dernière rangée opposée, il devient une dame

## Captures d'écran

![Menu Principal](https://github.com/votre-username/jeu-de-dames/raw/main/screenshots/menu.png)
![Partie en cours](https://github.com/davyemane/jeu-de-dames/raw/main/screenshots/gameplay.png)

## Structures de données principales

```c
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
    int plateau[TAILLE][TAILLE];  // Représentation du plateau de jeu
    int joueurActuel;             // 1 pour blanc, 2 pour noir
    bool partieTerminee;          // Indique si la partie est terminée
    Position pieceSel;            // Position de la pièce sélectionnée
} JeuDeDames;
```

## Améliorations prévues

- [ ] Règles complètes avec prise obligatoire et prises multiples
- [ ] Fonction d'annulation du dernier coup
- [ ] Sauvegarde et chargement de partie
- [ ] Adversaire IA avec plusieurs niveaux de difficulté
- [ ] Animations pour les mouvements des pions
- [ ] Effets sonores
- [ ] Menu principal et écran de configuration

## Contribution

Les contributions sont les bienvenues ! N'hésitez pas à ouvrir une issue ou à soumettre une pull request.

1. Forkez le projet
2. Créez votre branche de fonctionnalité (`git checkout -b feature/nouvelle-fonctionnalite`)
3. Committez vos changements (`git commit -m 'Ajout d'une nouvelle fonctionnalité'`)
4. Poussez vers la branche (`git push origin feature/nouvelle-fonctionnalite`)
5. Ouvrez une Pull Request

## Licence

Ce projet est sous licence MIT. Voir le fichier [LICENSE](ESIGN) pour plus de détails.

## Auteur

Votre Nom - [votre-username](https://github.com/davyemane)