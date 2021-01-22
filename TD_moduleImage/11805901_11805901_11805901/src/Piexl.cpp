#include <iostream>
#include "Pixel.h"
#include <cassert>

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
    assert(nr >= 0 && nr <= 255);
    r = nr;
}

void Pixel::setVert (const unsigned int nv) {
    assert(nv >= 0 && nv <= 255);
    v = nv;
}

void Pixel::setBleu (const unsigned int nb) {
    assert(nb >= 0 && nb <= 255);
    b = nb;
}