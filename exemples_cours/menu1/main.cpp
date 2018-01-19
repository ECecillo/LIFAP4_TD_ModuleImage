// MENU 1

#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

void truc1()
{
	printf("truc1\n");
	fflush(stdout);
}

void truc2()
{
	printf("truc2\n");
	fflush(stdout);
}

void truc3()
{
	printf("truc3\n");
	fflush(stdout);
}

void truc4()
{
	printf("truc4\n");
	fflush(stdout);
}


int main()
{
	ChoixMenu cm;
	do
	{
		menuAff();
		cm = menuQuestion();
		switch(cm)
		{
			case MENU_Choix1 : truc1(); break;
			case MENU_Choix2 : truc2(); break;
			case MENU_Choix3 : truc3(); break;
			case MENU_Choix4 : truc4(); break;
			case MENU_Quit: break;
			default: printf("Choix non traité par le programme\n");
		}
		fflush(stdout);
	} while(cm!=MENU_Quit);

	return 0;
}
