#include <cassert>
#include <time.h>
#include "sfmlJeu.h"
#include <stdlib.h>

using namespace sf;

#include <iostream>
using namespace std;

const int TAILLE_SPRITE = 32;

sfmlJeu::sfmlJeu () : jeu() {
    int dimx = jeu.getConstTerrain().getDimX() * TAILLE_SPRITE;
    int dimy = jeu.getConstTerrain().getDimY() * TAILLE_SPRITE;
    m_window = new RenderWindow(VideoMode(dimx,dimy), "Pacman");
}

void sfmlJeu::sfmlInit() {

    if (!tx_pacman.loadFromFile("data/pacman.png")) {cout << "Error data/pacman.png non found" << endl;}
    else {
            sp_pacman.setTexture(tx_pacman);
            float taillePacman = tx_pacman.getSize().x;
            Vector2f scalePacman (TAILLE_SPRITE/taillePacman,TAILLE_SPRITE/taillePacman);
            sp_pacman.setScale(scalePacman);
    }
    if (!tx_mur.loadFromFile("data/mur.png")) {cout << "Error data/mur.png non found" << endl;}
    else {
            sp_mur.setTexture(tx_mur);
            float tailleMur = tx_mur.getSize().x;
            Vector2f scaleMur (TAILLE_SPRITE/tailleMur,TAILLE_SPRITE/tailleMur);
            sp_mur.setScale(scaleMur);
    }
    if (!tx_pastille.loadFromFile("data/pastille.png")) {cout << "Error data/pastille.png non found" << endl;}
    else {
            sp_pastille.setTexture(tx_pastille);
            float taillePastille = tx_pastille.getSize().x;
            Vector2f scalePastille (TAILLE_SPRITE/taillePastille,TAILLE_SPRITE/taillePastille);
            sp_pastille.setScale(scalePastille);
    }
    if (!tx_fantome.loadFromFile("data/fantome.png")) {cout << "Error data/fantome.png non found" << endl;}
    else {
            sp_fantome.setTexture(tx_fantome);
            float tailleFantome = tx_fantome.getSize().x;
            Vector2f scaleFantome (TAILLE_SPRITE/tailleFantome,TAILLE_SPRITE/tailleFantome);
            sp_fantome.setScale(scaleFantome);
    }

    if (!m_font.loadFromFile("data/DejaVuSansCondensed.ttf")) {cout << "Error data/DejaVuSansCondensed.ttf non found" << endl;}
    else {
        m_text.setFont(m_font);
        m_text.setString("Pacman");
        m_text.setCharacterSize(30);
        m_text.setFillColor(Color::Blue);
        m_text.setPosition(Vector2f(270,30));
    }
    if (!m_soundbuffer.loadFromFile("data/son.wav")) {cout << "Error data/son.wav non found" << endl;}
    else {
        m_sound.setBuffer(m_soundbuffer);
    }

}


sfmlJeu::~sfmlJeu () {
    if (m_window != NULL) delete m_window;
}

void sfmlJeu::sfmlAff() {
    m_window->clear(Color(230, 240, 255, 255));

    const Terrain& ter = jeu.getConstTerrain();
	const Pacman& pac = jeu.getConstPacman();
	const Fantome& fan = jeu.getConstFantome();

    // Afficher les sprites des murs et des pastilles
	for (int x=0;x<ter.getDimX();++x) {
		for (int y=0;y<ter.getDimY();++y) {
            if (ter.getXY(x,y)=='.') {
                sp_pastille.setPosition(Vector2f(x*TAILLE_SPRITE,y*TAILLE_SPRITE));
                m_window->draw(sp_pastille);
            }
            if (ter.getXY(x,y)=='#') {
                sp_mur.setPosition(Vector2f(x*TAILLE_SPRITE,y*TAILLE_SPRITE));
                m_window->draw(sp_mur);
            }
		}
	}

	// Afficher le sprite de Pacman
	sp_pacman.setPosition(Vector2f(pac.getX()*TAILLE_SPRITE,pac.getY()*TAILLE_SPRITE));
	m_window->draw(sp_pacman);

	// Afficher le sprite du Fantome
	sp_fantome.setPosition(Vector2f(fan.getX()*TAILLE_SPRITE,fan.getY()*TAILLE_SPRITE));
	m_window->draw(sp_fantome);

    // Ecrire un titre par dessus
    m_window->draw(m_text);

    m_window->display();
}

void sfmlJeu::sfmlBoucle () {

    Clock clock;

    while (m_window->isOpen())
    {
        float elapsed = clock.getElapsedTime().asSeconds();
        if (elapsed > 0.5) {
            // mouvement fantomes
            jeu.actionsAutomatiques();
            clock.restart();
        }

        Event event;

        while (m_window->pollEvent(event))
        {
            if (event.type == Event::Closed)
                m_window->close();

            if (event.type == Event::KeyPressed) {
                bool mangePastille = false;
                switch (event.key.code) {
                case Keyboard::Up : mangePastille = jeu.actionClavier('b');    // car Y inverse
					break;
				case Keyboard::Down : mangePastille = jeu.actionClavier('h');     // car Y inverse
					break;
				case Keyboard::Left : mangePastille = jeu.actionClavier('g');
					break;
				case Keyboard::Right : mangePastille = jeu.actionClavier('d');
					break;
                default : break;
                }

                if (mangePastille) m_sound.play();
            }
        }

        sfmlAff();
    }

}
