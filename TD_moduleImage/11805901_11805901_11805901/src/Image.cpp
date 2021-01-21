#include <iostream>
#include <Image.h>


using namespace std;


Image::Image () {
    dimx = 0;
    dimy = 0;
}

Image::~Image () {
    delete [] tab;
    dimx = 0;
    dimy = 0;
}

Image::Image(const unsigned int dimensionX, const unsigned int dimensionY) :
        dimx(dimensionX), dimy(dimensionY)
{
    Pixel * tab = new Pixel[dimx*dimy];
}

Pixel Image::getPix(unsigned int x,unsigned int y) {
    return tab[y*dimx+x];
}

void Image::setPix (unsigned int x,unsigned int y, Pixel couleur) {
    tab[y*dimx+x].setRouge(couleur.getRouge());
    tab[y*dimx+x].setBleu(couleur.getBleu());
    tab[y*dimx+x].setVert(couleur.getVert());
}

void Image::dessinerRectangle (unsigned int Xmin,unsigned int Ymin,unsigned int Xmax,unsigned int Ymax, Pixel couleur) {

}

void Image::effacer (Pixel couleur) {

}

void Image::testRegression() {

}