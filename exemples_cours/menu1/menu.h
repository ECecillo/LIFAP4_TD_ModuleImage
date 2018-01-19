

#ifndef _MENU_H
#define _MENU_H

enum ChoixMenu { MENU_Choix1=1, MENU_Choix2=2, MENU_Choix3=3, MENU_Choix4=4, MENU_Quit=0 };
extern const int MENU_MAX;

void menuAff();
ChoixMenu menuQuestion();

#endif
