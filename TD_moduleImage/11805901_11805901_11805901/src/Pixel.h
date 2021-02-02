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
        Pixel (const unsigned char nr,const unsigned char nv, const unsigned char nb);
   
        // Accesseur : récupère la composante rouge du pixel
        unsigned char getRouge () const;

        // Accesseur : récupère la composante verte du pixel
        unsigned char getVert () const;

        // Accesseur : récupère la composante bleue du pixel
        unsigned char getBleu () const;

        // Mutateur : modifie la composante rouge du pixel
        void setRouge (const unsigned char nr);

        // Mutateur : modifie la composante verte du pixel
        void setVert (const unsigned char nv);

        // Mutateur : modifie la composante bleue du pixel
        void setBleu (const unsigned char nb);

        bool operator==(const Pixel& other);
};

#endif