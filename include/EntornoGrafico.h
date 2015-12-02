#ifndef ENTORNOGRAFICO_H
#define ENTORNOGRAFICO_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

using namespace std;

#define ERR_SDL_CREATE_WIONDOW   1
#define ERR_SDL_INIT             2
#define ERR_SDL_LOAD_BMP         3

#define IMAGES_DIR "/home/jrojo/Projects/C/04_key_presses"

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

class EntornoGrafico
{
public:
    EntornoGrafico();
    virtual ~EntornoGrafico();
    void loopUser();

protected:
    static const int SCREEN_WIDTH = 640;
    static const int SCREEN_HEIGHT = 480;

    SDL_Window* pWindow = NULL;
    SDL_Surface* pScreenSurface = NULL;
    SDL_Surface* pKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];
    SDL_Surface* pCurrentSurface = NULL;

    void init();
    void showImage();
    SDL_Surface* loadSurface( string path );
    void loadSurfaces();
};

#endif // ENTORNOGRAFICO_H
