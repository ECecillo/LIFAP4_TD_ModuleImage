#ifndef PIXEL_H
#define PIXEL_H

#include <iostream>

using namespace std;

class Pixel {
    private :
        unsigned char r,v,b; // Les composantes du pixel, unsigned char en C++.
    
    public :
        // Constructeur par défaut de la classe: initialise le pixel à la couleur noire
        Pixel();

        // Constructeur de la classe: initialise r,g,b avec les paramètres   
        Pixel (const unsigned int nr,const unsigned int nv, const unsigned int nb);
   
        // Accesseur : récupère la composante rouge du pixel
        int getRouge () const;

        // Accesseur : récupère la composante verte du pixel
        int getVert () const;

        // Accesseur : récupère la composante bleue du pixel
        int getBleu () const;

        // Mutateur : modifie la composante rouge du pixel
        void setRouge (const unsigned int nr);

        // Mutateur : modifie la composante verte du pixel
        void setVert (const unsigned int nv);

        // Mutateur : modifie la composante bleue du pixel
        void setBleu (const unsigned int nb);
};

#endif