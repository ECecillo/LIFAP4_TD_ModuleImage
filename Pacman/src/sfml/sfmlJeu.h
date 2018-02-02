#ifndef _SFMLJEU_H
#define _SFMLJEU_H

#include "Jeu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

/**
    La classe gérant le jeu avec un affichage SFML
*/

class sfmlJeu {

private :

	Jeu jeu;
	sf::RenderWindow * m_window;

    sf::Texture tx_pacman;
    sf::Texture tx_mur;
    sf::Texture tx_pastille;
    sf::Texture tx_fantome;

    sf::Sprite sp_pacman;
    sf::Sprite sp_mur;
    sf::Sprite sp_pastille;
    sf::Sprite sp_fantome;

    sf::Font m_font;
    sf::Text m_text;

    sf::SoundBuffer m_soundbuffer;
    sf::Sound m_sound;

public :

    sfmlJeu ();
    ~sfmlJeu ();

    void sfmlInit();
    void sfmlBoucle();
    void sfmlAff();

};

#endif
