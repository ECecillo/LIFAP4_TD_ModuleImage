# Pacman pour LIFAP4

Pacman est un exemple très simple d'une implémentation du Pacman pour le cours de L2 Informatique "Conception et Développement d'application".
Le code est écrit en C++, afin d'être compéhensible par un étudiant "classique" de L2. Pas de C++-18, template, metaprog, etc.
Il a également pour but d'illustrer les outils gravitant autour du code : git, doxygen, valgrinf, etc.

Il peut se compiler sous Linux, Windows, en ligne de commande avec un IDE (codeblocks, visual code, QtCreator).

Voir la page de LIFAP4 Conception et Developpement d'Applications
http://licence-info.univ-lyon1.fr/LIFAP4


## Le code et l'organisation des fichiers

Ce code est construit de manière à avoir les fonctionalités de base regroupées dans des classes noyau; 
puis d'avoir une surcouche pour l'affichage : texte/console, SDL2, Qt, OpenGl, etc.

L'organistion des fichiers est la suivante.

- **Pacmansrc/core**   : les classes de base du Pacman (il n'y a ici aucun appel aux couches du dessus, de l'affichage). 
                        Ce code doit compiler sans dépendance à part les lib du système.
- **Pacman/src/txt**   : les classes s'occupant de faire tourner un pacman (core) et de l'afficher sur la console en texte, 
                       il y a une classe winTxt facilitant l'utilisation  une fenêtre texte et des évènements claviers.
- **Pacman/src/SDL2**  : les classes s'occupant de faire tourner un pacman (core) et de l'afficher avec SDL2
- **Pacman/src/sfml**  : les classes s'occupant de faire tourner un pacman (core) et de l'afficher avec SFML
- **Pacman/src/Qt**    : les classes s'occupant de faire tourner un pacman (core) et de l'afficher avec Qt
- **Pacman/extern**    : contient une version de SDL2 pour windows. 
                        Sous linux il faut installer SDL2 avec votre gestionnaire de package, voir la rubrique pour compiler.
- **Pacman/doc**       : le fichier doxygen qui permet de générer la documentation du code
- **Pacman/data**      : les assets (image, sons, etc.)
- **Pacman/bin**       : répertoire où les executables seront compilés 
- **Pacman/obj**       : répertoire comportant les compilations intermédiaires (.o)

- **Pacman/pacman.cbp** : fichier de projet pour compiler avec Codeblocks. 
                    Il faut choisir la cible DebugTXT pour compiler la version console/texte ou DebugSDL pour la version SDL2.
                    Normalement ce projet fonctionne sous CB 20.04 Linux et Windows 
                    (TODO : mettre à jour le répertoire EXTERN pour fonctionner avec le nv compilo de CB 20)

- **Pacman/Pacman_qt.pro** : le projet Qt. 

- **Pacman/pacman.code-workspace** : fichier d'environnement de Visual Code. A ouvrir pour compiler avec Visual Code.


Pour la documentation du code, voir la rubrique "documentation du code" plus bas.


## Pour compiler

### Préambule : si vous voulez un Linux sous Windows, installez WSL ! 

Voir la page de l'UE : https://perso.liris.cnrs.fr/alexandre.meyer/public_html/www/doku.php?id=lifap4#wsl_pour_faire_tourner_un_linux_ultra_leger_sous_windows

C'est léger, pratique, rapide et suffisant pour de nombreuses applications.
Windows/WSL est exactement comme une machine Linux avec des drivers minimalistes, 
donc la gestion de certains périphériques commes la carte son ou l'accélération 3D peut ne pas marcher mais pour ce cours ca peut être suffisant.
Il faut parcontre que vous ayez installé XMing pour pouvoir ouvrir des fen^tres comme expliqué sur la page du cours. 
Valgrind marche aussi !


### Pour installer SDL2
Pour installer SDL2 sous Linux ou avec WSL/Windows
``` sudo apt install python3 valgrind doxygen libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev imagemagick ```

Pour Windows, le répertoire extern contient une version précompilé de SDL2 pour CB.


### Version Texte/SDL2 sous Linux (Ubuntu ou Windows-WSL) avec Makefile :  bien testé, devrait marcher
``` make -f Makefile_txt_sdl ```

Editer le fichier Makefile pour choisir votre plateforme entre texte ou SDL !


### Version Texte/SDL2 avec VisualCode
en chantier ... je regarde, je regarde ... il y a déjà le pacman.code-workspace

La doc : `https://code.visualstudio.com/docs/languages/cpp`

Sous Windows :
- installer MinGW ou CodeBlocks 20 (qui installe MinGW)
- ajouter le chemin vers le compilateur dans la variable PATH. Dans Paramètres, rechercher PATH, puis Modifier variable d'environnements.
  Et ajouter le chemin, si CB : `C:\Program Files\CodeBlocks\MinGW\bin` et si MinGW `C:\MinGW\bin`
  Tester en lancant un CMDPrompt et taper `g++ --version`
- La version simple : ouvrer le terminal intégré à VisualCode avec le menu ou `ctrl+ù`puis lancer `mingw32-make -f Makefile_txt_sdl`
- la version intégré `ctrl+shift+B`
- Dans VisualCode : Ctrl+Shift+P et cherche `task`


### Version Texte/SDL2 sous Linux/Windows/Windows-WSL avec Codeblocks : bien testé, devrait marcher
Identique sous Linux et Windows après avoir installé SDL2.

Ouvrez pacman.cbp puis choisissez votre cible : DebugTXT ou DebugSDL pour avoir l'affichage texte ou SDL2.


### Version Qt : devrait marcher
Sous Linux ou sous Windows installez Qt en cochant QtCreator.
Ouvrez QtCreator et le projet pacman_qt.pro. Compilez et lancez.

En ligne de commande
```
qmake 
make
./pacman_qt
```



### Version SFML : 
Il faut installer SFML
```sudo apt-get install libsfml-dev```




##  Documentation du code

Voir src/documentation.h
soit avec doxygen, soit avec un �diteur de texte



