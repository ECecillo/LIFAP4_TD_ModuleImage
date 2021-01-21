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
    setPix(Xmin,Ymin, couleur); // On fixe le bas à gauche du rectangle.
    setPix(Xmin,Ymax, couleur); // On fixe le haut à gauche du rectangle.
    
    setPix(Xmax,Ymax, couleur); // On fixe le haut à droite du rectangle.
    setPix(Xmax,Ymin, couleur); // On fixe le bas à droite du rectangle.
}

void Image::effacer (Pixel couleur) {

}

void Image::testRegression() {
    Image Im; 
    Pixel couleurRouge(255, 0, 0); 

    Image im(114, 29);

    cout << "Info du pixel dans l'image im aux coordo (100,15) :" << endl;
    im.getPix(100, 15);
    cout << endl;
    cout << "Info du pixel dans l'image Im aux coordo (0,0) :" << endl;
    Im.getPix(0, 0);
    cout << endl;

    cout << "On va set le pixel en (100,15) en rouge : " << endl;
    im.setPix(100, 15, couleurRouge);
    cout << endl;
    cout << "On set le pixel de Im en rouge" << endl;
    Im.setPix(0, 0, couleurRouge);
    cout << endl;

}