// MENU 2

#include <stdio.h>
#include <stdlib.h>

#include "menu.h"

class Camion
{
	int a;
	void calcul() {}
};

void truc1(Camion& c)
{
	printf("fonction truc1\n");
	fflush(stdout);
}

void truc2()
{
	printf("fonction truc2\n");
	fflush(stdout);
}

void truc3()
{
	printf("fonction truc3\n");
	fflush(stdout);
}


void Quitter()
{
	printf("fin\n");
	exit(0);
}

void trucmachin()
{
	printf("trucmachin\n");
}

int main()
{
	Menu m;
	m.ajouterLigne( "Quitter", &Quitter);
	m.ajouterLigne( "Truc1", &truc1);
	m.ajouterLigne( "Truc2", &truc2);
	m.ajouterLigne( "Fonction trucmachin", &trucmachin);
	m.ajouterLigne( "Fonction truc3", &truc3);

	m.loop();

	return 0;
}
