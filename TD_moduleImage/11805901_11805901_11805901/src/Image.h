#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <fstream>
#include <string.h>
#include "Pixel.h"

using namespace std;

class Image
{
private:
	Pixel *tab;				 // Tableau 1D de Pixel.
	unsigned int dimx, dimy; // Les dimensions de l'image.

public:
	///
	/// @param
	/// Constructeur par défaut de la classe: initialise dimx et dimy à 0
	/// ce constructeur n'alloue pas de pixel
	///
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
	/// et mise à jour des champs dimx et dimy à 0
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
	void sauver(const string &filename) const;

	/**
	 * @brief
	 * Ouvrir une image de format ppm
	 * @param [in]
	 * Chemin de l'image
	 */
	void ouvrir(const std::string &filename);

	/**
	 * @brief
	 * Afficher l'image dans la console
	 */
	void afficherConsole() const;

	/// 
	/// @brief
	/// Effectue une série de tests vérifiant que le module fonctionne et
	/// que les données membres de l'objet sont conformes
	/// 
	void testRegression();
};
#endif