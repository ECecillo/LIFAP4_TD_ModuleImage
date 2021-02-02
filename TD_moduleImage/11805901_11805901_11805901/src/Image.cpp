#include <iostream>
#include <Image.h>
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

Pixel Image::getPix(unsigned int x,unsigned int y) {
    assert(x >= 0 && y >= 0);
    return tab[y*dimx+x];
}

void Image::setPix (unsigned int x,unsigned int y, const Pixel& couleur) {
    assert((x >= 0 && y >= 0));
    assert((couleur.getRouge() >= 0 && couleur.getRouge() <= 255) &&
    (couleur.getBleu() >= 0 && couleur.getBleu() <= 255) &&
    (couleur.getVert() >= 0 && couleur.getVert() <= 255) );
    
    tab[y*dimx+x] = couleur;
}

void Image::dessinerRectangle (unsigned int Xmin,unsigned int Ymin,unsigned int Xmax,unsigned int Ymax, const Pixel& couleur) {
    assert(
    (Xmin >= 0 && Ymin >= 0) &&
    (Xmax > 0 && Ymax > 0));
    assert((Xmax >= Xmin && Ymax > Ymin));

    assert(
    (couleur.getRouge() >= 0 && couleur.getRouge() <= 255) &&
    (couleur.getBleu() >= 0 && couleur.getBleu() <= 255) &&
    (couleur.getVert() >= 0 && couleur.getVert() <= 255));

    for(int i = Xmin; i <= Xmax; i++) {
        for (int j = Ymin; j <= Ymax; j++) {
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

void Image::sauver(const string & filename) const 
{
	assert(!filename.empty());

    ofstream fichier(filename.c_str());
    assert(fichier.is_open());
    
    fichier << "P3" << endl;
    fichier << dimx << " " << dimy << endl;
    fichier << "255" << endl;
    for(unsigned int y=0; y<dimy; ++y)
        for(unsigned int x=0; x<dimx; ++x) {
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

void Image::afficherConsole() const{
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
    Image Im; 
    Pixel couleurRouge(255, 0, 0);
    Pixel couleurRouge2(255, 0, 0);
    // Test de l'opérateur == 
    if (couleurRouge == couleurRouge2) {
        cout << "Succes test egalite entre pixel." << endl;

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
    else {
        cout << "Le test d'égalité entre pixel n'est pas concluant" << endl;
    }

}