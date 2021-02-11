#include <iostream>
#include "Image.h"
#include <fstream>
#include <string.h>
#include <cassert> // Pour les assert.

using namespace std;

Image::Image()
{
    tab = NULL;
    dimy = dimx = 0;
    zoomLevel = 50;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    surface = NULL;
    texture = NULL;
    has_changed = false;
}

Image::~Image()
{
    delete[] tab;
    tab = NULL;
    zoomLevel = 5;
    dimy = dimx = 0;
}

Image::Image(const unsigned int dimensionX, const unsigned int dimensionY)
{
    assert(dimensionX > 0 && dimensionY > 0);
    dimx = dimensionX;
    dimy = dimensionY;
    zoomLevel = 5;
    tab = new Pixel[dimx * dimy];
    // Construction de la SDL.
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    // Creation de la fenetre
    window = SDL_CreateWindow("Module_Image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, dimx, dimy);
}

Pixel &Image::getPix(unsigned int x, unsigned int y) const
{
    assert(x <= dimx && y <= dimy);
    return tab[y * dimx + x];
}

void Image::setPix(unsigned int x, unsigned int y, const Pixel &couleur)
{
    assert(x <= dimx && y <= dimy);
    assert((couleur.getRouge() >= 0 && couleur.getRouge() <= 255) &&
           (couleur.getBleu() >= 0 && couleur.getBleu() <= 255) &&
           (couleur.getVert() >= 0 && couleur.getVert() <= 255));

    tab[y * dimx + x] = couleur;
}

void Image::dessinerRectangle(unsigned int Xmin, unsigned int Ymin, unsigned int Xmax, unsigned int Ymax, const Pixel &couleur)
{
    assert((Xmax > 0 && Ymax > 0) && (Xmax <= dimx && Ymax <= dimy));
    assert((Xmax >= Xmin && Ymax >= Ymin));

    assert(
        (couleur.getRouge() >= 0 && couleur.getRouge() <= 255) &&
        (couleur.getBleu() >= 0 && couleur.getBleu() <= 255) &&
        (couleur.getVert() >= 0 && couleur.getVert() <= 255));

    for (unsigned int i = Xmin; i <= Xmax; i++)
    {
        for (unsigned int j = Ymin; j <= Ymax; j++)
        {
            setPix(i, j, couleur);
        }
    }
}

void Image::effacer(const Pixel &couleur)
{
    assert(
        couleur.getRouge() >= 0 && couleur.getRouge() <= 255 &&
        couleur.getVert() >= 0 && couleur.getVert() <= 255 &&
        couleur.getBleu() >= 0 && couleur.getBleu() <= 255);

    dessinerRectangle(0, 0, dimx - 1, dimy - 1, couleur);
}

void Image::sauver(const string &filename) const
{
    assert(!filename.empty());

    ofstream fichier(filename.c_str());
    assert(fichier.is_open());
    fichier << "P3" << endl;
    fichier << dimx << " " << dimy << endl;
    fichier << "255" << endl;
    for (unsigned int y = 0; y < dimy; ++y)
        for (unsigned int x = 0; x < dimx; ++x)
        {
            Pixel &pix = getPix(x, y);
            fichier << +pix.getRouge() << " " << +pix.getVert() << " " << +pix.getBleu() << " ";
        }
    cout << "Sauvegarde de l'image " << filename << " ... OK\n";
    fichier.close();
}

void Image::ouvrir(const string &filename)
{
    assert(!filename.empty());

    ifstream fichier(filename.c_str());
    assert(fichier.is_open());

    unsigned int r, g, b;
    string mot;
    //dimx = dimy = 0;
    fichier >> mot >> dimx >> dimy >> mot;
    assert(dimx > 0 && dimy > 0);
    if (tab != NULL)
        delete[] tab;
    tab = new Pixel[dimx * dimy];

    for (unsigned int y = 0; y < dimy; ++y)
        for (unsigned int x = 0; x < dimx; ++x)
        {
            fichier >> r >> g >> b;
            getPix(x, y).setRouge((unsigned char)r);
            getPix(x, y).setVert((unsigned char)g);
            getPix(x, y).setBleu((unsigned char)b);
        }
    fichier.close();
    cout << "Lecture de l'image " << filename << " ... OK\n";
}

void Image::afficherConsole()
{
    cout << dimx << " " << dimy << endl;
    for (unsigned int y = 0; y < dimy; ++y)
    {
        for (unsigned int x = 0; x < dimx; ++x)
        {
            Pixel &pix = getPix(x, y);
            cout << +pix.getRouge() << " " << +pix.getVert() << " " << +pix.getBleu() << " ";
        }
        cout << endl;
    }
}
void Image::affInit()
{
    //Remplir l'écran de blanc
    SDL_SetRenderDrawColor(renderer, 211, 211, 211, 255); // Fond gris clair.
    SDL_RenderClear(renderer);

    if (SDL_SetRenderTarget(renderer, texture) != 0)
    {
        cout << "Erreur SDL_SetRenderTarget : " << SDL_GetError() << endl;
        exit(1);
    }

    // On affiche les pixels ligne par ligne (haut en bas)
    for (unsigned int i = 0; i < dimx; ++i)
    {
        for (unsigned int j = 0; j < dimy; ++j)
        {
            const Pixel p = tab[j * dimx + i];
            SDL_SetRenderDrawColor(renderer, p.getRouge(), p.getVert(), p.getBleu(), 255);
            SDL_RenderDrawPoint(renderer, i, j);
        }
    }
    SDL_SetRenderTarget(renderer, NULL);

    SDL_Rect r;
    r.x = 0;
    r.y = 0;
    r.w = dimx + zoomLevel ;
    r.h = dimy + zoomLevel ;

    if (r.w < (unsigned int)dimx)
        r.w = dimx;
    if (r.h < (unsigned int)dimy)
        r.h = dimy;
    if (r.w > WIDTH)
        r.w = WIDTH;
    if (r.h > HEIGHT)
        r.h = HEIGHT;

    r.x = (r.x - r.w / 2) + WIDTH / 2;
    r.y = (r.y - r.h / 2) + HEIGHT / 2;
    SDL_RenderCopy(renderer, texture, NULL, &r);

    SDL_RenderPresent(renderer);
}
/* void Image::ZoomIn() {

}
void Image::ZoomOut() {

} */
void Image::affBoucle()
{
    SDL_Event events;
    bool quit = false;

    Uint32 t = SDL_GetTicks(), nt;

    // tant que ce n'est pas la fin ...
    while (!quit)
    {

        nt = SDL_GetTicks();
        if (nt - t > 500)
        {
            //jeu.actionsAutomatiques();
            t = nt;
        }

        // tant qu'il y a des evenements � traiter (cette boucle n'est pas bloquante)
        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
                quit = true; // Si l'utilisateur a clique sur la croix de fermeture
            else if (events.type == SDL_KEYDOWN)
            { // Si une touche est enfoncee
                //bool mangePastille = false;
                switch (events.key.keysym.scancode)
                {
                case SDL_SCANCODE_T: // On Zoom
                    // https://wiki.libsdl.org/SDL_RenderCopy
                    if(zoomLevel >= HEIGHT) zoomLevel = HEIGHT;
                    zoomLevel ++;
                    cout << zoomLevel << endl;
                    break;
                case SDL_SCANCODE_G: // On Dézoom
                    if(zoomLevel <= 0) zoomLevel = 0;
                    zoomLevel --;
                    break;
                case SDL_SCANCODE_ESCAPE:
                    affDetruit();
                    quit = true;
                    break;
                default:
                    break;
                }
            }

            // on affiche le jeu sur le buffer cach�
            affInit();

            // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
            SDL_RenderPresent(renderer);
        }
    }
}

void Image::affDetruit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Image::afficher()
{
    affBoucle();
}

void Image::testRegression()
{
    Pixel pix(4, 5, 6);

    /* test des get dans Pixel */
    if (pix.getRouge() == 4 && pix.getVert() == 5 && pix.getBleu() == 6)
    {
        cout << "les get de Pixel fonctionnent" << endl;
    }
    else
    {
        cout << "Problème avec les get de Pixel" << endl;
    }

    /* test des set dans Pixel */
    pix.setRouge(7);
    pix.setVert(8);
    pix.setBleu(9);
    if (pix.getRouge() == 7 && pix.getVert() == 8 && pix.getBleu() == 9)
    {
        cout << "les set de Pixel fonctionnent" << endl;
    }
    else
    {
        cout << "Problème avec les set de Pixel" << endl;
    }

    /* test du constructeur d'Image */
    /* if (dimx == 4 && dimy == 3) {
        cout << "Le constructeur d'Image fonctionne" << endl;
    }
    else {
        cout << "Problème avec le constructeur d'Image" << endl;
    } */

    /* test de getPix */
    Pixel p = getPix(0, 0);
    if (p.getRouge() == 0 && p.getVert() == 0 && p.getBleu() == 0)
    {
        cout << "getPix fonctionne" << endl;
    }
    else
    {
        cout << "Problème avec getPix" << endl;
    }

    /* test de setPix */
    setPix(1, 2, pix);
    p = getPix(1, 2);
    if (p.getRouge() == pix.getRouge() && p.getVert() == pix.getVert() && p.getBleu() == pix.getBleu())
    {
        cout << "setPix fonctionne" << endl;
    }
    else
    {
        cout << "Problème avec setPix" << endl;
    }

    /*test de dessinerRectangle */
    dessinerRectangle(0, 0, 3, 2, pix);
    bool testPix = true;
    for (int i = 0; i <= 3; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            if (!(tab[j * dimx + i] == pix))
            {
                testPix = false;
            }
        }
    }
    if (testPix)
    {
        cout << "dessinerRectangle fonctionne" << endl;
    }
    else
    {
        cout << "Problème avec dessinerRectangle" << endl;
    }

    /* test de effacer */
    pix.setRouge(0);
    effacer(pix); // (0, 5, 6) = pix.
    testPix = true;
    for (unsigned i = 0; i < 4; i++)
    {
        for (unsigned j = 0; j < 3; j++)
        {
            if (!(getPix(i, j) == pix))
                testPix = false;
        }
    }
    if (testPix)
    {
        cout << "effacer fonctionne" << endl;
    }
    else
    {
        cout << "Problème avec effacer" << endl;
    }
}
