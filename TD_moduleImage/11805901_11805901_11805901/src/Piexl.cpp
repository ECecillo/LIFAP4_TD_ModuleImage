#include <iostream>
#include "Pixel.h"

using namespace std;

Pixel::Pixel() {
    r = 0;
    v = 0;
    b = 0;
}

Pixel::Pixel(const unsigned int nr,const unsigned int nv,const unsigned int nb) 
    : r(nr), v(nv), b(nb) {}

int Pixel::getRouge () const {
    return r;
}

int Pixel::getVert() const {
    return v;
}

int Pixel::getBleu () const {
    return b;    
}

void Pixel::setRouge (const unsigned int nr) {
    r = nr;
}

void Pixel::setVert (const unsigned int nv) {
    v = nv;
}

void Pixel::setBleu (const unsigned int nb) {
    b = nb;
}