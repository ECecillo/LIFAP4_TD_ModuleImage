// MENU 3

#include <stdio.h>
#include <stdlib.h>

#include "menu.h"

struct Camion
{
   int id;
   int poids;
};

struct Voiture
{
   int id;
};

void truc1(void* _cam)
{
	Camion* cam = ((Camion*)(_cam));
	printf("fonction truc1 %d %d\n", cam->id, cam->poids);
	fflush(stdout);
}

void truc2(Camion* cam)
{
	printf("fonction truc2 %d %d\n", cam->id, cam->poids);
	fflush(stdout);
}

void truc3(Voiture* voiture)
{
	printf("fonction truc3 %d\n", voiture->id);
	fflush(stdout);
}


void Quitter(void* )
{
	printf("fin\n");
	exit(0);
}

void trucmachin(void* )
{
	printf("trucmachin\n");
}

int main()
{
	Menu m;
	Camion cam1 = { 0, 33000 };
	Camion cam2 = { 1, 14000 };
	Voiture voit = { 2 };
	
	m.ajouterLigne( "Quitter", &Quitter, NULL);
	m.ajouterLigne( "Truc1", &truc1, &cam1);
	m.ajouterLigne( "Truc2", ((MenuFonction)(&truc2)), &cam2);
	m.ajouterLigne( "Fonction truc3", ((MenuFonction)(&truc3)), &voit);
	m.ajouterLigne( "Fonction trucmachin", &trucmachin, NULL);

	m.loop();

	return 0;
}
