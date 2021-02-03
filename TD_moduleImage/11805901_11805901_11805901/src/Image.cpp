#include <iostream>
#include "Image.h"
#include <fstream>
#include <string.h>
#include <cassert> // Pour les assert.

using namespace std;


Image::Image () {
    tab = NULL;
    dimy = dimx = 0;
}

Image::~Image () {
    delete [] tab;
    tab = NULL; 
    dimy = dimx = 0;
}

Image::Image(const unsigned int dimensionX, const unsigned int dimensionY)
{
    assert(dimensionX > 0 && dimensionY > 0);
    dimx = dimensionX;
    dimy = dimensionY;
    tab = new Pixel[dimx*dimy];
}

Pixel& Image::getPix(unsigned int x,unsigned int y) const {
    assert(x <= dimx && y <= dimy);
    return tab[y*dimx+x];
}

void Image::setPix (unsigned int x,unsigned int y, const Pixel& couleur) {
    assert(x <= dimx && y <= dimy);
    assert((couleur.getRouge() >= 0 && couleur.getRouge() <= 255) &&
    (couleur.getBleu() >= 0 && couleur.getBleu() <= 255) &&
    (couleur.getVert() >= 0 && couleur.getVert() <= 255) );
    
    tab[y*dimx+x] = couleur;
}

void Image::dessinerRectangle (unsigned int Xmin,unsigned int Ymin,unsigned int Xmax,unsigned int Ymax, const Pixel& couleur) {
    assert((Xmax > 0 && Ymax > 0) && (Xmax <= dimx && Ymax <= dimy));
    assert((Xmax >= Xmin && Ymax >= Ymin));

    assert(
    (couleur.getRouge() >= 0 && couleur.getRouge() <= 255) &&
    (couleur.getBleu() >= 0 && couleur.getBleu() <= 255) &&
    (couleur.getVert() >= 0 && couleur.getVert() <= 255));

    for(unsigned int i = Xmin; i <= Xmax; i++) {
        for (unsigned int j = Ymin; j <= Ymax; j++) {
            setPix(i,j,couleur);
        }
    }
}

void Image::effacer(const Pixel& couleur)
{
	assert(
  couleur.getRouge() >= 0 && couleur.getRouge() <= 255 &&
	couleur.getVert() >= 0 && couleur.getVert() <= 255 &&
	couleur.getBleu() >= 0 && couleur.getBleu() <= 255);

	dessinerRectangle(0, 0, dimx - 1, dimy - 1, couleur);
}


void Image::sauver(const string & filename) 
{
	assert(!filename.empty());
    ofstream fichier(filename.c_str());
    assert(fichier.is_open());

    fichier << "P3" << endl;
    fichier << dimx << " " << dimy << endl;
    fichier << "255" << endl;
    for(unsigned int y = 0; y < dimy; ++y)
        for(unsigned int x = 0; x < dimx; x++) {
            Pixel& pix = getPix(x, y);
            fichier << +pix.getRouge() << " " << +pix.getVert() << " " << +pix.getBleu() << " ";
        }
    cout << "Sauvegarde de l'image " << filename << " ... OK\n";
    fichier.close();
}

void Image::ouvrir(const string & filename) 
{
	assert(!filename.empty());

    ifstream fichier(filename.c_str());
    assert(fichier.is_open());

    unsigned int r,g,b;
    string mot;
    //dimx = dimy = 0;
    fichier >> mot >> dimx >> dimy >> mot;
    assert(dimx > 0 && dimy > 0);
    if (tab != NULL) delete[] tab;
    tab = new Pixel[dimx*dimy];

    for(unsigned int y=0; y<dimy; ++y)
        for(unsigned int x=0; x<dimx; ++x) {
            fichier >> r >> g >> b;
            getPix(x,y).setRouge((unsigned char)r);
            getPix(x,y).setVert((unsigned char)g);
            getPix(x,y).setBleu((unsigned char)b);
        }
    fichier.close();
    cout << "Lecture de l'image " << filename << " ... OK\n";
}

void Image::afficherConsole() {
    cout << dimx << " " << dimy << endl;
    for(unsigned int y=0; y<dimy; ++y) {
        for(unsigned int x=0; x<dimx; ++x) {
            Pixel& pix = getPix(x,y);
            cout << +pix.getRouge() << " " << +pix.getVert() << " " << +pix.getBleu() << " ";
        }
        cout << endl;
    }
} 

void Image::testRegression() {
    Pixel pix(4,5,6);

    /* test des get dans Pixel */
    if (pix.getRouge()==4 && pix.getVert()==5 && pix.getBleu()==6) {
        cout << "les get de Pixel fonctionnent" << endl;
    }
    else {
        cout << "Problème avec les get de Pixel"<< endl;
    }

    /* test des set dans Pixel */
    pix.setRouge(7);
    pix.setVert(8);
    pix.setBleu(9);
    if (pix.getRouge()==7 && pix.getVert()==8 && pix.getBleu()==9) {
        cout << "les set de Pixel fonctionnent" << endl;
    }
    else {
        cout << "Problème avec les set de Pixel"<< endl;
    }
    

    /* test du constructeur d'Image */
    /* if (dimx == 4 && dimy == 3) {
        cout << "Le constructeur d'Image fonctionne" << endl;
    }
    else {
        cout << "Problème avec le constructeur d'Image" << endl;
    } */

    /* test de getPix */
    Pixel p = getPix(0,0);
    if (p.getRouge() == 0 && p.getVert() == 0 && p.getBleu() == 0) {
        cout << "getPix fonctionne" << endl;
    }
    else {
        cout << "Problème avec getPix" << endl;
    }

    /* test de setPix */
    setPix(1,2,pix);
    p = getPix(1,2);
    if (p.getRouge() == pix.getRouge() && p.getVert() == pix.getVert() && p.getBleu() == pix.getBleu()) {
        cout << "setPix fonctionne" << endl;
    }
    else {
        cout << "Problème avec setPix" << endl;
    }

    /*test de dessinerRectangle */
    dessinerRectangle (0,0,3,2,pix);
    bool testPix = true;
    for (int i = 0; i <= 3; i++) {
			for (int j = 0; j <= 2; j++) {
				if (!(tab[j * dimx + i] == pix))
				{
					testPix = false;
				}
			}
		}
    if (testPix) {
        cout << "dessinerRectangle fonctionne" << endl;
    }
    else {
        cout << "Problème avec dessinerRectangle" << endl;
    }

    /* test de effacer */
    pix.setRouge(0);
    effacer(pix); // (0, 5, 6) = pix.
    testPix = true;
    for (unsigned i = 0; i<4; i++) {
        for (unsigned j = 0; j<3; j++) {
            if(!(getPix(i,j) == pix)) testPix = false;
        }
    }
    if (testPix) {
        cout << "effacer fonctionne" << endl;
    }
    else {
        cout << "Problème avec effacer" << endl;
    }
}
