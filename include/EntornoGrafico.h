#ifndef ENTORNOGRAFICO_H
#define ENTORNOGRAFICO_H

#include <SDL.h>
#include <iostream>
using namespace std;

#define ERR_SDL_CREATE_WIONDOW   1
#define ERR_SDL_INIT             2

class EntornoGrafico
{
public:
    EntornoGrafico();
    virtual ~EntornoGrafico();
    bool loadMedia();
    void showImage();
protected:
private:
    static const int SCREEN_WIDTH = 640;
    static const int SCREEN_HEIGHT = 480;

    SDL_Window* pWindow = NULL;
    SDL_Surface* pScreenSurface = NULL;
    SDL_Surface* pHelloWorld = NULL;

    void init();

};

#endif // ENTORNOGRAFICO_H
