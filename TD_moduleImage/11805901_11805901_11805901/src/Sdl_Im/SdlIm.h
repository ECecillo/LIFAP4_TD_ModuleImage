#ifndef SDLIM_H
#define SDLIM_H

#include <iostream>
#include "Pixel.h"
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

class SdlIm
{
private:
    // Fenêtre SDL
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool souris;
    bool touche;

public:
    // ============ Fonctions pour la fenêtre SDL ========
    /**
	 * @brief 
	 * Gère les interactions avec l'utilisateur, appelle la fonction Affiche tant qu'on a pas fermé la fenêtre.
	 */
    void sdlBoucle();

    /**
	 * @brief 
	 * Appel les fonctions qui permettent d'afficher les images dans la fenêtre SDL.
	 */
    void sdlAff();

    ///
    /// @brief
    /// Effectue une série de tests vérifiant que le module fonctionne et
    /// que les données membres de l'objet sont conformes
    ///
    void testRegression();
};
#endif
