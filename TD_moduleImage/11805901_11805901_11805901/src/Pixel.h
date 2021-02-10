#ifndef PIXEL_H
#define PIXEL_H

#include <iostream>

using namespace std;

class Pixel
{
private:
    unsigned char r, v, b;

public:
    ///
    /// @brief
    /// Constructeur par défaut de la classe: initialise le pixel à la couleur noire
    ///
    Pixel();

    ///
    /// @brief
    /// Constructeur de la classe: initialise r,g,b avec les paramètres
    /// @param
    /// nr : [0, ... 255] rouge.
    /// @param
    /// nv : [0, ... 255] vert.
    /// @param
    /// nb : [0, ... 255] bleu.
    ///
    Pixel(const unsigned char nr, const unsigned char nv, const unsigned char nb);

    ///
    /// @brief
    /// Accesseur : récupère la composante rouge du pixel
    ///
    unsigned char getRouge() const;

    ///
    /// @brief
    /// Accesseur : récupère la composante verte du pixel
    ///
    unsigned char getVert() const;

    ///
    /// @brief
    /// Accesseur : récupère la composante bleue du pixel
    ///
    unsigned char getBleu() const;

    ///
    /// @brief
    /// Mutateur : modifie la composante rouge du pixel
    ///
    void setRouge(const unsigned char nr);

    ///
    /// @brief
    /// Mutateur : modifie la composante verte du pixel
    ///
    void setVert(const unsigned char nv);

    ///
    /// @brief
    /// Mutateur : modifie la composante bleue du pixel
    ///
    void setBleu(const unsigned char nb);

    bool operator==(const Pixel &other);
};

#endif