## CeciliaCraftedMine

Jeu voxel de type Minecraft, écrit en C++ avec Raylib.

## Aperçu
Projet scolaire autour du développement de jeux : un monde en blocs (voxels) inspiré de Minecraft, avec son propre moteur de rendu 3D bâti sur Raylib. Le projet sert à explorer la 3D temps réel — découpage du monde en chunks, génération de maillages, shaders et physique du joueur.
Le moteur et les bases du gameplay sont fonctionnels. Le contenu (types de blocs, génération du terrain, ambiance) continue d'évoluer.


## Fonctionnalités

Moteur maison (classe Engine) : boucle de jeu, gestion clavier et souris, FPS limité <br>
Monde découpé en chunks de 16 × 128 × 16 blocs <br>
Types de blocs : air, terre, herbe <br>
Génération de maillages, textures et shaders personnalisés (.vs / .fs) <br>
Éclairage de scène (lumière ponctuelle) <br>
Joueur en vue première personne : déplacement (WASD), saut, gravité, collision au sol, mode vol <br>
Caméra libre avec verrouillage du curseur <br>

## Stack technique

Langage : C++17 <br>
Moteur graphique : Raylib 5.0 (avec raymath, rlgl) <br>
Architecture : moteur / jeu / joueur / chunk / mesh / shader (classes séparées) <br>
Build : Makefile (g++) <br>

## Comment démarrer 
bash# Nécessite Raylib 5.0 installé <br>
make            # compile le projet <br>
./main.exe      # lance le jeu <br>

Statut : En cours d'achèvement
