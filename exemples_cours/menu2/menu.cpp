// MENU 2
#include <cstdio>
#include <cstring>
#include "menu.h"
#include <cassert>

//const int MENU_MAX = 4;

Menu::Menu() : nb_lignes(0)
{
}

void Menu::ajouterLigne(const char txt[64], MenuFonction fonct)
{
    assert( nb_lignes<32 );
	strcpy(  lignes[ nb_lignes ].texte, txt);
	lignes[ nb_lignes ].fonction_commande = fonct;
	nb_lignes++;
}

Menu::~Menu()
{
	nb_lignes = 0;
}

void Menu::afficher()
{
	int i;
	printf("\n\nMenu\n");
	for(i=0;i<nb_lignes;++i)
		printf("%d : %s\n", i, lignes[i].texte);
	printf("Votre choix?\n");
	fflush(stdout);
}

int Menu::question()
{
	int cm;
	char dum[32];
	bool ok=false;
	do
	{
		if (scanf("%d",&cm)!=1) scanf("%s",dum);
		if ((cm<0) || (cm>=nb_lignes))
			printf("Erreur choix menu\n");
		else ok=true;
		fflush(stdout);
	} while(!ok);
	printf("\n"); fflush(stdout);
	return cm;
}

void Menu::loop()
{
	int cm;
	while(true)
	{
		afficher();
		cm = question();
		lignes[ cm ].fonction_commande();
	}
}
