#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <fstream>
#include <string.h>
#include "Pixel.h"
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

/**
 * @brief 
 * Class qui génère une image et la charge pour la SDL
 * 
 */
class Image
{
private:
	Pixel *tab;				 // Tableau 1D de Pixel.
	unsigned int dimx, dimy; // Les dimensions de l'image.

	// Image
	SDL_Surface *surface;
	SDL_Texture *texture;
	bool has_changed;

	// Fenêtre SDL
	SDL_Window *window;
	SDL_Renderer *renderer;

	bool souris;
	bool touche;

public:
	/**
	 * @brief Construit une nouvelle image et construit une Fenêtre SDL.
	 * 
	 */
	Image();

	///
	/// @brief
	/// Constructeur de la classe: initialise dimx et dimy (après vérification)
	/// puis alloue le tableau de pixel dans le tas (image noire)
	/// @param
	/// dimensionX : largeur de l'image que l'on veut créer.
	/// @param
	/// dimensionY :  hauteur de l'image que l'on veut créer.
	Image(const unsigned int dimensionX, const unsigned int dimensionY);

	///
	/// @brief
	/// Destructeur de la classe: déallocation de la mémoire du tableau de pixels
	/// et mise à jour des champs dimx et dimy à 0.
	///
	///
	~Image();

	///
	/// @brief
	/// Accesseur : récupère le pixel original de coordonnées (x,y) en vérifiant leur validité
	/// la formule pour passer d'un tab 2D à un tab 1D est tab[y*dimx+x]
	/// @param
	/// x : coordonnées x du pixel à récupérer.
	/// @param
	/// y : coordonnées y du pixel à récupérer.
	///
	Pixel &getPix(unsigned int x, unsigned int y) const;

	///
	/// @brief
	/// Mutateur : modifie le pixel de coordonnées (x,y)
	/// @param
	/// x : coordonnées x du pixel.
	/// @param
	/// y : coordonnées y du pixel.
	/// @param
	/// couleur : Couleur de type Pixel.
	void setPix(unsigned int x, unsigned int y, const Pixel &couleur);

	///
	/// @brief
	/// Dessine un rectangle plein de la couleur dans l'image (en utilisant setPix, indices en paramètre compris)
	/// @param
	/// Xmin : X de début du rectangle qui va d'en bas à gauche.
	/// @param
	/// Ymin : Y de début du rectangle qui va d'en bas à gauche.
	/// @param
	/// Xmax : X de fin du rectangle qui se termine en haut à droite.
	/// @param
	/// Ymax : Y de fin du rectangle qui se termine en haut à droite.
	void dessinerRectangle(unsigned int Xmin, unsigned int Ymin, unsigned int Xmax, unsigned int Ymax, const Pixel &couleur);

	/**
	 * @brief
	 * Efface le contenu de l'image en la remplissant de couleur
	 * @param [in]
	 * Couleur
	 */
	void effacer(const Pixel &couleur);

	/**
	 * @brief
	 * Sauvegarde l'image au format ppm
	 * @param [in]
	 * Chemin de la sauvegarde
	 */
	void sauver(const string &filename);

	/**
	 * @brief
	 * Ouvrir une image de format ppm
	 * @param [in]
	 * Chemin de l'image
	 */
	void ouvrir(const string &filename);

	/**
	 * @brief
	 * Afficher l'image dans la console
	 */
	void afficherConsole();

	///
	/// @brief
	/// Affiche l'image dans une fenêtre SDL2
	///
	void afficher();

	// ============ Fonctions pour charger/afficher Image ========
	/**
	 * @brief 
	 * Charge L'image que l'on passe en paramètre.
	 * @param filename : Nom du fichier à ouvrir peut être de n'importe qu'elle format du moment qu'on précise ce dernier.
	 * @param renderer : Structure qui s'occupe de toute le rendu. Lié à SDL_Window qui est une structure où l'on a ttes les infos de la fenêtre SDL.
	 */
	void loadFromFile(const char *filename, SDL_Renderer *renderer);

	/**
	 * @brief 
	 * 
	 * @param renderer : Structure qui s'occupe de toute le rendu. Lié à SDL_Window qui est une structure où l'on a ttes les infos de la fenêtre SDL.
	 */
	void loadFromCurrentSurface(SDL_Renderer *renderer);

	/**
	 * @brief 
	 * Fonction qui s'occupe de générer L'image en fontion des dimensions x,y,w,h passé en paramètre.
	 * @param renderer 
	 * @param x : Position x de la fenêtre.
	 * @param y : Position y de la fenêtre.
	 * @param w : Largeur de la fenêtre.
	 * @param h : Hauteur de la fenêtre.
	 */
	void draw(SDL_Renderer *renderer, int x, int y, int w = -1, int h = -1);


	/**
	 * @brief Get the Texture object
	 * Retourne la texture qui est en privé.
	 * @return SDL_Texture* 
	 */
	SDL_Texture *getTexture() const;

	/**
	 * @brief Set the Surface object
	 * Défini la valeur de la Surface qui est dans la partie privé de la Classe Image.
	 * @param surf 
	 */
	void setSurface(SDL_Surface *surf);

	
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