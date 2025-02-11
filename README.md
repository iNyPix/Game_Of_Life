# Game of Life

Le **Jeu de la Vie** (Game of Life) est un automate cellulaire inventé par John Conway en 1970. Ce projet implémente ce jeu à l'aide de la bibliothèque PDCurses pour une interface en mode texte.

## Description

Le projet implémente une version interactive du **Jeu de la Vie**, où les utilisateurs peuvent visualiser l'évolution des cellules en fonction de règles spécifiques ou aléatoires. Le projet utilise **PDCurses**, une bibliothèque qui fournit des fonctionnalités pour les applications en mode texte.

## Prérequis

### Dépendances

- **CMake** : utilisé pour la gestion de la construction du projet.
- **PDCurses** : une bibliothèque permettant de créer des interfaces utilisateur en mode texte (similaire à ncurses).
- **Un compilateur C++** : GCC, Clang, MSVC, etc.

### Installation de PDCurses

Le projet inclut la version source de **PDCurses**. Lors de la configuration du projet, CMake l'ajoutera automatiquement aux dépendances du projet.

## Compilation et Exécution

### 1. Configuration avec CMake

1. Clonez ce dépôt sur votre machine locale.

   ```bash
   git clone https://github.com/iNyPix/Game_Of_Life.git
   cd Game_Of_Life
   ```
2. Créez un répertoire de construction :
   ```bash
   mkdir build
   cd build
   ```
3. Exécutez CMake pour générer les fichiers de construction :
   ```bash
   cmake ..
   ```
### 2. Construction du projet
• Sur un système UNIX (Linux, macOS), utilisez make :
  ```bash
  make
  ```
• Sur Windows, vous pouvez utiliser Ninja ou générer un projet dans Visual Studio, selon la configuration CMake choisie.

### 3. Exécution du jeu
Une fois la compilation terminée, vous pouvez exécuter le jeu avec la commande suivante :
```bash
./Game_Of_Life
```

### Utilisation
Une fois le programme lancé, vous pouvez interagir avec le jeu en utilisant les touches de votre clavier. Le programme devrait afficher la grille du jeu de la vie, et les cellules vivantes seront représentées par un caractère (par exemple, *).

### Fichiers
• main.cpp : le fichier source principal contenant la logique du jeu.  
• Pattern.txt : un fichier texte contenant des motifs de départ pour le jeu (facultatif).  
• CMakeLists.txt : le fichier de configuration pour CMake.  
• PDCurses-3.9/ : le répertoire contenant les sources de la bibliothèque PDCurses.  

___
Créé avec ❤️ par Thomas NICOLLE
