#include "Terrain.h"
#include <cassert>

const char terrain1[15][21] = { // On prend ce terrain en référence de caractère et on l'affichage dans le sens inverse.
 "####################",
 "#.###....##........#",
 "#.#####..##...####.#",
 "#........##........#",
 "#........###.......#",
 "#...#..#....#......#",
 "#......#...##......#",
 "#####..#....#..#####",
 "#......##...#......#",
 "#......#....#......#",
 "#..................#",
 "#..................#",
 "#.....#......#.....#",
 "#.....#......#.....#",
 "####################"
};

const char terrain2[15][21] = {
 "####################",
 "#.###....##.....#..#",
 "#.#####..##...####.#",
 "#........##........#",
 "#........###.......#",
 "#...#..#....#......#",
 "#......#...##......#",
 "#####..#....#..#####",
 "#......##...#......#",
 "#......#....#......#",
 "#..................#",
 "#..................#",
 "#.....#......#.....#",
 "#.....#......#.....#",
 "####################"
};


Terrain::Terrain () { // Met dans le tableau 2D terrain les caractères du terrain déclarré ci-dessus.
	dimx = 20;
	dimy = 15;
	for(int x=0;x<dimx;++x)
		for(int y=0;y<dimy;++y)
			ter[x][y] = terrain1[dimy-1-y][x];
}

bool Terrain::estPositionPersoValide (const int x, const int y) const {
	return ((x>=0) && (x<dimx) && (y>=0) && (y<dimy) && (ter[x][y]!='#'));
}

void Terrain::mangePastille (const int x, const int y) {
	assert(x>=0);
	assert(y>=0);
	assert(x<dimx);
	assert(y<dimy);
	ter[x][y]=' ';
}

char Terrain::getXY (const int x, const int y) const {
	assert(x>=0);
	assert(y>=0);
	assert(x<dimx);
	assert(y<dimy);
	return ter[x][y];
}

int Terrain::getDimX () const { return dimx; }

int Terrain::getDimY () const {	return dimy; }
