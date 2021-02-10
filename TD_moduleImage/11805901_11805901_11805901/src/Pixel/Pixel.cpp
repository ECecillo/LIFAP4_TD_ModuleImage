#include <iostream>
#include "Pixel.h"
#include <cassert>

using namespace std;

Pixel::Pixel() {
    r = 0;
    v = 0;
    b = 0;
}

Pixel::Pixel(const unsigned char nr,const unsigned char nv,const unsigned char nb) 
    : r(nr), v(nv), b(nb) {}

unsigned char Pixel::getRouge () const {
    return r;
}

unsigned char Pixel::getVert() const {
    return v;
}

unsigned char Pixel::getBleu () const {
    return b;    
}

void Pixel::setRouge (const unsigned char nr) {
    assert(nr <= 255);
    r = nr;
}

void Pixel::setVert (const unsigned char nv) {
    assert(nv <= 255);
    v = nv;
}

void Pixel::setBleu (const unsigned char nb) {
    assert(nb <= 255);
    b = nb;
}
bool Pixel::operator==(const Pixel& other) {
    return r == other.getRouge() &&
            v == other.getVert() &&
            b == other.getBleu();
}